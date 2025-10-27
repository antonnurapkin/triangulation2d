#include <spdlog/spdlog.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_set>
#include "triangulation.h"
#include "preparing.h"
#include "structures.h"
#include "utils.h"


triangulation::trianglesArrayLikeDataType triangulation::get_triangulation(std::vector<std::array<double, 2>>& points) {

    // TODO: Добавить обработку пустого вектора
    // if (points.empty()) {
    //     throw error
    // }

    std::vector<std::shared_ptr<Triangle>> triangles;

    std::unordered_map<std::string, double> bounds = preparing::get_bounds(points);

    std::vector<Point> normalized_points = preparing::normalize_coords(points, bounds);

    std::vector<int> bins = preparing::bin_sort(normalized_points, bounds);

    preparing::quick_sort(bins, normalized_points, 0, bins.size() - 1);

    triangles.push_back(preparing::create_super_triangle(normalized_points));

    std::shared_ptr<Triangle> current_triangle = triangles[0];

    // -3 means without super triangles's points
    for (int i = 0; i < normalized_points.size() - 3; i++) {
        spdlog::debug("{}: {} {}", i, normalized_points[i].get_x(), normalized_points[i].get_y());

        spdlog::debug("Поиск необходимого треугольника\n");
        for (const auto& tri : triangles) { // Сделать поиск по треугольникам, а не перебор
            if (is_inside_triangle(tri, normalized_points[i], normalized_points)) {
                current_triangle = tri;
            }
        }

        current_triangle = add_new_triangles(i, current_triangle, triangles, normalized_points);
    }

    remove_supplementary_triangles(triangles, normalized_points);

    return convert_to_array_like(triangles, normalized_points, bounds);
}

bool triangulation::is_inside_triangle(const std::shared_ptr<Triangle>& triangle, const Point& point, const std::vector<Point>& points) {
    
    const Point& A = points[triangle->get_points_indexes()[0]];
    const Point& B = points[triangle->get_points_indexes()[1]];
    const Point& C = points[triangle->get_points_indexes()[2]];

    // Функция для вычисления ориентированной площади
    auto cross_product = [](const Point& p1, const Point& p2, const Point& p3) -> double {
        return (p2.get_x() - p1.get_x()) * (p3.get_y() - p1.get_y()) - 
               (p2.get_y() - p1.get_y()) * (p3.get_x() - p1.get_x());
    };

    // Вычисляем ориентированные площади для трех подтреугольников
    double area1 = cross_product(point, A, B);
    double area2 = cross_product(point, B, C);
    double area3 = cross_product(point, C, A);

    // Проверяем знаки площадей
    bool has_negative = (area1 < 0) || (area2 < 0) || (area3 < 0);
    bool has_positive = (area1 > 0) || (area2 > 0) || (area3 > 0);

    double tolerance = 1e-10;
    
    // Если все площади имеют одинаковый знак (с учетом tolerance) - точка внутри
    // Если одна из площадей близка к нулю - точка на границе
    if (std::abs(area1) < tolerance || std::abs(area2) < tolerance || std::abs(area3) < tolerance) {
        return true; // Точка на границе
    }

    return !(has_negative && has_positive); // Если есть и положительные и отрицательные - точка снаружи
}

// TODO: Доступ через указатель
std::shared_ptr<Triangle> triangulation::find_triangle(const Point& point, const std::shared_ptr<Triangle>& cur_triangle, const std::vector<Point>& points) {
    Point center = utils::get_centroid(cur_triangle, points);

    std::vector<double> N1 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle->get_points_indexes()[0]],
            points[cur_triangle->get_points_indexes()[1]]
        )
    );

    std::vector<double> N2 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle->get_points_indexes()[1]],
            points[cur_triangle->get_points_indexes()[2]]
        )
    );

    std::vector<double> N3 = utils::cross_product_with_normal(
        utils::vector_by_points(
            points[cur_triangle->get_points_indexes()[2]],
            points[cur_triangle->get_points_indexes()[0]]
        )
    );

    std::vector<double> vec_to_point = utils::vector_by_points(center, point);

    double S1 = utils::dot_product(N1, vec_to_point);
    double S2 = utils::dot_product(N2, vec_to_point);
    double S3 = utils::dot_product(N3, vec_to_point);

    if (S1 > 0 && S1 >= S2 && S1 >= S3) {
        return cur_triangle->get_adjacent(0);
    } else if (S2 > 0 && S2 >= S1 && S2 >= S3) {
        return cur_triangle->get_adjacent(2);
    }
    else if (S3 > 0 && S3 >= S2 && S3 >= S1) {
        return cur_triangle->get_adjacent(1);
    }
    return cur_triangle;
}


