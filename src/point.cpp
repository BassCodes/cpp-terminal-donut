// Alexander Bass
// Created 4/16/24
#include "point.h"
#include "types.h"

#include <cmath>

void Point::rotate_x(f64 angle) {
    f64 cos_a = cos(angle);
    f64 sin_a = sin(angle);
    f64 y_1 = this->y * cos_a - this->z * sin_a;
    f64 z_1 = this->y * sin_a + this->z * cos_a;
    this->y = y_1;
    this->z = z_1;
}

void Point::rotate_y(f64 angle) {
    f64 cos_a = cos(angle);
    f64 sin_a = sin(angle);

    f64 x_1 = this->x * cos_a + this->z * sin_a;
    f64 z_1 = this->z * cos_a - this->x * sin_a;
    this->x = x_1;
    this->z = z_1;
}

void Point::rotate_z(f64 angle) {
    f64 cos_a = cos(angle);
    f64 sin_a = sin(angle);

    f64 x_1 = this->x * cos_a - this->y * sin_a;
    f64 y_1 = this->x * sin_a + this->y * cos_a;
    this->x = x_1;
    this->y = y_1;
}