#pragma once
#include <vector>
#include "structures.h"

namespace triangulation {
    std::vector<std::array<std::array<double>>> get_triangulation(std::vector<std::array<double>>& points);

    bool is_inside_triangle(const Triangle& triangle, const Point& point);
} namespace triangulation