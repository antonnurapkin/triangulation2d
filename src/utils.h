#pragma once
#include <vector>

namespace utils {
    double dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2);

    std::vector<double> cross_product(const std::vector<double>& vec1, const std::vector<double>& vec2);
} // namespace utils