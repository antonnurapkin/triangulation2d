#include <vector>
#include <iostream>
#include <memory>
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

    // TODO: Сделать вектор указателей
    std::vector<Triangle> triangles;

    std::unordered_map<std::string, double> bounds = preparing::get_bounds(points);

    std::vector<Point> normalized_points = preparing::normalize_coords(points, bounds);

    std::vector<int> bins = preparing::bin_sort(normalized_points, bounds);

    preparing::quick_sort(bins, normalized_points, 0, bins.size());

    triangles.push_back(preparing::create_super_triangle(normalized_points));

    Triangle current_triangle = triangles[0];

    for (const Point& point: normalized_points) {
        //std::cout << point.get_x() << " " << point.get_y() << " " << is_inside_triangle(triangles[0], point, normalized_points) << std::endl;

        // if (is_inside_triangle(current_triangle, point, normalized_points)) {
        //     ...
        // } else {
        //    shared_prt<Trinagle> current_triangle = find_triangle(point, current_triangle, trinagles, points);
        // }

    }
}

// TODO: Доступ через указатель
bool triangulation::is_inside_triangle(const Triangle& triangle, const Point& point, const std::vector<Point>& points) {

    const Point& A = points[triangle.get_points_indexes()[0]];
    const Point& B = points[triangle.get_points_indexes()[1]];
    const Point& C = points[triangle.get_points_indexes()[2]];

    auto calculate_area = [](const Point& p1, const Point& p2, const Point& p3) -> double {
        return 0.5 * std::abs(
            p1.get_x() * (p2.get_y() - p3.get_y()) +
            p2.get_x() * (p3.get_y() - p1.get_y()) +
            p3.get_x() * (p1.get_y() - p2.get_y())
        );
    };

    double S_ABC = calculate_area(A, B, C);

    double S_PAB = calculate_area(point, A, B);
    double S_PBC = calculate_area(point, B, C);
    double S_PCA = calculate_area(point, C, A);

    double S_total = S_PAB + S_PBC + S_PCA;

    double tolerance = 0.0001;

    if (std::abs(S_total - S_ABC) < tolerance) {
        return true;
    }

    // // Если точка лежит на границе треугольника (одна из площадей равна нулю)
    // if (S_PAB < tolerance || S_PBC < tolerance || S_PCA < tolerance) {
    //     return true;
    // }

    // В остальных случаях точка лежит снаружи
    return false;
}

// TODO: Доступ через указатель
shared_ptr<Triangle> find_triangle(const Point& point, const Triangle& cur_triangle,  std::vector<Triangle>& trinagles, const std::vector<Point>& points) {
    Point center = utils::get_centroid(cur_triangle, points);

    std::vector<double> N1 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle.get_points_indexes()[0]],
            points[cur_triangle.get_points_indexes()[1]]
        )
    )

    std::vector<double> N2 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle.get_points_indexes()[1]],
            points[cur_triangle.get_points_indexes()[2]]
        )
    )

    std::vector<double> N3 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle.get_points_indexes()[2]],
            points[cur_triangle.get_points_indexes()[0]]
        )
    )

    std::vector<double> vec_to_point = utils::vector_by_points(center, point);

    double S1 = utils::dot_product(N1, vec_to_point);
    double S2 = utils::dot_product(N2, vec_to_point);
    double S3 = utils::dot_product(N3, vec_to_point);

    if (S1 > 0 && S1 >= S2 && S1 >= S3) {
        return *(triangle.get_adjacent(0));
    } else if (S2 > 0 && S2 >= S1 && S2 >= S3) {
        return *(triangle.get_adjacent(1));
    } else if (S3 > 0 && S3 >= S2 && S3 >= S1) {
        return *(triangle.get_adjacent(2));
}
