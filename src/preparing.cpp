#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include "preparing.h"
#include "structures.h"

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


std::shared_ptr<Triangle> preparing::create_super_triangle(std::vector<Point>& points) {
    // Добавление вершин супер-треугольника
    points.emplace_back(2, 100);
    points.emplace_back(100, -100);
    points.emplace_back(-100, -100);

    int size = points.size();

    return std::make_shared<Triangle>(std::array<int, 3> {size - 1, size - 2, size - 3});
}

std::vector<int> preparing::bin_sort(std::vector<Point>& points, const std::unordered_map<std::string, double>& bounds) {
    std::vector<int> bins;
    bins.reserve(points.size());

    int n_bins = sqrt(sqrt(points.size()));

    for (const Point& point: points ) {
        int i = static_cast<int>(point.get_y() * n_bins * 0.99 / bounds.at("y_max"));
        int j = static_cast<int>(point.get_x() * n_bins * 0.99 / bounds.at("x_max"));

        if ( i % 2 == 0) {
            bins.push_back(i * n_bins + j + 1);
        } else {
            bins.push_back( (i + 1) * n_bins - j);
        }
    }

    return bins;
}

void preparing::quick_sort(std::vector<int>& bins, std::vector<Point>& points, int start, int end) {
    if (start < end) {
        int pivot = bins[end];
    
        int j = start - 1;
    
        for(int i = start; i < end; i++) {
            if (bins[i] <= pivot) {
                j++;
                std::swap(bins[i], bins[j]);
                std::swap(points[i], points[j]);
            }
        }
    
        std::swap(bins[j + 1], bins[end]);
        std::swap(points[j + 1], points[end]);
    
        quick_sort(bins, points, start, j);
        quick_sort(bins, points, j + 2, end);
    }
}