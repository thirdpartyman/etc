#pragma once

#include <fmt/printf.h>

#define print(...) fmt::print(__VA_ARGS__)
#define println(...) print(__VA_ARGS__); puts("")