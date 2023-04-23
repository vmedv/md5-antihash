#ifndef TASK_2_BRUTE_FORCE_H
#define TASK_2_BRUTE_FORCE_H

#include <functional>
#include <concepts>
#include <optional>
#include <thread>
#include <iostream>
#include <queue>
#include <mutex>

template<typename Producer, typename TargetFunc, typename TargetRes>
class brute_force;

template<typename T, typename R>
class brute_force<std::function<T(std::size_t)>, std::function<R(T)>, R> : std::function<T(std::size_t)>,
                                                                           std::function<R(T)> {
private:
    using producer = std::function<T(std::size_t)>;
    using target_func = std::function<R(T)>;
    std::vector<std::jthread> thread_pool;
    std::optional<T> result_;
    std::atomic_bool calculated{false};
    std::atomic_bool started{false};
    std::mutex m;

public:
    brute_force(std::size_t threads, producer const &p, target_func const &t, R const &target)
            : producer(p),
              target_func(t) {
        thread_pool.reserve(threads);
        for (std::size_t thread = 0; thread < threads; ++thread) {
            thread_pool.emplace_back([&, thread, threads, target]() {
                auto iter = thread;
                while (!calculated) {
                    started.wait(false);
                    auto task = producer::operator()(iter);
                    auto taskRes = target_func::operator()(task);
                    if (target == taskRes) {
                        std::unique_lock lg(m);
                        result_ = task;
                        calculated = true;
                        lg.unlock();
                        calculated.notify_one();
                        break;
                    }
                    iter += threads;
                }
            });
        }
    }

    void toggle() {
        started = !started;
        started.notify_all();
    }

    bool is_paused() {
        return !started;
    }

    void pause() {
        started = false;
    }

    void start() {
        if (started) {
            return;
        }
        started = true;
        started.notify_all();
    }

    bool is_ready() {
        return result_.has_value();
    }

    T result() {
        calculated.wait(false);
        return result_.value();
    }

};

#endif //TASK_2_BRUTE_FORCE_H
