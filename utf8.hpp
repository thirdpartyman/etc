#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <string>

namespace utf8
{
    std::string encode(const std::string& str)
    {
        std::wstring wstr(str.length(), L' ');
        std::mbstowcs(wstr.data(), str.c_str(), str.length());

        int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
        std::string utf8str(size_needed, ' ');
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), utf8str.data(), size_needed, NULL, NULL);

        return utf8str;
    }

    std::string decode(const std::string& utf8str)
    {
        int wchars_num = MultiByteToWideChar(CP_UTF8, 0, utf8str.data(), -1, NULL, 0) - 1;

        std::wstring wstr(wchars_num, L' ');
        MultiByteToWideChar(CP_UTF8, 0, utf8str.c_str(), -1, wstr.data(), wchars_num);

        std::string res(wchars_num, ' ');
        std::wcstombs(res.data(), wstr.c_str(), wchars_num);

        return res;
    }
};
#else
namespace utf8
{
    inline std::string encode(const std::string& str) { return str; }
    inline std::string decode(const std::string& str) { return str; }
}
#endif

