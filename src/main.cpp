#include <vector>
#include <iostream>
#include "triangulation.h"


int main() {
    std::vector<std::array<double, 2>> points = {
        {1, 2},
        {4, 7},
        {0, 5},
        {7, 1}
    };

    std::vector<std::array<std::array<double, 2>, 3>> result = triangulation::get_triangulation(points);

    for (const auto& tri : result) {
        for (const auto& point : tri) {
            if (-10 < point[0] < 10 && -10 < point[1] < 10) {
                std::cout << "x: " << point[0] << " y: " << point[1] << ", ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}