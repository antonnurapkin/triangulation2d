add_executable(
    triangulation2d 
    main.cpp
)

target_sources(
    triangulation2d
    PUBLIC preparing.cpp
    PUBLIC utils.cpp
    PUBLIC structures.cpp
    PUBLIC triangulation.cpp
    PUBLIC plot.cpp
)

target_link_libraries(triangulation2d spdlog::spdlog Matplot++::matplot)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})