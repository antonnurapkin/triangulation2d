#pragma once
#include <vector>
#include "structures.h"

namespace triangulation {
    // std::vector<std::array<double, 3>> get_triangulation(std::vector<std::array<double, 2>>& points);
    void get_triangulation(std::vector<std::array<double, 2>>& points);

    bool is_inside_triangle(const Triangle& triangle, const Point& point, const std::vector<Point>& points);

    Triangle find_triangle(const Point& point, const std::vector<Triangle>& trinagles);
} // namespace triangulation