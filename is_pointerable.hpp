#pragma once

#include <type_traits>

template<typename T, typename _ = void>
struct is_pointerable : std::false_type {};

template<typename... Ts>
struct is_pointerable_helper {};

template<typename T>
struct is_pointerable<
        T,
        std::conditional_t<
            false,
            is_pointerable_helper<
                decltype(std::declval<T>().operator*()),
                decltype(std::declval<T>().operator->())
                >,
            void
            >
        > : public std::true_type {};