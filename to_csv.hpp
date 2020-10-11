#pragma once

#include <csv/writer.hpp>
#include <visit_struct/visit_struct.hpp>
#include "struct_fields_to_container.hpp"


template<template<class> class Container, class T, typename = std::enable_if_t<visit_struct::traits::is_visitable<T>::value>>
void to_csv(const std::string& filename, const Container<T>& struct_list)
{
    csv::Writer foo{ filename };
    foo.configure_dialect()
        .delimiter(", ")
        .column_names(fields::names<std::vector, T>());
    for (const auto& account : struct_list)
        foo.write_row(fields::values<std::vector>(account));
}