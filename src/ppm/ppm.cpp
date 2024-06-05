// Alexander Bass
// Created 4/16/24
// Modified 4/17/24
#include "ppm.h"
using std::string;
#include <cassert>
#include <fstream>
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
        // The extraction operator assumes a uint8_t type represents an ascii
        // character and thus grabs the first ascii character of the color value
        // and places it within the u8.
        // A u32 is used as the extraction operator understands it to be an integer
        u32 val = 0;
        input >> val;
        buffer[i] = (u8)(val);
    }

    return buffer;
}

u8 *ppm::from_file(string path) {
    std::ifstream in(path);
    u8 *ppm = ppm::load_ppm(in);
    in.close();
    return ppm;
}