// Alexander Bass
// Created 4/16/24
#pragma once

#include "../types.h"

#include <istream>

namespace ppm {

    u8 *load_ppm(std::istream &input);
} // namespace ppm