// Alexander Bass
// Created 4/16/24

#include "donut.h"
#include "point.h"
#include "types.h"
#include <vector>

#include "rgb.h"

rgb sample_rgb(u8 *texture, usize index) {
    u8 d_red = texture[index * 3];
    u8 d_green = texture[index * 3 + 1];
    u8 d_blue = texture[index * 3 + 2];
    f64 d_r = (f64)d_red / 255.0;
    f64 d_g = (f64)d_green / 255.0;
    f64 d_b = (f64)d_blue / 255.0;
    return rgb(d_r, d_g, d_b);
};

inline rgb mix_transparency(rgb transparent, rgb solid) {
    if (transparent.r == 0.0 && transparent.g == 0.0 && transparent.b == 0.0) {
        return solid;
    }
    return transparent;
}

std::vector<Point> generate_cube(u8 *bottom_texture, u8 *top_texture, u8 *side_texture, i32 face_x, i32 face_y) {
    std::vector<Point> out = {};
    const usize image_size = 16;
    const usize point_count = 22;
    const usize world_width = 16;
    for (usize l_x = 0; l_x < point_count; l_x++) {
        for (usize l_y = 0; l_y < point_count; l_y++) {

            f64 sx = (f64)l_x / (f64)point_count;
            f64 sy = (f64)l_y / (f64)point_count;
            usize index = (usize)(sx * (f64)(image_size)) + usize(sy * (f64)(image_size)) * image_size;
            rgb dirt = sample_rgb(bottom_texture, index);
            rgb grass = sample_rgb(top_texture, index);
            rgb sides = sample_rgb(side_texture, index);
            grass.mix(rgb(0.4, 1.0, 0.4));
            sides.mix(rgb(0.4, 1.0, 0.4));

            sides = mix_transparency(sides, dirt);

            f64 x_w = sx * (f64)world_width;
            f64 y_w = sy * (f64)world_width;
            f64 w_w = (f64)world_width;

            if (face_y == -1 || (face_y == 1 && face_x == 0)) {
                out.push_back(*Point(x_w, 0, y_w).set_rgb(sides));
            }
            if (face_x == -1 || (face_x == 1 && face_y == 0)) {
                out.push_back(*Point(0, x_w, y_w).set_rgb(sides));
            }
            if (face_x == 1 || (face_x == -1 && face_y == 0)) {
                out.push_back(*Point(w_w, x_w, y_w).set_rgb(sides));
            }
            if (face_y == 1 || (face_y == -1 && face_x == 0)) {
                out.push_back(*Point(x_w, w_w, y_w).set_rgb(sides));
            }

            out.push_back(*Point(x_w, y_w, w_w).set_rgb(dirt));
            out.push_back(*Point(x_w, y_w, 0.0).set_rgb(grass));
        }
    }
    for (usize i = 0; i < out.size(); i++) {
        Point *p = &out[i];
        p->translate_x((f64)face_x * (f64)world_width - (f64)world_width / 2.0);
        p->translate_y((f64)face_y * (f64)world_width - (f64)world_width / 2.0);
        p->translate_z(-(f64)world_width / 2.0);
    }
    return out;
}

std::vector<Point> generate_donut(u8 *bottom_texture, u8 *top_texture, u8 *side_texture, f64 offset) {
    std::vector<Point> points = {};
    for (i32 x = -1; x <= 1; x++) {
        for (i32 y = -1; y <= 1; y++) {
            if (x == y && x == 0) {
                continue;
            }
            std::vector<Point> pt = generate_cube(bottom_texture, top_texture, side_texture, x, y);
            points.insert(points.end(), pt.begin(), pt.end());
        }
    }
    for (usize i = 0; i < points.size(); i++) {
        Point *point = &points[i];
        point->translate_z(offset);
    }

    return points;
}