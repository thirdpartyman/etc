#pragma once

#include <iostream>

struct Console
{
    Console()
    {
        std::cout << std::boolalpha;
    }

    template<typename... Types>
    static void log(Types const&...  args)
    {
        (std::cout << ... << args) << std::endl;
    }
};

#define console Console()