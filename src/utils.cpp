#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <spdlog/spdlog.h>
#include "utils.h"
#include "structures.h"

double utils::dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() == 2 && vec2.size() == 2) {
        return vec1[0] * vec2[0] + vec1[1] * vec2[1];
    } else if (vec1.size() == 3 && vec2.size() == 3) {
        return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
    }
    // throw error
}

std::vector<double> utils::cross_product(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    return std::vector<double> {
        vec1[1] * vec2[2] - vec1[2] * vec2[1],
        vec1[2] * vec2[0] - vec1[0] * vec2[2],
        vec1[0] * vec2[1] - vec1[1] * vec2[0]
    };
}

std::vector<double> utils::cross_product_with_normal(const std::vector<double>& vec) {
    // if (vec.size() != 3) {
    //     throw std::runtime_error("Input vector must have 3 components.");
    // }
    return std::vector<double> {
        vec[1],  // -v_y
        -vec[0],  // v_x
         //0.0      // z-компонента всегда 0
    };
}

std::vector<double> utils::vector_by_points(const Point& point1, const Point& point2) {
    return std::vector<double> {point2.get_x() - point1.get_x(), point2.get_y() - point1.get_y()};
}

void utils::print_vector(std::vector<double> vec) {
    for( int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;
}

Point utils::get_centroid(const std::shared_ptr<Triangle>& triangle, const std::vector<Point>& points) {
    double x_c = (
        points[triangle->get_points_indexes()[0]].get_x() +
        points[triangle->get_points_indexes()[1]].get_x() +
        points[triangle->get_points_indexes()[2]].get_x()
    ) / 3;

    double y_c = (
        points[triangle->get_points_indexes()[0]].get_y() +
        points[triangle->get_points_indexes()[1]].get_y() +
        points[triangle->get_points_indexes()[2]].get_y()
    ) / 3;

    return Point(x_c, y_c);
}

void utils::save_to_file(const std::vector<std::array<std::array<double, 2>, 3>>& triangles, const std::string& filename) {
    std::ofstream file(filename);
    file << std::fixed << std::setprecision(6);

    spdlog::info("Запись в файл");
    
    file << "x1,y1,x2,y2,x3,y3\n";

    if (file.is_open()) {
        for (const auto& triangle : triangles) {
            for (int i = 0; i < 3; ++i) {
                file << triangle[i][0]; // x координата
                file << ",";
                file << triangle[i][1]; // y координата
                if (i < 2) file << ","; // Добавляем запятую между точками, но не в конце строки
            }
            file << "\n"; // Новая строка после каждого треугольника
        }
        file.close();
    }
    else {
        file.close();
        throw std::runtime_error("Error: Could not create or open file");
    }
}

void utils::run_vizualization() {
    std::filesystem::path path_to_script = std::filesystem::current_path() / "scripts" / "vizualization.py";

    std::system((std::string("python3 ") + path_to_script.string()).c_str());
}