#pragma once

#include <visit_struct/visit_struct.hpp>
#include "is_container.hpp"
#include <string>
#include <sstream>

namespace fields
{
    template<template<class> class Container, class Struct, typename = std::enable_if_t<std::is_container<Container<std::string>>::value>>
    Container<std::string> names() {
        Container<std::string> res;
        if constexpr (std::is_same<Container<std::string>, std::vector<std::string>>::value)
            res.reserve(visit_struct::field_count<Struct>());

        visit_struct::visit_types<Struct>([&]<typename T>(const char* name, visit_struct::type_c<T>) {
            res.insert(res.end(), name);
        });
        return res;
    }

    template<template<class> class Container, class Struct, typename = std::enable_if_t<std::is_container<Container<std::string>>::value>>
    Container<std::string> names(const Struct&) {
        return names<Container, Struct>();
    }

    template<template<class> class Container, class Struct, typename = std::enable_if_t<std::is_container<Container<std::string>>::value>>
    Container<std::string> values(const Struct& s) {
        Container<std::string> res;
        if constexpr (std::is_same<Container<std::string>, std::vector<std::string>>::value)
            res.reserve(visit_struct::field_count<Struct>());

        visit_struct::for_each(s,
            [&](const char* name, auto& value) {
                if constexpr (!std::is_same<decltype(value), std::string>::value)
                {
                    std::ostringstream stream;
                    stream << value;
                    res.insert(res.end(), stream.str());
                }            
                else res.insert(res.end(), value);
            });


        return res;
    }
}
