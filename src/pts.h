#pragma once
// Alexander Bass
//  Created 4/19/24
// Modified 4/19/24
#include "point.h"
#include <istream>
#include <string>
#include <vector>

namespace pts {
    std::vector<Point> load_pts(std::istream &);
    std::vector<Point> load_pts_from_path(std::string);
}