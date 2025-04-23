#include "structures.h"

Triangle::Triangle(std::array<int, 3> indexes, std::vector<std::shared_ptr<Triangle>> adjacentTriangles) :
indexes_(indexes), adjacentTriangles_(adjacentTriangles) {};

Triangle::Triangle(std::array<int, 3> indexes) : indexes_(indexes) {};


Point::Point(double x, double y) : x_(x), y_(y) {};