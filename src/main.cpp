#include <spdlog/spdlog.h>
#include <vector>
#include <iostream>
#include <random>
#include "triangulation.h"
#include "plot.h"


int main(int args, char** argv) {
    spdlog::set_level(spdlog::level::info);
    
    // Настройка генератора случайных чисел
    double lower_bound = -10;
    double upper_bound = 10;
    std::random_device rd;  // Источник энтропии
    std::mt19937 gen(rd()); // Mersenne Twister генератор
    std::uniform_real_distribution<double> dis(lower_bound, upper_bound); // Диапазон значений

    // Создание вектора для 60 точек
    std::vector<std::array<double, 2>> points;
    points.reserve(40); // Резервируем место для эффективности

    // Заполнение вектора 60 случайными точками
    for (int i = 0; i < 30; ++i) {
        points.push_back({dis(gen), dis(gen)});
    }

    std::vector<std::array<std::array<double, 2>, 3>> result = triangulation::get_triangulation(points);

    // for (const auto& tri : result) {
    //     for (const auto& point : tri) {
    //         if (-10 < point[0] < 10 && -10 < point[1] < 10) {
    //             std::cout << "( " << point[0] << ", " << point[1] << " ), ";
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    plot::draw(result, lower_bound, upper_bound);


    return 0;
}