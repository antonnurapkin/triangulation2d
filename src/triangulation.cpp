#include <vector>
#include <iostream>
#include "triangulation.h"
#include "preparing.h"
#include "structures.h"
#include "utils.h"

using vectorTriangles = std::vector<std::array<double, 3>>;

void triangulation::get_triangulation(std::vector<std::array<double, 2>>& points) {

    // TODO: Добавить обработку пустого вектора
    // if (points.empty()) {
    //     throw error
    // }

    std::vector<Triangle> triangles;

    std::unordered_map<std::string, double> bounds = preparing::get_bounds(points);

    std::vector<Point> normalized_points = preparing::normalize_coords(points, bounds);

    triangles.push_back(preparing::create_super_triangle(normalized_points));

    std::vector<int> bins = preparing::bin_sort(normalized_points, bounds);

    preparing::quick_sort(bins, normalized_points, 0, bins.size());

    normalized_points.emplace_back(1000,1000);

    for (const Point& point: normalized_points) {
        std::cout << is_inside_triangle(triangles[0], point, normalized_points) << std::endl;
    }
}

// TODO: Расчёт вектора на основе двух точек
bool triangulation::is_inside_triangle(const Triangle& triangle, const Point& point, const std::vector<Point>& points) {
    std::vector<double> normal {0, 0, 1};

    std::vector<double> N1 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[triangle.get_points_indexes()[0]], 
            points[triangle.get_points_indexes()[1]]
        )
    );

    std::vector<double> N2 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[triangle.get_points_indexes()[1]], 
            points[triangle.get_points_indexes()[2]]
        )
    );

    std::vector<double> N3 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[triangle.get_points_indexes()[0]], 
            points[triangle.get_points_indexes()[2]]
        )
    );

    std::cout << points[triangle.get_points_indexes()[0]].get_x() << " " << points[triangle.get_points_indexes()[0]].get_y() << std::endl;
    std::cout << points[triangle.get_points_indexes()[1]].get_x() << " " << points[triangle.get_points_indexes()[1]].get_y() << std::endl;
    std::cout << points[triangle.get_points_indexes()[2]].get_x() << " " << points[triangle.get_points_indexes()[2]].get_y() << std::endl;

    if (
        utils::dot_product(N1, utils::vector_by_points(point, points[triangle.get_points_indexes()[0]])) >= 0 &&
        utils::dot_product(N2, utils::vector_by_points(point, points[triangle.get_points_indexes()[1]])) >= 0 &&
        utils::dot_product(N3, utils::vector_by_points(point, points[triangle.get_points_indexes()[2]])) >= 0
    ) {
        return true;
    } else {
        return false;
    }
}


