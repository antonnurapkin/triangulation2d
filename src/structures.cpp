#include <algorithm>
#include "structures.h"


Point::Point(double x, double y) : x_(x), y_(y) {};


Triangle::Triangle(std::array<int, 3> indexes, std::vector<std::shared_ptr<Triangle>> adjacentTriangles) :
	indexes_(indexes), adjacentTriangles_(adjacentTriangles) {};

Triangle::Triangle(std::array<int, 3> indexes) : indexes_(indexes) {};

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