#pragma once
#include <unordered_map>
#include <string>
#include "structures.h"


namespace preparing {

    std::unordered_map<std::string, double> get_bounds(const std::vector<std::array<double, 2>>& points); 

    std::vector<Point> normalize_coords(const std::vector<std::array<double, 2>>& points, const std::unordered_map<std::string, double>& bounds);

    Triangle create_super_triangle(std::vector<Point>& points);

    std::vector<int> bin_sort(std::vector<Point>& points, const std::unordered_map<std::string, double>& bounds);

    void quick_sort(std::vector<int>& bins, std::vector<Point>& points, int start, int end);
} // namespace preparing