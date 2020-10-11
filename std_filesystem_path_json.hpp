#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>

namespace nlohmann {
    template<>
    struct adl_serializer<std::filesystem::path>
    {
        static void to_json(json& j, const std::filesystem::path& path)
        {
            j = path.string();
        }

        static void from_json(const json& j, std::filesystem::path& path)
        {
            path = j.get<std::string>();
        }
    };
}