#pragma once
#include <vector>
#include <memory>

class Point final {
friend 
private:
    double x;
    double y;
}

class Triangle final {
    std::array<size_t, 3> indexes; 
    std::vector<std::shared_ptr<Triangle>> adjacentTriangles;
}