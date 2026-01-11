#include "utils.h"

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "structures.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

double utils::dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() == 2 && vec2.size() == 2) {
        return vec1[0] * vec2[0] + vec1[1] * vec2[1];
    } else if (vec1.size() == 3 && vec2.size() == 3) {
        return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
    }
    // throw error
}

std::vector<double> utils::cross_product(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    return std::vector<double>{vec1[1] * vec2[2] - vec1[2] * vec2[1], vec1[2] * vec2[0] - vec1[0] * vec2[2], vec1[0] * vec2[1] - vec1[1] * vec2[0]};
}

std::vector<double> utils::cross_product_with_normal(const std::vector<double>& vec) {
    return std::vector<double>{
        vec[1],   // -v_y
        -vec[0],  // v_x
                  // 0.0      // z-компонента всегда 0
    };
}

std::vector<double> utils::vector_by_points(const Point& point1, const Point& point2) {
    return std::vector<double>{point2.get_x() - point1.get_x(), point2.get_y() - point1.get_y()};
}

void utils::print_vector(std::vector<double> vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;
}

Point utils::get_centroid(const std::shared_ptr<Triangle>& triangle, const std::vector<Point>& points) {
    double x_c = (points[triangle->get_points_indexes()[0]].get_x() + points[triangle->get_points_indexes()[1]].get_x() +
                  points[triangle->get_points_indexes()[2]].get_x()) /
                 3;

    double y_c = (points[triangle->get_points_indexes()[0]].get_y() + points[triangle->get_points_indexes()[1]].get_y() +
                  points[triangle->get_points_indexes()[2]].get_y()) /
                 3;

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
                file << triangle[i][0];  // x координата
                file << ",";
                file << triangle[i][1];  // y координата
                if (i < 2) file << ",";  // Добавляем запятую между точками, но не в конце строки
            }
            file << "\n";  // Новая строка после каждого треугольника
        }
        file.close();
    } else {
        file.close();
        throw std::runtime_error("Error: Could not create or open file");
    }
}

std::vector<std::array<double, 2>> utils::read_from_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Error: Could not create or open file");
    }

    std::vector<std::array<double, 2>> points;

    std::string line;

    while (std::getline(file, line, '\n')) {
        points.push_back(get_point(line, ","));
    }

    return points;
}

void utils::run_vizualization(std::filesystem::path path_to_traingles) {
    std::filesystem::path path_to_script = std::filesystem::absolute(get_executable_path().parent_path()) / "vizualization.py";

    std::system((std::string("python3 ") + path_to_script.string() + std::string(" --file ") + path_to_traingles.string()).c_str());
}

std::array<double, 2> utils::get_point(std::string& s, const std::string& delimiter) {
    std::array<double, 2> coords;
    size_t pos = 0;

    pos = s.find(delimiter);
    double x_coord = std::stod(s.substr(0, pos));

    s.erase(0, pos + delimiter.length());
    double y_coord = std::stod(s);

    coords[0] = x_coord;
    coords[1] = y_coord;

    return coords;
}

int utils::check_launch_flag(int args, char** argv, const std::string& name, int default_value) {
    for (int i = 1; i < args; i++) {
        if (std::string(argv[i]) == "--" + name) {
            if (i + 1 < args) {
                try {
                    int value = std::stoi(std::string(argv[i + 1]));
                    return value;
                } catch (const std::exception& e) {
                    std::cerr << "Error converting '" << argv[i + 1] << "' to int for flag -" << name << std::endl;
                    return default_value;
                }
            }
            break;
        }
    }
    return default_value;
}

std::string utils::check_launch_flag(int args, char** argv, const std::string& name, std::string default_value) {
    for (int i = 1; i < args; i++) {
        if (std::string(argv[i]) == "--" + name) {
            if (i + 1 < args) {
                return std::string(argv[i + 1]);
            }
            break;
        }
    }
    return default_value;
}

std::filesystem::path utils::get_executable_path() {
    return std::filesystem::canonical("/proc/self/exe");
}