#pragma once
#include <vector>
#include <array>
#include <memory>

class Point final {
public:
    Point(double x, double y);

    double get_x() const { return x_; }
    double get_y() const { return y_; }

private:
    double x_;
    double y_;
};

class Triangle final {
public:
    Triangle(std::array<int, 3> indexes, std::vector<std::shared_ptr<Triangle>> adjacentTriangles);
    Triangle(std::array<int, 3> indexes);

    std::array<int, 3> get_points_indexes() const {return indexes_; }
private:
    std::array<int, 3> indexes_; 
    std::vector<std::shared_ptr<Triangle>> adjacentTriangles_;
};