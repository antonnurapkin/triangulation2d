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

    std::vector<Point> normilized_points = preparing::normalize_coords(points, bounds);

    triangles.push_back(preparing::create_super_triangle(normilized_points));

    std::vector<int> bins = preparing::bin_sort(normilized_points, bounds);

    preparing::quick_sort(bins, normilized_points, 0, bins.size());
}

// TODO: Расчёт вектора на основе двух точек
bool triangulation::is_inside_triangle(const Triangle& triangle, const Point& point, const std::vector<Point>& points) {
    std::vector<double> normal {0, 0, 1};

    std::vector<double> N1 = utils::cross_product(
        utils::vector_by_points(
            points[triangle.get_points_indexes()[0]], 
            points[triangle.get_points_indexes()[1]]
        ),
        normal
    );

    std::vector<double> N2 = utils::cross_product(
        utils::vector_by_points(
            points[triangle.get_points_indexes()[1]], 
            points[triangle.get_points_indexes()[2]]
        ),
        normal
    );

    std::vector<double> N3 = utils::cross_product(
        utils::vector_by_points(
            points[triangle.get_points_indexes()[2]], 
            points[triangle.get_points_indexes()[0]]
        ),
        normal
    );

    if (
        utils::dot_product(N1, utils::vector_by_points(point, points[triangle.get_points_indexes()[0]])) >= 0 &&
        utils::dot_product(N1, utils::vector_by_points(point, points[triangle.get_points_indexes()[1]])) >= 0 &&
        utils::dot_product(N1, utils::vector_by_points(point, points[triangle.get_points_indexes()[2]])) >= 0
    ) {
        return true;
    } else {
        return false;
    }
}


