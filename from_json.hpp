#pragma once

#include <nlohmann/json.hpp>
#include <visit_struct/visit_struct.hpp>
#include <visit_struct/visit_struct_intrusive.hpp>
#include "trycatch.hpp"

#define VISIT_FROM_JSON \
template<typename T, typename = std::enable_if_t<visit_struct::traits::is_visitable<T>::value>>\
static void from_json(const nlohmann::json& j, T& p) {\
    visit_struct::for_each(p,\
        [&](const char* name, auto& value) {\
            try{\
                j.at(name).get_to(value);\
            }\
            catch (...)\
            {\
                puts(name);\
            }\
        });\
}

VISIT_FROM_JSON




#define VISIT_FROM_JSON_ALT \
template<typename T, typename = std::enable_if_t<visit_struct::traits::is_visitable<T>::value>>\
static void from_json(const nlohmann::json& j, T& p) {\
    for (const auto& [key, value] : j.items()) {\
        visit_struct::for_each(p,\
            [&](const char* name, auto& struct_value) {\
                if (key == name)\
                    value.get_to(struct_value);\
            });\
    }\
}


