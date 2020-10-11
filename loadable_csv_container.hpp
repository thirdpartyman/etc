#pragma once

#include "is_container.hpp"
#include <visit_struct/visit_struct.hpp>
#include "struct_fields_to_container.hpp"

#include "csv2/csv2.hpp"

struct Writer : csv2::Writer<>
{
    template <typename Stream>
    Writer(Stream&& stream) : csv2::Writer<>(stream) {}

    template <typename Container>
    void write_row(Container&& row) {
        csv2::Writer<>::write_row(row);
        if (stream_.bad()) throw std::bad_exception();
    }
};

template<template<class> class Container, class Struct>
class loadable_csv_container : public Container<Struct>
{
public:
    bool load(const std::string& filename)
    {
        using namespace csv2;
        Reader<> csv;

        try
        {
            if (csv.mmap(filename)) {
                const auto header = csv.header();
                for (const auto row : csv) {
                    Struct user;
                    auto cell = row.begin();
                    visit_struct::for_each(user,
                        [&](const char* name, auto& value) {
                            std::string str;
                            (*cell).read_value(str);
                            value = str;
                        });
                    add<Container, Struct>(*this, user);
                }
            }
            else return false;
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    bool save(const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        try
        {
            using namespace csv2;
            ::Writer writer(file);

            writer.write_row(fields::names<std::vector, Struct>());

            for (const auto& account : *this)
            {
                auto res = fields::values<std::vector>(account);
                writer.write_row(res);
            }
            file.close();
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
};