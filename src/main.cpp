// Alexander Bass
// Created 4/16/24
// Modified 4/17/24

#include "donut.h"
#include "point.h"
#include "ppm/ppm.h"
#include "pts.h"
#include "types.h"
#include <cassert>
#include <chrono>
#include <cmath>
#include <format>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

const i32 WIDTH = 120;
const i32 HEIGHT = 100;
const i32 DEPTH = WIDTH;

using std::format;
using std::vector, std::ifstream;

void draw(size_t *grid, vector<Point> &points);
void update(vector<Point> &points);

int main() {

    u8 *dirt = ppm::from_file("dirt.ppm");
    u8 *grass = ppm::from_file("grass_top.ppm");
    u8 *grass_side = ppm::from_file("grass_side.ppm");

    std::vector<Point> points = {};
    points.push_back(*Point().set_rgb(1.0, 0, 0));

    std::vector<Point> horse = pts::load_pts_from_path("horse.pts.txt");
    for (auto &p : horse) {
        vec3 a = p.get_xyz();
        a *= 300.0;
        p.set_xyz(a);
    }
    points.insert(points.end(), horse.begin(), horse.end());

    // std::vector<Point> donut = generate_donut(dirt, grass, grass_side);
    // points.insert(points.end(), donut.begin(), donut.end());

    delete[] dirt;
    delete[] grass;
    delete[] grass_side;

    auto grid = new size_t[WIDTH * HEIGHT];

    while (true) {
        // Move cursor to top left
        std::cout << "\033[0;0H";
        // Draw points
        draw(grid, points);
        // Rotate points
        update(points);
        // Wait
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
        // Repeat
    }
    return 0;
}

i32 w_x_to_screen(f64 w_x) {
    return static_cast<i32>(std::round(w_x + static_cast<f64>(WIDTH) / 2.0));
}

i32 w_y_to_screen(f64 w_y) {
    return static_cast<i32>(std::round(w_y + static_cast<f64>(HEIGHT) / 2.0 + 10.5));
}

f64 w_z_to_screen(f64 w_z) {
    return (w_z + static_cast<f64>(DEPTH) / 2.0) / static_cast<f64>(DEPTH);
}

void draw(size_t *grid, vector<Point> &points) {
    // grid is a list of handles to points in the points vector.
    // these handles can be 0 to indicate that there is no representative point
    // and therefor no pixel for that position.
    // the values of grid can also be the index to points to represent a point
    // being mapped to a pixel. This system also handles depth buffering.
    for (u32 i = 0; i < static_cast<u32>(WIDTH * HEIGHT); i++) {
        grid[i] = 0;
    };

    // Pseudo-rasterization
    for (size_t i = 0; i < points.size(); i++) {
        Point &p = points[i];
        f64 p_x = p.get_x();
        f64 p_y = p.get_y();
        f64 p_z = p.get_z();

        i32 s_x = w_x_to_screen(p_x);
        i32 s_y = w_y_to_screen(p_y);
        if (0 <= s_x && s_x < HEIGHT && 0 <= s_y && s_y < HEIGHT) {
            size_t index = static_cast<size_t>(s_x + s_y * HEIGHT);
            size_t existing_pixel_handle = grid[index];
            if (existing_pixel_handle == 0) {
                grid[index] = i + 1;
            } else if (points[existing_pixel_handle - 1].get_z() < p_z) {
                // Pixel already exists at point on screen. Check its depth.
                grid[index] = i + 1;
            }
        }
    }

    // Printing
    std::string line = "";
    for (size_t y = 0; y < static_cast<size_t>(WIDTH); y++) {
        for (size_t x = 0; x < static_cast<size_t>(HEIGHT); x++) {
            size_t index = x + y * HEIGHT;
            size_t handle = grid[index];
            if (handle == 0) {
                line += "  ";
                continue;
            }
            Point p = points[handle - 1];
            f64 depth = w_z_to_screen(p.get_z());
            assert(depth >= 0.0);
            assert(depth <= 1.0);
            vec3 rgb = p.get_rgb() * depth * 255.0;
            u8 r8 = (u8)(round(rgb.i));
            u8 g8 = (u8)(round(rgb.j));
            u8 b8 = (u8)(round(rgb.k));
            line += format("\033[38;2;{};{};{}m██", r8, g8, b8);
        }
        line += '\n';
    }
    std::cout << line;
}

void update(vector<Point> &points) {
    for (auto &p : points) {
        p.rotate_x(0.02);
        p.rotate_y(-0.04);
        p.rotate_z(0.03);
    }
}
