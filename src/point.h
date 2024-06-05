// Alexander Bass
// Created 4/16/24
// Modified 4/17/24
#pragma once
#include "types.h"
#include "vec3.h"
class Point {
  private:
    f64 x;
    f64 y;
    f64 z;
    f64 r;
    f64 g;
    f64 b;

  public:
    Point(f64 _x, f64 _y, f64 _z) {
        x = _x;
        y = _y;
        z = _z;
        r = 1.0;
        g = 1.0;
        b = 1.0;
    }
    Point() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }
    void set_xyz(f64 _x, f64 _y, f64 _z) {
        x = _x;
        y = _y;
        z = _z;
    };
    void set_xyz(vec3 pos) {
        x = pos.i;
        y = pos.j;
        z = pos.k;
    };
    void rotate_x(f64 angle);
    void rotate_y(f64 angle);
    void rotate_z(f64 angle);
    Point *translate(f64 dx, f64 dy, f64 dz) {
        x += dx;
        y += dy;
        z += dz;
        return this;
    };

    f64 get_x() const {
        return x;
    };
    f64 get_y() const {
        return y;
    };
    f64 get_z() const {
        return z;
    };

    vec3 get_xyz() const {
        return vec3(x, y, z);
    }

    f64 get_r() const {
        return r;
    }
    f64 get_g() const {
        return g;
    }
    f64 get_b() const {
        return b;
    }

    vec3 get_rgb() const {
        return vec3(r, g, b);
    }

    void translate_x(f64 dx) {
        x += dx;
    }
    void translate_y(f64 dy) {
        y += dy;
    }
    void translate_z(f64 dz) {
        z += dz;
    }

    Point *set_rgb(f64 _r, f64 _g, f64 _b) {
        r = _r;
        g = _g;
        b = _b;
        return this;
    };
    Point *set_rgb(vec3 col) {
        r = col.i;
        g = col.j;
        b = col.k;
        return this;
    };
};