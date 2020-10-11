#pragma once

#include <visit_struct/visit_struct.hpp>
#include <visit_struct/visit_struct_intrusive.hpp>


// Convert array into a tuple
template<typename Struct, std::size_t... I>
auto a2t_impl(const Struct& a, const Struct& b, std::index_sequence<I...>)
{
    return ((visit_struct::get<I>(a) == visit_struct::get<I>(b)) && ...);
}

template<typename Struct, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const Struct& a, const Struct& b)
{
    return a2t_impl(a, b, Indices{});
}


template<class Struct, typename = std::enable_if_t<visit_struct::traits::is_visitable<Struct>::value>>
bool operator == (const Struct& a, const Struct& b) {
    return a2t<Struct, visit_struct::field_count<Struct>()>(a, b);
}

