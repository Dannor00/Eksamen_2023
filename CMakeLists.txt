cmake_minimum_required(VERSION 3.15)
project(Tetris_2023 VERSION 1.0)  # Updated project name

option(TERRIS_BUILD_TESTS "Enable Tetris function testing" ON)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Tetris
        main.cpp
        src/grid.cpp
        src/Block.cpp
        src/colors.cpp
        src/blocks.cpp
        src/game.cpp
        include/Keylistner.hpp
        include/CalculateTime.hpp
        src/Position.cpp
        include/CommonUnits.hpp
)

target_link_libraries(Tetris
        PRIVATE threepp::threepp
        PRIVATE imgui::imgui
        PRIVATE TetrisLib
        PRIVATE TetrisLibInclude
)

add_subdirectory(src)
add_subdirectory(include)

# ============================
# Testing
# ============================
if (TERRIS_BUILD_TESTS)
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
