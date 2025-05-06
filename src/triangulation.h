#pragma once
#include <vector>
#include <memory>
#include "structures.h"

namespace triangulation {
    // std::vector<std::array<double, 3>> get_triangulation(std::vector<std::array<double, 2>>& points);
    void get_triangulation(std::vector<std::array<double, 2>>& points);

    bool is_inside_triangle(const Triangle& triangle, const Point& point, const std::vector<Point>& points);

    std::shared_ptr<Triangle> find_triangle(const Point& point, const Triangle& cur_triangle, const std::vector<Point>& points);

    void add_new_triangles(const Point& point, std::shared_ptr<Triangle>& cur_triangle, std::vector<Triangle>& triangles, const std::vector<Point>& points);

    void update_adjacent_neighbors(const std::shared_ptr<Triangle>& tri_i, std::shared_ptr<Triangle>& cur_triangle, const Point& point_1, const Point& point_2, const std::vector<Point>& points);

    bool have_common_edge(const std::vector<Point>& triangle_points, const Point& p1, const Point& p2);

    bool check_delauney_condition(const std::shared_ptr<Triangle>& new_tri, const std::shared_ptr<Triangle>& adjacent, const std::vector<Point>& points);

    Point get_opposite_vertex(const std::shared_ptr<Triangle>& known_tri, const std::shared_ptr<Triangle>& unknown_tri);
} // namespace triangulation