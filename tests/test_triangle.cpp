#include <memory>

#include "gtest/gtest.h"

#include "structures.h"

class TriangleTest: public ::testing::Test {
    protected: 
        std::shared_ptr<Triangle> triangle = std::make_shared<Triangle>(1, 20, 321);
};

TEST_F(TriangleTest, GetPointIndex) {
    EXPECT_EQ(triangle->get_point_index(0), 1);
    EXPECT_EQ(triangle->get_point_index(1), 20);
    EXPECT_EQ(triangle->get_point_index(2), 321);
}

TEST_F(TriangleTest, SetPointIndex) {
    triangle->set_point_index(100, 0);

    EXPECT_EQ(triangle->get_point_index(0), 100);
}

TEST_F(TriangleTest, IsAdjacentExists) {
    EXPECT_FALSE(triangle->is_adjacents_exist());
}