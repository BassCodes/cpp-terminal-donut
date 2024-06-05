// Alexander Bass
// Created 4/16/24
// Modified 4/17/24
#pragma once

#include "../types.h"

#include <istream>
#include <string>

namespace ppm {
    u8 *load_ppm(std::istream &input);
    u8 *from_file(std::string path);
} // namespace ppm