#include <vector>


using vectorTriangles = std::vector<std::array<std::array<double>>>

namespace triangulation {
    vectorTriangles get_triangulation(std::vector<std::array<double>>& points);
} namespace triangulation