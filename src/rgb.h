// Alexander Bass
// Created 4/16/24
#pragma once
#include "types.h"
struct rgb {
    f64 r;
    f64 g;
    f64 b;
    rgb(f64 _r, f64 _g, f64 _b) {
        r = _r;
        g = _g;
        b = _b;
    }
    void mix(rgb rhs) {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
    }
};