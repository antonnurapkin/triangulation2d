#pragma once
#include <vector>
#include "structures.h"

namespace utils {
    double dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2);

    std::vector<double> cross_product(const std::vector<double>& vec1, const std::vector<double>& vec2);

    std::vector<double> vector_by_points(const Point& point1, const Point& point2);

    void print_vector(std::vector<double> vec);

    std::vector<double> cross_product_with_normal(const std::vector<double>& vec);

    Point get_centroid(const std::shared_ptr<Triangle>& triangle, const std::vector<Point>& points); // Центр треугольника

    void save_to_file(std::vector<std::array<std::array<double, 2>, 3>> triangles, const std::string filename = "triangles.csv");
} // namespace utils