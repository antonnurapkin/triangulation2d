#include <vector>
#include "triangulation.h"
#include "structures.h"
#include "utils.h"

using vectorTriangles = std::vector<std::array<std::array<double>>>;

/* vectorTriangles get_triangulation(std::vector<std::array<double>>& points) {
    ...
} */ 

// TODO: Расчёт вектора на основе двух точек
bool triangulation::is_inside_triangle(const Triangle& triangle, const Point& point, const ) {
    std::vector<double> normal {0, 0, 1};

    std::vector<double> N1 = cross_product(
        std::vector<double> {points[triangle.indexes_[0], triangle.indexes_[1]},
        normal;
    );
}


