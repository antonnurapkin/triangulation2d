#pragma once
#include <vector>
#include <array>
#include <memory>

class Point final {
public:
    Point(double x, double y);

    double get_x() const { return x_; }
    double get_y() const { return y_; }

private:
    double x_;
    double y_;
};

class Triangle final {
public:
    Triangle(std::array<int, 3> indexes, std::vector<std::shared_ptr<Triangle>> adjacentTriangles);
    Triangle(std::array<int, 3> indexes);

    std::array<int, 3> get_points_indexes() const {return indexes_; }
    int get_index(int index) {return indexes_[index]; }

    bool is_adjacents_exist() const {return true ? adjacentTriangles_.size() > 0 : false;}

    std::shared_ptr<Triangle> get_adjacent(int index) const {return adjacentTriangles_[index]; }

    void add_adjacent(const shared_prt<Triangle>& adjacent) {adjacentTriangles_.push_back(adjacent);}

    void set_adjacent(int index, const shared_prt<Triangle>& adjacent) {adjacentTriangles_[index] = adjacent;}

    std::vector<std::shared_ptr<Triangle>> get_all_adjacents() {return adjacentTriangles_;}
    
private:
    std::array<int, 3> indexes_; 
    std::vector<std::shared_ptr<Triangle>> adjacentTriangles_;
};