#include <unordered_map>
#include <string>
#include "structures.h"


namespace preparing {

    std::unordered_map<std::string, double> get_bounds(const std::vector<<std::array<double, 2>>>& points); 

    std::vector<Point> normalize_coords(std::vector<<std::array<double, 2>>>& points);


} // namespace preparing