#pragma once

#include <type_traits>

namespace std
{
    template<typename T, typename _ = void>
    struct is_container : std::false_type {};

    template<typename... Ts>
    struct is_container_helper {};

    template<typename T>
    struct is_container<
        T,
        std::conditional_t<
        false,
        is_container_helper<
        typename T::value_type,
        typename T::size_type,
        typename T::allocator_type,
        typename T::iterator,
        typename T::const_iterator,
        decltype(std::declval<T>().size()),
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end()),
        decltype(std::declval<T>().cbegin()),
        decltype(std::declval<T>().cend())
        >,
        void
        >
    > : public std::true_type{};

}


template <class C, class T>
auto append(C& container, const T& value, int)
-> decltype(container.push_back(value), void())
{
    container.push_back(value);
}

template <class C, class T>
void append(C& container, const T& value, ...)
{
    container.insert(value);
}

template <template<class> class Container, typename T>
void add(Container<T>& container, const T& value) {
    append(container, value, 0);
}