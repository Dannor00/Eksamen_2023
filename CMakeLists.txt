cmake_minimum_required(VERSION 3.15)
project(Eksamen_2023)

option(TERRIS_BUILD_TESTS "Tetris funksjonstesting" ON)

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
        game/game.cpp
)

target_link_libraries(Tetris
        PRIVATE threepp::threepp
        PRIVATE imgui::imgui)

target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Grid")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/Block")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/colors")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/Position")
target_include_directories(Tetris PRIVATE "${CMAKE_SOURCE_DIR}/Tetrominos/Block/blocks")

# ============================
# Testing
# ============================
if (TERRIS_BUILD_TESTS)

# Download Catch2 unit-test framework from GitHub
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_subdirectory(tests)

endif ()