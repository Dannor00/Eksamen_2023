cmake_minimum_required(VERSION 3.15)
project(Eksamen_2023)

option(TERRIS_BUILD_TESTS "Enable Tetris function testing" ON)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Tetris
        main.cpp
        src/grid.cpp
        src/Block.cpp
        src/Position.cpp
        src/colors.cpp
        src/blocks.cpp
        src/game.cpp
)

target_link_libraries(Tetris
        PRIVATE threepp::threepp
        PRIVATE imgui::imgui
)

add_subdirectory(src)

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