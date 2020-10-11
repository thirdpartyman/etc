#pragma once

#include <functional>

template<typename ReturnValue, typename ...Args, typename Function>
auto function_pointer_cast_helper(std::function< ReturnValue(Args...)> f1, Function f2)
{
    return static_cast<ReturnValue(*)(Args...)>(f2);
}

template<typename Function>
auto function_pointer_cast(Function f)
{
    auto func = std::function{ f };
    return function_pointer_cast_helper(func, f);
}