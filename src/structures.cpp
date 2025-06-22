#include <algorithm>
#include "structures.h"


Point::Point(double x, double y) : x_(x), y_(y) {};


Triangle::Triangle(std::array<int, 3> indexes, std::vector<std::shared_ptr<Triangle>> adjacentTriangles) :
	indexes_(indexes), adjacentTriangles_(adjacentTriangles) {};

Triangle::Triangle(std::array<int, 3> indexes) : indexes_(indexes) {};


Triangle::Triangle(int index1, int index2, int index3) {
    indexes_ = std::array<int, 3> {{index1, index2, index3}};
}

Triangle::Triangle(const Triangle& other) {
    adjacentTriangles_ = other.adjacentTriangles_;
    indexes_ = other.indexes_;
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (&other != this) {
        adjacentTriangles_ = other.adjacentTriangles_;
        indexes_ = other.indexes_;
    }
    return *this;
}

Triangle::Triangle(Triangle&& moved) {
    adjacentTriangles_ = std::move(moved.adjacentTriangles_);
    indexes_ = moved.indexes_;

    moved.indexes_.fill(0);
}

std::set<std::pair<int, int>> Triangle::get_edges() const {
    std::set<std::pair<int, int>> result;
    for (int i = 0; i < 3; ++i) {
        int a = this->get_point_index(i);
        int b = this->get_point_index((i + 1) % 3);
        result.insert(std::minmax(a, b));
    }
    return result;
}

int Triangle::get_index_of_adjacent(std::shared_ptr<Triangle> adj) {
    for (int i = 0; i < get_all_adjacents().size(); i++) {
        if (get_adjacent(i) == adj) {
            return i;
        }
    }
}