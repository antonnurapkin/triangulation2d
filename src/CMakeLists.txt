
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
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})