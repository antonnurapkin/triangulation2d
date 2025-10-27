#include <vector>
#include <iostream>
#include <random>
#include <cstdlib>
#include <filesystem>
#include <spdlog/spdlog.h>
#include "triangulation.h"
#include "utils.h"


int main(int args, char** argv) {
    int vizualization = utils::check_launch_flag(args, argv, "vizualization", 1);
    std::string path_to_points = utils::check_launch_flag(args, argv, "input", "points.csv");
    std::string path_to_triangles = utils::check_launch_flag(args, argv, "output", "triangles.csv");

    std::vector<std::array<double, 2>> points = utils::read_from_file(path_to_points);

    std::vector<std::array<std::array<double, 2>, 3>> result = triangulation::get_triangulation(points);

    std::filesystem::path absolute_path_to_triangles = std::filesystem::absolute(path_to_triangles);

    utils::save_to_file(result, absolute_path_to_triangles.string());

    if (vizualization) {
        utils::run_vizualization(absolute_path_to_triangles);
    }

    return 0;
}