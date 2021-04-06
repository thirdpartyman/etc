#pragma once

#include <string>
#include <iostream>

#include <visit_struct/visit_struct.hpp>
#include <visit_struct/visit_struct_intrusive.hpp>
#include <magic_enum.hpp>
#include <optional>


#include "is_container.hpp"

static size_t Tabs(0);
template<typename T, typename = std::enable_if_t<visit_struct::traits::is_visitable<T>::value>>
std::ostream& operator << (std::ostream& out, const T& my_struct) {
    out << "{" << std::endl;
    Tabs++;
    visit_struct::for_each(my_struct,
        [&](const char* name, const auto& value) {
            for (size_t i = 0; i != Tabs; i++) out << "    ";
            out << name << ": " << value << ',' << std::endl;
        });
    Tabs--;
    for (size_t i = 0; i != Tabs; i++) out << "    ";
    out << "}";
    return out;
}

#include <is_pointerable.hpp>

template<typename T, typename = std::enable_if_t<!visit_struct::traits::is_visitable<T>::value>, typename = std::enable_if_t<is_pointerable<T>::value>>
std::ostream& operator << (std::ostream& out, const T& my_struct) {
    out << ((my_struct) ? *my_struct : "null");
    return out;
}

//template<typename T, typename = std::enable_if_t<!visit_struct::traits::is_visitable<T>::value>, typename = std::enable_if_t<std::is_enum<T>::value>>
//std::ostream& operator << (std::ostream& out, const T& my_enum) {
//    out << magic_enum::enum_name(my_enum);
//    return out;
//}

template<typename T, typename = std::enable_if_t<!std::is_same<T, std::string>::value>, typename = std::enable_if_t<!std::is_enum<T>::value>, typename = std::enable_if_t<std::is_container<T>::value>>
std::ostream& operator << (std::ostream& out, const T& my_container) {
    if (my_container.size() == 0) return out << "[]";
    for (size_t i = 0; i != Tabs; i++) out << "    ";
    out << "[";
    Tabs++;
    if (!my_container.empty()) out << std::endl;
    for (const auto& value : my_container)
    {
        for (size_t i = 0; i != Tabs; i++) out << "    ";
        out << value << ",\n";
    }
    Tabs--;
    for (size_t i = 0; i != Tabs; i++) out << "    ";
    out << "]";
    return out;
}

//inline std::ostream& operator << (std::ostream& out, const std::string& my_string) {
//    out << '"' << my_string.c_str() << '"';
//    return out;
//}
//
//#include <filesystem>
//inline std::ostream& operator << (std::ostream& out, const std::filesystem::path& my_string) {
//    out << my_string.string();
//    return out;
//}
