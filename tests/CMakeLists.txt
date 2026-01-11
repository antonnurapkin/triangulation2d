add_executable(test_triangulation 
test_triangle.cpp
${CMAKE_SOURCE_DIR}/src/structures.cpp
)

target_link_libraries(test_triangulation 
GTest::gtest_main
)

target_include_directories(test_triangulation PUBLIC ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(test_triangulation)