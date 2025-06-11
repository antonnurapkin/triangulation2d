#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "structures.h"
#include "unordered_map"


// TODO: ������� ���������� namespace, ����� � ������������ �� ���� ������� � ������ ��������, ����� get_triangulation

namespace triangulation {
    using trianglesArrayLikeDataType = std::vector<std::array<std::array<double, 2>, 3>>;

    // std::vector<std::array<double, 3>> get_triangulation(std::vector<std::array<double, 2>>& points);
    trianglesArrayLikeDataType get_triangulation(std::vector<std::array<double, 2>>& points);

    bool is_inside_triangle(const std::shared_ptr<Triangle>& triangle, const Point& point, const std::vector<Point>& points);

    std::shared_ptr<Triangle> find_triangle(const Point& point, const std::shared_ptr<Triangle>& cur_triangle, const std::vector<Point>& points);

    void add_new_triangles(int index, std::shared_ptr<Triangle>& parent_triangle, std::vector<std::shared_ptr<Triangle>>& triangles, const std::vector<Point>& points);

    void add_external_adjacent(std::shared_ptr<Triangle>& new_tri, std::shared_ptr<Triangle>& parent_tri, const std::vector<Point>& points);

    void update_adjacent_neighbors(const std::shared_ptr<Triangle>& new_triangle, std::shared_ptr<Triangle>& parent_triangle, const Point& point_1, const Point& point_2, const std::vector<Point>& points);

    bool have_common_edge(const std::vector<Point>& triangle_points, const Point& p1, const Point& p2);

    bool have_common_edge(const std::shared_ptr<Triangle>& t1, const std::shared_ptr<Triangle>& t2);

    bool check_delauney_condition(const std::shared_ptr<Triangle>& new_tri, const std::shared_ptr<Triangle>& adjacent, const std::vector<Point>& points);

    int get_opposite_vertex(const std::shared_ptr<Triangle>& known_tri, const std::shared_ptr<Triangle>& unknown_tri); 

    void swap_edge(std::shared_ptr<Triangle>& new_triangle, std::shared_ptr<Triangle>& adjacent, const std::vector<Point>& points);

    void set_new_adjacents(std::shared_ptr<Triangle>& triangle, std::vector<std::shared_ptr<Triangle>>& adjacents, const std::vector<Point>& points);

    trianglesArrayLikeDataType convert_to_array_like(const std::vector<std::shared_ptr<Triangle>>& triangles, const std::vector<Point>& points, const std::unordered_map<std::string, double>& bounds);
} // namespace triangulation