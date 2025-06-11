#pragma once
#include <vector>
#include <set>
#include <array>
#include <memory>

class Point final {
public:
    Point(double x, double y);

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

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
    Triangle(int index1, int index2, int index3);

    Triangle(const Triangle& other);

    Triangle& operator=(const Triangle& other);

    Triangle(Triangle&& moved);

    // for points
    std::array<int, 3> get_points_indexes() const {return indexes_; }

    int get_point_index(int index) const {return indexes_[index]; }

    int set_point_index(int point_index, int place_index) { return indexes_[place_index] == point_index; }

    //for edges
    std::set<std::pair<int, int>> get_edges() const;

    // for adjacents
    bool is_adjacents_exist() const {return true ? adjacentTriangles_.size() > 0 : false;}

    std::shared_ptr<Triangle> get_adjacent(int index) const {return adjacentTriangles_[index]; }

    void add_adjacent(const std::shared_ptr<Triangle>& adjacent) {adjacentTriangles_.push_back(adjacent);}

    void set_adjacent(int index, const std::shared_ptr<Triangle>& adjacent) {adjacentTriangles_[index] = adjacent;}

    std::vector<std::shared_ptr<Triangle>> get_all_adjacents() {return adjacentTriangles_;}

    void clear_adjacents() { adjacentTriangles_.clear(); }
    
private:
    std::array<int, 3> indexes_; 
    std::vector<std::shared_ptr<Triangle>> adjacentTriangles_;
};