std::shared_ptr<Triangle> triangulation::add_new_triangles(int index, std::shared_ptr<Triangle>& parent_triangle, std::vector<std::shared_ptr<Triangle>>& triangles, const std::vector<Point>& points) {
    spdlog::info("Добавление нового треугольника");
    std::shared_ptr<Triangle> tri_1 = std::make_shared<Triangle>(index, parent_triangle->get_point_index(0), parent_triangle->get_point_index(1));
    std::shared_ptr<Triangle> tri_2 = std::make_shared<Triangle>(index, parent_triangle->get_point_index(1), parent_triangle->get_point_index(2));
    std::shared_ptr<Triangle> tri_3 = std::make_shared<Triangle>(index, parent_triangle->get_point_index(2), parent_triangle->get_point_index(0));

    tri_1->add_adjacent(tri_3);
    tri_1->add_adjacent(tri_2);

    tri_2->add_adjacent(tri_1);
    tri_2->add_adjacent(tri_3);

    tri_3->add_adjacent(tri_2);
    tri_3->add_adjacent(tri_1);

    std::stack<std::shared_ptr<Triangle>> stack;
    stack.push(tri_1);
    stack.push(tri_2);
    stack.push(tri_3);
    
    if (parent_triangle->is_adjacents_exist()) {
        add_external_adjacent(tri_1, parent_triangle, points);
        add_external_adjacent(tri_2, parent_triangle, points);
        add_external_adjacent(tri_3, parent_triangle, points);
        
    }

    update_trinagulation(stack, points);

    triangles.push_back(tri_1);
    triangles.push_back(tri_2);
    triangles.push_back(tri_3);   

    spdlog::debug("Удаление старого треугольника");
    triangles.erase(
        std::remove_if(
            triangles.begin(), 
            triangles.end(), 
            [&parent_triangle](const std::shared_ptr<Triangle>& tri) { return true ? tri == parent_triangle : false;}
        ),
        triangles.end()
    );

    return tri_1;
}

void triangulation::update_trinagulation(std::stack<std::shared_ptr<Triangle>>& stack, const std::vector<Point>& points) {
    while(!stack.empty()) {
        spdlog::debug("Размер стэка: {}", stack.size());

        std::shared_ptr<Triangle> new_tri = stack.top();
        bool is_swaped = false;
        for (auto& adjacent: new_tri->get_all_adjacents()) {
            if (!check_delauney_condition(new_tri, adjacent, points)) {
                swap_edge(new_tri, adjacent, points);
                stack.push(adjacent);
                is_swaped = true;
            }
        }
        if (!is_swaped) {
            stack.pop();
        }
        
        if (stack.size() > points.size() * 10) {
            throw std::runtime_error("Размер стека превышен");
        }
    }
    spdlog::debug("Триунгуляция обновлена");
}


void triangulation::add_external_adjacent(std::shared_ptr<Triangle>& new_tri, std::shared_ptr<Triangle>& parent_tri, const std::vector<Point>& points) {
    spdlog::debug("Добавление внешнего соседа");
    for (auto& adjacent : parent_tri->get_all_adjacents()) {
        std::vector<Point> vertices = {
                points[adjacent->get_point_index(0)],
                points[adjacent->get_point_index(1)],
                points[adjacent->get_point_index(2)],
        };
        if (have_common_edge(vertices, points[new_tri->get_point_index(1)], points[new_tri->get_point_index(2)])) {
            new_tri->add_adjacent(adjacent);
            update_adjacent_neighbors(new_tri, parent_tri, points[new_tri->get_point_index(1)], points[new_tri->get_point_index(2)], points);
        }
    }
}


