#pragma once

#include <chrono>
#include <functional>
#include <type_traits>

template<typename ReturnValue, typename ...FuncArgs>
auto execution_time(const std::function<ReturnValue(FuncArgs...)>& F, FuncArgs... args)
{
	auto begin = std::chrono::steady_clock::now();
	auto res = F(args...);
	auto end = std::chrono::steady_clock::now();
	return std::pair{ res, end - begin };
}

template<typename ...FuncArgs>
auto execution_time(const std::function<void(FuncArgs...)>& F, FuncArgs... args)
{
	auto begin = std::chrono::steady_clock::now();
	F(args...);
	auto end = std::chrono::steady_clock::now();
	return end - begin;
}

auto execution_time(const std::function<void(void)>& F)
{
	auto begin = std::chrono::steady_clock::now();
	F();
	auto end = std::chrono::steady_clock::now();
	return end - begin;
}

