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
    std::string path_to_points_file = utils::check_launch_flag(args, argv, "input", "points.csv");

    std::vector<std::array<double, 2>> points = utils::read_from_file(path_to_points_file);

    std::vector<std::array<std::array<double, 2>, 3>> result = triangulation::get_triangulation(points);

    std::filesystem::path path_to_triangles_file = std::filesystem::current_path() / "scripts" / "triangles.csv";

    utils::save_to_file(result, path_to_triangles_file.string());

    if (vizualization) {
        utils::run_vizualization();
    }

    return 0;
}