cmake_minimum_required(VERSION 3.10)
project(triangulation2d)
find_package(spdlog REQUIRED)
find_package(Matplot++ REQUIRED)

set(CMAKE_BUILD_TYPE ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем папку src как подпроект
add_subdirectory(src)