#pragma once

#include <fstream>
#include <iomanip>

template<typename Child>
struct loadable_json_struct
{
    bool load(const std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            try
            {
                json j;
                file >> j;
                j.get_to(get_this());
            }
            catch (...)
            {
                return false;
            }
        }
        else return false;
        return true;
    }

    bool save(const std::string& filename)
    {
        std::ofstream file(filename, std::ios::trunc);
        file << std::setw(4) << to_json();
        return !file.bad();
    }


    json to_json()
    {
        return get_this();
    }

protected:
    Child& get_this() {
        return reinterpret_cast<Child&>(*this);
    };
    using child_class = Child;
};
