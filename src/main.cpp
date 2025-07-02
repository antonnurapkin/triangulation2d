#include <vector>
#include <iostream>
#include "triangulation.h"


int main() {
    std::vector<std::array<double, 2>> points = {
        {0, 0},
        {1, 1},
        {0, 1},
        {1, 0},
        {0.1, 0.5},
        {0.7, 0.5},
        {0.5, 0.9},
        {-0.5, 0.5}
    };

    std::vector<std::array<std::array<double, 2>, 3>> result = triangulation::get_triangulation(points);

    for (const auto& tri : result) {
        for (const auto& point : tri) {
            if (-10 < point[0] < 10 && -10 < point[1] < 10) {
                std::cout << "( " << point[0] << ", " << point[1] << " ), ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}