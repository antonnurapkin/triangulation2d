#include <vector>
#include <iostream>
#include "triangulation.h"


int main() {
    std::vector<std::array<double, 2>> points = {
        {1, 2},
        {4, 7},
        {0, 10},
        {7, 1}
    };

    triangulation::get_triangulation(points);

    return 0;
}