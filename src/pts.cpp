// Alexander Bass
// Created 4/19/24
// Modified 4/19/24
#include "point.h"
#include <istream>
#include <string>
#include <vector>
using std::string;
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

namespace pts {
    std::vector<Point> load_pts(std::istream &input) {
        std::vector<Point> output = {};
        while (true) {
            f64 i = 0.0, j = 0.0, k = 0.0;
            f64 ni = 0.0, nj = 0.0, nk = 0.0;
            input >> i;
            input >> j;
            input >> k;
            input >> ni;
            input >> nj;
            input >> nk;
            if (input.eof() || input.fail()) {
                return output;
            }
            output.push_back(Point(i, j, k));
        }
        return output;
    }
    std::vector<Point> load_pts_from_path(std::string path) {
        std::ifstream input(path);
        return load_pts(input);
        input.close();
    }
}