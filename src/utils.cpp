#include <vector>
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
