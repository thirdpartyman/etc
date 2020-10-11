#pragma once

#include <functional>

template<typename T>
struct autoproperty
{
	using type = T;
	T val;

	std::function<void(const T&)> setter;
	std::function<T& (void)> getter;

	autoproperty& operator=(const T& value)
	{
		setter(value);
		return *this;
	}

	T& operator()() { return getter(); }

	operator T() { return getter(); }

	T& operator*() { return val; }

	T* operator ->() { return &val; }
};

#define get(variable) .getter = [&property = *variable](void) -> decltype(variable)::type&


#define set(variable) .setter = [&property = *variable](const decltype(variable)::type& value)