void triangulation::update_adjacent_neighbors(const std::shared_ptr<Triangle>& new_triangle, std::shared_ptr<Triangle>& parent_triangle, const Point& point_1, const Point& point_2, const std::vector<Point>& points){
    spdlog::debug("Обновление соседей у треугольников, которые были созданы на предыдущих итерациях");
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


bool triangulation::have_common_edge(const std::shared_ptr<Triangle>& t1, const std::shared_ptr<Triangle>& t2) {
    std::set<std::pair<int, int>> edges1 = t1->get_edges();
    std::set<std::pair<int, int>> edges2 = t2->get_edges();

    for (const auto& e : edges1) {
        if (edges2.count(e)) return true;
    }
    return false;
}

bool triangulation::check_delauney_condition(
    const std::shared_ptr<Triangle>& tri,
    const std::shared_ptr<Triangle>& adj,
    const std::vector<Point>& points) {

    // Находим общее ребро
    auto tri_edges = tri->get_edges();
    auto adj_edges = adj->get_edges();

    std::vector<std::pair<int, int>> common_edges;
    for (const auto& edge : tri_edges) {
        if (adj_edges.find(edge) != adj_edges.end()) {
            common_edges.push_back(edge);
        }
    }

    if (common_edges.empty()) {
        spdlog::debug("Нет общего ребра между треугольниками");
        return true;
    }

    // Общее ребро
    auto common_edge = common_edges[0];
    int v0 = common_edge.first;
    int v1 = common_edge.second;

    // Найдём третью точку в каждом треугольнике (не входящую в ребро)
    std::array<int, 3> tri_indices = tri->get_points_indexes();
    int idx_A = -1, idx_B = -1, idx_C = -1;

    for (int i : tri_indices) {
        if (i != v0 && i != v1) {
            idx_C = i; // Точка, противоположная ребру в первом треугольнике
        }
    }

    std::array<int, 3> adj_indices = adj->get_points_indexes();
    int idx_D = -1;
    for (int i : adj_indices) {
        if (i != v0 && i != v1) {
            idx_D = i; // Точка, противоположная ребру во втором треугольнике
        }
    }

    if (idx_C == -1 || idx_D == -1) {
        spdlog::debug("Не удалось найти противоположные вершины");
        return true;
    }

    const Point& A = points[v0];
    const Point& B = points[v1];
    const Point& C = points[idx_C]; // Третья точка первого треугольника
    const Point& D = points[idx_D]; // Третья точка второго треугольника

    // Проверяем, лежит ли D внутри окружности ABC
    auto in_circle = [](const Point& A, const Point& B, const Point& C, const Point& D) -> bool {
        double ax = A.get_x() - D.get_x();
        double ay = A.get_y() - D.get_y();
        double bx = B.get_x() - D.get_x();
        double by = B.get_y() - D.get_y();
        double cx = C.get_x() - D.get_x();
        double cy = C.get_y() - D.get_y();

        double det = (ax * ax + ay * ay) * (bx * cy - cx * by)
            - (bx * bx + by * by) * (ax * cy - cx * ay)
            + (cx * cx + cy * cy) * (ax * by - bx * ay);

        double orient = (B.get_x() - A.get_x()) * (C.get_y() - A.get_y())
            - (B.get_y() - A.get_y()) * (C.get_x() - A.get_x());

        return (det * orient) > 0;
    };

    return !in_circle(A, B, C, D); // true — условие Делоне выполнено
}

void triangulation::swap_edge(std::shared_ptr<Triangle>& new_triangle, std::shared_ptr<Triangle>& adjacent, const std::vector<Point>& points) {
    spdlog::debug("Смена ребёр между соседними треугольниками");
    int v2_index = get_opposite_vertex(new_triangle, adjacent); // opposite vertex os adjacent
    int v0_index = new_triangle->get_point_index(0); // vertex of new triangle
    int v1_index = new_triangle->get_point_index(1);
    int v3_index = new_triangle->get_point_index(2);

    spdlog::debug("v2: {}, v0: {}, v1: {}, v3: {}", v2_index, v0_index, v1_index, v3_index);

    // This vector will be used as set of all adjacents of the resulting quadrilateral
    std::vector <std::shared_ptr<Triangle>> all_adjacents;

    for (const auto& adj : new_triangle->get_all_adjacents()) {
        if (adj != adjacent) {
            all_adjacents.push_back(adj);
        }
    }
    
    for (const auto& adj : adjacent->get_all_adjacents()) {
        if (adj != new_triangle) {
            all_adjacents.push_back(adj);
        }
    }

    new_triangle->clear_adjacents();
    adjacent->clear_adjacents();

    // create new triangles 
    new_triangle->set_point_index(v0_index, 0);   // this line is unnecassary, but it reeds more clearly
    new_triangle->set_point_index(v2_index, 1);
    new_triangle->set_point_index(v1_index, 2);

    adjacent->set_point_index(v0_index, 0);
    adjacent->set_point_index(v2_index, 1);
    adjacent->set_point_index(v3_index, 2);

    new_triangle->add_adjacent(adjacent);
    adjacent->add_adjacent(new_triangle);

    set_new_adjacents(new_triangle, adjacent, all_adjacents, points);
    set_new_adjacents(adjacent, new_triangle, all_adjacents, points);
}

void triangulation::set_new_adjacents(std::shared_ptr<Triangle>& triangle, std::shared_ptr<Triangle>& other_triangle, std::vector<std::shared_ptr<Triangle>>& adjacents, const std::vector<Point>& points) {
    spdlog::debug("set_new_adjacents() - Установка новых соседей для треугольников, который сменили ребро");
    std::array<std::pair<int, int>, 2> edges = { {
            // {0, 1},  // beacause adjacent for edge with indexes [0, 1] was inserted when the triangle was created
            {0, 2},
            {1, 2}
        }};


    for (auto& adjacent : adjacents) {
        if (have_common_edge(triangle, adjacent)) {
            triangle->add_adjacent(adjacent);

            int index = adjacent->get_index_of_adjacent(triangle);
            spdlog::debug("Индекс соседа: {}", index);

            if (index == -1) { // this means what this adjacent has not triangle as neighbor
                index = adjacent->get_index_of_adjacent(other_triangle);
            }
            spdlog::debug("Индекс соседа после обработки: {}", index);
            adjacent->set_adjacent(index, triangle); // TODO: set new adj to old adjacent's place
        }
    }

}

int triangulation::get_opposite_vertex(const std::shared_ptr<Triangle>& known_tri, const std::shared_ptr<Triangle>& unknown_tri) {
    std::array<int, 3> known_points = known_tri->get_points_indexes(); // known because it was created recently
    std::array<int, 3> unknown_points = unknown_tri->get_points_indexes();

    std::unordered_set<int> known_set(known_points.begin(), known_points.end());

    for (const int idx : unknown_points) {
        if (known_set.find(idx) == known_set.end()) {
            return idx; // Найдена вершина, которой нет в known_tri
        }
    }

    return -1;
}

triangulation::trianglesArrayLikeDataType triangulation::convert_to_array_like(const std::vector<std::shared_ptr<Triangle>>& triangles, const std::vector<Point>& points, const std::unordered_map<std::string, double>& bounds) {
    trianglesArrayLikeDataType tris_array_like;
    tris_array_like.reserve(triangles.size());

    double delta_max = std::max(bounds.at("x_max") - bounds.at("x_min"), bounds.at("y_max") - bounds.at("y_min"));

    for (const auto& tri : triangles) {
        const auto& indexes = tri->get_points_indexes();

        std::array<std::array<double, 2>, 3> triangle_coords;

        for (size_t i = 0; i < 3; ++i) {
            const Point& p = points[indexes[i]];
            triangle_coords[i] = { {p.get_x() * delta_max + bounds.at("x_min"), p.get_y() * delta_max + bounds.at("y_min")}};
        }

        tris_array_like.emplace_back(std::move(triangle_coords));
    }

    return tris_array_like;
}

void triangulation::remove_supplementary_triangles(std::vector<std::shared_ptr<Triangle>>& triangles, const std::vector<Point>& points) {
    triangles.erase(
        std::remove_if(triangles.begin(), triangles.end(),
            [&points](const std::shared_ptr<Triangle>& tri) {
                for (const int id : tri->get_points_indexes()) {
                    if (abs(points[id].get_x()) == 100 || abs(points[id].get_y()) == 100) {
                        return true;
                    }
                }
                return false;
            }),
        triangles.end());
}