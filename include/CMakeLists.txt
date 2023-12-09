# List header files in the 'include' directory
set(INCLUDE_FILES
        Position.hpp
        Keylistner.hpp
        Grid.hpp
        Game.hpp
        CommonUnits.hpp
        colors.hpp
        CalculateTime.hpp
        Block.hpp
)

# Add the header files to the library
add_library(TetrisLibInclude INTERFACE
        ColisionManager.hpp)

# Include directories for the library
target_include_directories(TetrisLibInclude INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link TetrisLib with TetrisLibInclude
target_link_libraries(TetrisLibInclude INTERFACE TetrisLib)
