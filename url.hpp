#pragma once

#include <string>
#include <fmt/format.h>

inline std::string url_encode(const std::string& s) {
    std::string hex[1 << 8];
    size_t count = 0;
    for (auto c : s) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
            count++;
        else
        {
            uint8_t index = c;
            if (hex[index] == "")
                hex[index] = fmt::format("%{:02x}", c);
            count += hex[index].length();
        }
    }
    std::string encoded(count, 0);
    for (auto it = encoded.data(); auto c : s) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            *it++ = c;
        }
        else {
            uint8_t index = c;
            strcpy(it, hex[index].data());
            it += hex[index].length();
        }
    }
    return encoded;
}

inline std::string url_decode(const std::string& s) {
    std::string decoded;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] == '%') {
            int n;
            n = std::stoul(s.substr(i + 1, 2), nullptr, 16);
            decoded = decoded + static_cast<char>(n);
            i = i + 2;
        }
        else if (s[i] == '+') {
            decoded = decoded + ' ';
        }
        else {
            decoded = decoded + s[i];
        }
    }
    return decoded;
}