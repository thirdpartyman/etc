#pragma once

#include <nlohmann/json.hpp>
#include <visit_struct/visit_struct.hpp>


template<typename T, typename = std::enable_if_t<visit_struct::traits::is_visitable<T>::value>>
void to_json(nlohmann::json& j, const T& p) {
    visit_struct::for_each(p,
        [&](const char* name, auto& value) {
            j[name] = value;
        });
}
