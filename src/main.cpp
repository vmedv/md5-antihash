#include <chrono>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <future>

#include "brute_force.h"
#include "utils.h"

bool wait_input() {
    std::string got;
    std::cin >> got;
    if (got == "p") { return true; }
    return false;
}

int main(int argc, char **argv) {

    std::string target = argv[1];

    std::ifstream cfg(argv[2]);
    std::string alphabet((std::istreambuf_iterator<char>(cfg)),
                         std::istreambuf_iterator<char>());
    std::sort(alphabet.begin(), alphabet.end());
    auto last = std::unique(alphabet.begin(), alphabet.end());
    alphabet.erase(last, alphabet.end());

    using namespace std::chrono_literals;

    using md5brute_force = brute_force<std::function<std::string(std::size_t)>, std::function<std::string(
            std::string)>, std::string>;
    md5brute_force bf(
            8,
            [&](std::size_t num) { return md5_utils::gen_string(num, alphabet); },
            &md5_utils::md5,
            target);
    bf.start();

    while (!bf.is_ready()) {
        while (!kbhit()) {
            if (bf.is_ready()) goto drop_toggling;
        }
        int c = getch();
        if (c == 'p') {
            bf.toggle();
            std::cout << "toggled\n";
        }
    }
    drop_toggling:
    auto r = bf.result();

    std::cout << "result: " << r << std::endl;

}