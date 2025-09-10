#include <array>
#include <utility>
#include <matplot/matplot.h>
#include "plot.h"

void plot::draw(std::vector<std::array<std::array<double, 2>, 3>> triangles, double lower_bound, double upper_bound) {
    matplot::plot(matplot::iota(lower_bound, upper_bound));
    std::array<std::pair<int, int>, 3> pairs ={{
        {0, 1}, {1, 2}, {2, 0}
    }};

    for(auto& triangle: triangles) {
        for(auto& pair: pairs) {
            double x1 = triangle[pair.first][0];
            double y1 = triangle[pair.first][1];

            double x2 = triangle[pair.first][0];
            double y2 = triangle[pair.first][1];

            matplot::line(x1, y1, x2, y2);
        }
    }

    matplot::show();
}