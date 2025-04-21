#include <vector>

class Point final {
friend 
private:
    double x;
    double y;
}

class Triangle final {
    std::array<double, 3> indexes; 
    std::vector<Triangle> adjacentTriangles;
}