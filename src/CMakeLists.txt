# List source files in the 'src' directory
set(SRC_FILES
        grid.cpp
        Block.cpp
        colors.cpp
        blocks.cpp
        game.cpp
        Position.cpp
)

# Add the source files to the library
add_library(TetrisLib STATIC
        ${SRC_FILES}
)

# Include directories for the library
target_include_directories(TetrisLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link against threepp library if it's used in the source files
target_link_libraries(TetrisLib PUBLIC
        threepp::threepp  # Replace with the actual target name for linking against threepp
)
