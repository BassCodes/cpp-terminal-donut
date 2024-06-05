// Alexander Bass
// Created 4/16/24
// Modified 4/17/24

#include "donut.h"
#include "point.h"
#include "types.h"
#include <vector>

#include "vec3.h"

vec3 sample_rgb(u8 *texture, usize index) {
    u8 red = texture[index];
    u8 green = texture[index + 1];
    u8 blue = texture[index + 2];
    vec3 color = vec3((f64)red, (f64)green, (f64)blue);
    color *= vec3(1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0);
    return color;
};

inline vec3 mix_transparency(vec3 transparent, vec3 solid) {
    if (transparent.i == 0.0 && transparent.j == 0.0 && transparent.k == 0.0) {
        return solid;
    } else {
        return transparent;
    }
}

std::vector<Point> generate_cube(u8 *bottom_texture, u8 *top_texture, u8 *side_texture, i32 face_x, i32 face_y) {
    std::vector<Point> out = {};
    const vec3 grass_color_scale = vec3(0.4, 1.0, 0.4);
    const usize image_size = 16;
    const usize point_count = 22;
    const usize world_width = 16;
    for (usize l_x = 0; l_x < point_count; l_x++) {
        for (usize l_y = 0; l_y < point_count; l_y++) {

            f64 sx = (f64)l_x / (f64)point_count;
            f64 sy = (f64)l_y / (f64)point_count;
            usize index = 3 * ((usize)(sx * (f64)(image_size)) + usize(sy * (f64)(image_size)) * image_size);
            vec3 dirt = sample_rgb(bottom_texture, index);
            vec3 grass = sample_rgb(top_texture, index);
            vec3 side = sample_rgb(side_texture, index);
            grass *= grass_color_scale;
            side *= grass_color_scale;

            side = mix_transparency(side, dirt);

            f64 x_w = sx * (f64)world_width;
            f64 y_w = sy * (f64)world_width;
            f64 w_w = (f64)world_width;

            if (face_y == -1 || (face_y == 1 && face_x == 0)) {
                out.push_back(*Point(x_w, 0, y_w).set_rgb(side));
            }
            if (face_x == -1 || (face_x == 1 && face_y == 0)) {
                out.push_back(*Point(0, x_w, y_w).set_rgb(side));
            }
            if (face_x == 1 || (face_x == -1 && face_y == 0)) {
                out.push_back(*Point(w_w, x_w, y_w).set_rgb(side));
            }
            if (face_y == 1 || (face_y == -1 && face_x == 0)) {
                out.push_back(*Point(x_w, w_w, y_w).set_rgb(side));
            }

            out.push_back(*Point(x_w, y_w, w_w).set_rgb(dirt));
            out.push_back(*Point(x_w, y_w, 0.0).set_rgb(grass));
        }
    }
    for (auto &p : out) {
        p.translate_x((f64)face_x * (f64)world_width - (f64)world_width / 2.0);
        p.translate_y((f64)face_y * (f64)world_width - (f64)world_width / 2.0);
        p.translate_z(-(f64)world_width / 2.0);
    }
    return out;
}

std::vector<Point> generate_donut(u8 *bottom_texture, u8 *top_texture, u8 *side_texture) {
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

    return points;
}