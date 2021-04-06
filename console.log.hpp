#pragma once

#include <iostream>

struct Console
{
    Console()
    {
        std::cout << std::boolalpha;
    }

    template<typename... Types>
    static void log(Types const&... args)
    {
        log_helper(args...);
        //(std::cout << ... << args) << std::endl;
    }

private:
    template<typename T, typename... Types>
    static void log_helper(const T& arg1, Types const&... args)
    {
        std::cout << arg1;
        if constexpr (sizeof...(Types))
            (log_helper_helper(args), ...);
        std::cout << std::endl;
    }

    template<typename T>
    static void log_helper_helper(const T &arg)
    {
        std::cout << ", " << arg;
    }
};

#define console Console()