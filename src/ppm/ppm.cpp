// Alexander Bass
// Created 4/16/24
#include "ppm.h"
using std::string;
#include <cassert>
#include <iostream>
#include <string>
u8 *ppm::load_ppm(std::istream &input) {
    string header;
    input >> header;
    assert(header == "P3");
    u32 width, height;
    u32 color;
    input >> width;
    input >> height;
    assert(width == 16 && height == 16);
    input >> color;
    assert(color == 255);

    u8 *buffer = new u8[width * height * 3];
    for (size_t i = 0; i < width * height * 3; i++) {
        u16 val = 0;

        input >> val;
        buffer[i] = val;
    }

    return buffer;
}