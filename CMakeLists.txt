cmake_minimum_required(VERSION 3.15)
project(Eksamen_2023)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Tetris
        main.cpp
        Grid/grid.cpp
        Tetrominos/Block/Block.cpp
        Tetrominos/Position/Position.cpp
        Tetrominos/colors/colors.cpp
        Tetrominos/Block/blocks/blocks.cpp
        Tetrominos/Block/Block.h
        Tetrominos/colors/colors.h
        Tetrominos/Position/Position.h
)

target_link_libraries(Tetris
        PRIVATE threepp::threepp
        PRIVATE imgui::imgui)

target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Grid")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/Block")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/colors")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/Position")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/Block/blocks")
