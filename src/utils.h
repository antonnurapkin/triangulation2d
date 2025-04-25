#pragma once
#include <vector>
#include "structures.h"

namespace utils {
    double dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2);

    std::vector<double> cross_product(const std::vector<double>& vec1, const std::vector<double>& vec2);

    std::vector<double> vector_by_points(const Point& point1, const Point& point2);
} // namespace utils