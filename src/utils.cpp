#include <vector>
#include <iostream>
#include "utils.h"
#include "structures.h"

double utils::dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() == 2 && vec2.size() == 2) {
        return vec1[0] * vec2[0] + vec1[1] * vec2[1];
    } else if (vec1.size() == 3 && vec2.size() == 3) {
        return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
    }
    // throw error
}

std::vector<double> utils::cross_product(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    return std::vector<double> {
        vec1[1] * vec2[2] - vec1[2] * vec2[1],
        vec1[2] * vec2[0] - vec1[0] * vec2[2],
        vec1[0] * vec2[1] - vec1[1] * vec2[0]
    };
}

std::vector<double> utils::cross_product_with_normal(const std::vector<double>& vec) {
    // if (vec.size() != 3) {
    //     throw std::runtime_error("Input vector must have 3 components.");
    // }
    return std::vector<double> {
        vec[1],  // -v_y
        -vec[0],  // v_x
         //0.0      // z-компонента всегда 0
    };
}

std::vector<double> utils::vector_by_points(const Point& point1, const Point& point2) {
    return std::vector<double> {point2.get_x() - point1.get_x(), point2.get_y() - point1.get_y()};
}

void utils::print_vector(std::vector<double> vec) {
    for( int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;
}

Point utils::get_centroid(const Triangle& triangle, const std::vector<Point>& points) {
    double x_c = (
        points[triangle.get_points_indexes()[0]].get_x() +
        points[triangle.get_points_indexes()[1]].get_x() +
        points[triangle.get_points_indexes()[2]].get_x()
    ) / 3;

    double y_c = (
        points[triangle.get_points_indexes()[0]].get_y() +
        points[triangle.get_points_indexes()[1]].get_y() +
        points[triangle.get_points_indexes()[2]].get_y()
    ) / 3;

    return Point(x_c, y_c);
}