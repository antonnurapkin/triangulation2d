cmake_minimum_required(VERSION 3.10)
project(triangulation2d)
find_package(spdlog REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем папку src как подпроект
add_subdirectory(src)

# Копируем скрипт для отображения и устанавливаем необходимые python-библиотеки
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/vizualization.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)

find_package(Python REQUIRED COMPONENTS Interpreter)

function(install_python_package package_name)
    execute_process(
        COMMAND ${Python_EXECUTABLE} -m pip install --user ${package_name}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error
    )
    if(NOT result EQUAL 0)
        message(WARNING "Failed to install ${package_name}: ${error}")
    else()
        message(STATUS "Successfully installed ${package_name}")
    endif()
endfunction()

install_python_package(plotly)

# Устанавливаем библиотеки для тестирования
enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Подключаем подпроект с тестами
add_subdirectory(tests)