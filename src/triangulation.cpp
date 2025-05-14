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
std::shared_ptr<Triangle> triangulation::find_triangle(const Point& point, const Triangle& cur_triangle, const std::vector<Point>& points) {
    Point center = utils::get_centroid(cur_triangle, points);

    std::vector<double> N1 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle.get_points_indexes()[0]],
            points[cur_triangle.get_points_indexes()[1]]
        )
    );

    std::vector<double> N2 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle.get_points_indexes()[1]],
            points[cur_triangle.get_points_indexes()[2]]
        )
    );

    std::vector<double> N3 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle.get_points_indexes()[2]],
            points[cur_triangle.get_points_indexes()[0]]
        )
    );

    std::vector<double> vec_to_point = utils::vector_by_points(center, point);

    double S1 = utils::dot_product(N1, vec_to_point);
    double S2 = utils::dot_product(N2, vec_to_point);
    double S3 = utils::dot_product(N3, vec_to_point);

    if (S1 > 0 && S1 >= S2 && S1 >= S3) {
        return cur_triangle.get_adjacent(0);
    } else if (S2 > 0 && S2 >= S1 && S2 >= S3) {
        return cur_triangle.get_adjacent(1);
    }
    else if (S3 > 0 && S3 >= S2 && S3 >= S1) {
        return cur_triangle.get_adjacent(2);
    }
}


void triangulation::add_new_triangles(const Point& point, std::shared_ptr<Triangle>& cur_triangle, std::vector<Triangle>& triangles, const std::vector<Point>& points) {
    std::shared_ptr<Triangle> tri_1 = std::make_shared<Triangle>(point, points[cur_triangle->get_index(0)], points[cur_triangle->get_index(1)]);
    std::shared_ptr<Triangle> tri_2 = std::make_shared<Triangle>(point, points[cur_triangle->get_index(1)], points[cur_triangle->get_index(2)]);
    std::shared_ptr<Triangle> tri_3 = std::make_shared<Triangle>(point, points[cur_triangle->get_index(2)], points[cur_triangle->get_index(0)]);

    // TODO: Добавить проверки на соседей
    if (cur_triangle->is_adjacents_exist()) {
        tri_1->add_adjacent(tri_3);
        tri_1->add_adjacent(cur_triangle->get_adjacent(0));
        tri_1->add_adjacent(tri_2);
        update_adjacent_neighbors(tri_1, cur_triangle, points[tri_1->get_index(1)], points[tri_1->get_index(2)], points);

        tri_2->add_adjacent(tri_1);
        tri_2->add_adjacent(cur_triangle->get_adjacent(1));
        tri_2->add_adjacent(tri_3);
        update_adjacent_neighbors(tri_2, cur_triangle, points[tri_2->get_index(1)], points[tri_2->get_index(2)], points);

        tri_3->add_adjacent(tri_2);
        tri_3->add_adjacent(cur_triangle->get_adjacent(2));
        tri_3->add_adjacent(tri_1);
        update_adjacent_neighbors(tri_3, cur_triangle, points[tri_3->get_index(1)], points[tri_3->get_index(2)], points);
    }
}


void triangulation::update_adjacent_neighbors(const std::shared_ptr<Triangle>& new_triangle, std::shared_ptr<Triangle>& parent_triangle, const Point& point_1, const Point& point_2, const std::vector<Point>& points){
    // Данный метод добавляет i-ый новый треугольник в качестве соседа к какому-то соседу cтарого большого треугольника
    const auto& adjacents = parent_triangle->get_all_adjacents();
    
    for (int i = 0; i < adjacents.size(); i++) {

        std::shared_ptr<Triangle> adjacent = adjacents[i];

        std::array<int, 3> ids = adjacent->get_points_indexes();
        std::vector<Point> tri_points;
        for(int j = 0; j < 3; j++) {
            tri_points.push_back(points[ids[j]]);
        }
        
        // Если у нас два треугольника имеют 2 общих точки, то они соседи
        // Тогда i-ый новый треугольник делаем соседом треугольника, который является соседом большого треуголньика
        if (have_common_edge(tri_points, point_1, point_2)) {
            for (int j = 0; j < adjacent->get_all_adjacents().size(); j++) {
                if (adjacent->get_all_adjacents()[j] == parent_triangle) {
                    adjacent->set_adjacent(j, new_triangle);
                }
            }
        }
    }
}


bool triangulation::have_common_edge(const std::vector<Point>& triangle_points, const Point& p1, const Point& p2) {
    return std::find(triangle_points.begin(), triangle_points.end(), p1) != triangle_points.end() &&
        std::find(triangle_points.begin(), triangle_points.end(), p2) != triangle_points.end();
}


bool triangulation::check_delauney_condition(const std::shared_ptr<Triangle>& new_tri, const std::shared_ptr<Triangle>& adjacent, const std::vector<Point>& points) {
    const Point& v2 = get_opposite_vertex(new_tri, adjacent); // opposite vertex os adjacent
    const Point& v0 = points[new_tri->get_index(0)]; // vertex of new triangle
    const Point& v1 = points[new_tri->get_index(1)];
    const Point& v3 = points[new_tri->get_index(2)];

    double cos_a = utils::dot_product(
        utils::vector_by_points(v0, v1),
        utils::vector_by_points(v0, v3)
    );

    double cos_b = utils::dot_product(
        utils::vector_by_points(v2, v1),
        utils::vector_by_points(v2, v3)
    );

    if (cos_a < 0 && cos_b < 0) {
        return false;
    } else if (cos_a >= 0 && cos_b >= 0) {
        return true;
    }
    
    double sin_a = (v0.get_x() - v1.get_x()) * (v0.get_y() - v3.get_y()) - (v0.get_y() - v1.get_y()) * (v0.get_x() - v3.get_x());
    double sin_b = (v2.get_x() - v3.get_x()) * (v2.get_y() - v1.get_y()) - (v2.get_x() - v1.get_x()) * (v2.get_y() - v3.get_y());

    if (sin_a * cos_b + cos_a * sin_b >= 0) {
        return true;
    } else {
        return false;
    }
}