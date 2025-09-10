#pragma once
#include <matplot/matplot.h>


namespace plot {
    void draw(std::vector<std::array<std::array<double, 2>, 3>> triangles, double lower_bound, double upper_bound);
} // namespace plot