cmake_minimum_required(VERSION 3.10)
project(triangulation2d)
find_package(spdlog REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем папку src как подпроект
add_subdirectory(src)

# По умолчанию визуализация выключена
option(VIZUALIZATION "Enable Python visualization support" OFF)

if (VIZUALIZATION)
    configure_file(scripts/vizualization.py "${CMAKE_CURRENT_BINARY_DIR}/src/vizualization.py" COPYONLY)

    execute_process(pip3 install uv)
    execute_process(uv add plotly)
endif()
