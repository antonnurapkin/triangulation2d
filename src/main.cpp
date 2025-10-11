#include <vector>
#include <iostream>
#include <random>
#include <cstdlib>
#include <filesystem>
#include <spdlog/spdlog.h>
#include "triangulation.h"
#include "utils.h"


int main(int args, char** argv) {

    spdlog::set_level(spdlog::level::err);
    
    // // Настройка генератора случайных чисел
    double lower_bound = -10;
    double upper_bound = 10;
    // std::random_device rd;
    std::mt19937 gen(1);
    std::uniform_real_distribution<double> dis(lower_bound, upper_bound); // Диапазон значений

    std::vector<std::array<double, 2>> points;
    points.reserve(60); // Резервируем место для эффективности

    // Заполнение вектора 60 случайными точками
    for (int i = 0; i < 50; ++i) {
        points.push_back({dis(gen), dis(gen)});
    }

    std::vector<std::array<std::array<double, 2>, 3>> result = triangulation::get_triangulation(points);

    std::filesystem::path filename = std::filesystem::current_path() / "scripts" / "triangles.csv";

    utils::save_to_file(result, filename.string());

    utils::run_vizualization();

    return 0;
}