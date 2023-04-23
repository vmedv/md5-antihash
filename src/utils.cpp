#include "utils.h"
#include "openssl/md5.h"

#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

std::string md5_utils::md5(const std::string &str) {
    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, str.c_str(), str.size());
    MD5_Final(hash, &md5);

    std::stringstream ss;

    for (unsigned char i: hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( i );
    }
    return ss.str();

}

std::pair<std::size_t, std::size_t> md5_utils::spec_log(std::size_t x, std::size_t n) {
    int k = 0;
    if (x < n) return {x, 1};

    while (x >= (std::size_t) std::pow(n, k)) {
        x -= k == 0 ? 0 : (std::size_t) std::pow(n, k);
        k++;
    }
    return {x, k};
}


std::string md5_utils::gen_string(std::size_t x, const std::string &alphabet) {
    auto [nx, len] = spec_log(x, alphabet.size());
    std::string ans;
    for (int i = 0; i < len; i++) {
        ans += alphabet[nx % alphabet.size()];
        nx /= alphabet.size();
    }
    return ans;
}