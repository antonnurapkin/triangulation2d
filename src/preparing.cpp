#include <algorithm>
#include <preparing.h>

std::unordered_map<std::string, double> preparing::get_bounds(const std::vector<std::array<double, 2>>& points) {
    std::unordered_map<std::string, double> bounds = {
        {"x_max", points[0][0]},
        {"x_min", points[0][0]},
        {"y_max", points[0][1]},
        {"y_min", points[0][1]}
    };

    for (size_t i = 1; i < points.size(); i++) {
        if (points[i][0] > bounds["x_max"]) {
            bounds["x_max"] = points[i][0];
        } else if (points[i][0] < bounds["x_min"]) {
            bounds["x_min"] = points[i][0];
        }
        if (points[i][1] > bounds["y_max"]) {
            bounds["y_max"] = points[i][1];
        } else if (points[i][1] < bounds["y_min"]) {
            bounds["y_min"] = points[i][1];
        }
    }

    return bounds;
}


std::vector<Point> preparing::normalize_coords(const std::vector<std::array<double, 2>>& points, const std::unordered_map<std::string, double>& bounds) {
    std::vector<Point> result;
    result.reserve(points.size());

    double delta_max = std::max(bounds.at("x_max") - bounds.at("x_min"), bounds.at("y_max") - bounds.at("y_min"));
    
    for (const auto& p : points) {
        double norm_x = (p[0] - bounds.at("x_min")) / delta_max;
        double norm_y = (p[1] - bounds.at("y_min")) / delta_max;
        result.emplace_back(norm_x, norm_y);
    }

    return result;
}