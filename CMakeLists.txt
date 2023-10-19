cmake_minimum_required(VERSION 3.15)
project(Eksamen_2023)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Tetris
        main.cpp
        grid.cpp
        grid.h
        grid.cpp
)

target_link_libraries(Tetris
        PRIVATE threepp::threepp
        PRIVATE imgui::imgui)
