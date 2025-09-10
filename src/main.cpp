#include <spdlog/spdlog.h>
#include <vector>
#include <iostream>
#include <random>
#include "triangulation.h"


int main() {
    spdlog::set_level(spdlog::level::debug);
    
    // Настройка генератора случайных чисел
    std::random_device rd;  // Источник энтропии
    std::mt19937 gen(rd()); // Mersenne Twister генератор
    std::uniform_real_distribution<double> dis(-10.0, 10.0); // Диапазон значений

    // Создание вектора для 60 точек
    std::vector<std::array<double, 2>> points;
    points.reserve(10000); // Резервируем место для эффективности

    // Заполнение вектора 60 случайными точками
    for (int i = 0; i < 5000; ++i) {
        points.push_back({dis(gen), dis(gen)});
    }

    std::vector<std::array<std::array<double, 2>, 3>> result = triangulation::get_triangulation(points);

    for (const auto& tri : result) {
        for (const auto& point : tri) {
            if (-10 < point[0] < 10 && -10 < point[1] < 10) {
                std::cout << "( " << point[0] << ", " << point[1] << " ), ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}