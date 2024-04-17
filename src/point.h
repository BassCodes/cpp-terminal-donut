// Alexander Bass
// Created 4/16/24
#pragma once
#include "rgb.h"
#include "types.h"
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
    void set_xyz(f64 _x, f64 _y, f64 _z) {
        x = _x;
        y = _y;
        z = _z;
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

    f64 get_r() const {
        return r;
    }
    f64 get_g() const {
        return g;
    }
    f64 get_b() const {
        return b;
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
    Point *set_rgb(rgb col) {
        r = col.r;
        g = col.g;
        b = col.b;
        return this;
    };
};