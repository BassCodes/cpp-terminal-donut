// Alexander Bass
// Created 4/16/24
// Modified 4/17/24
#pragma once
#include "types.h"
struct vec3 {
    f64 i;
    f64 j;
    f64 k;
    vec3(f64 _i, f64 _j, f64 _k) {
        i = _i;
        j = _j;
        k = _k;
    }

    vec3 &operator*=(const vec3 &rhs) {
        i *= rhs.i;
        j *= rhs.j;
        k *= rhs.k;
        return *this;
    }
    vec3 operator*(const vec3 &rhs) {
        vec3 copy = *this;
        copy.i *= rhs.i;
        copy.j *= rhs.j;
        copy.k *= rhs.k;
        return copy;
    }
    vec3 &operator*=(const f64 &rhs) {
        i *= rhs;
        j *= rhs;
        k *= rhs;
        return *this;
    }
    vec3 operator*(const f64 &rhs) {
        vec3 copy = *this;
        copy.i *= rhs;
        copy.j *= rhs;
        copy.k *= rhs;
        return copy;
    }
};
