#ifndef TASK_2_UTILS_H
#define TASK_2_UTILS_H

#include <string>

namespace md5_utils {

    std::string md5(const std::string &str);

    std::pair<std::size_t, std::size_t> spec_log(std::size_t x, std::size_t n);

    std::string gen_string(std::size_t x, std::string const &alphabet);

}

#endif //TASK_2_UTILS_H
