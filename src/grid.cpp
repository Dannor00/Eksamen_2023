#include "iostream"
#include "../include/grid.hpp"
#include "../include/colors.hpp"


Grid::Grid() {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    initialize();
    colors = GetCellColors();
}

void Grid::initialize() {
    // Initialize the 2D vector with zeros
    grid.assign(numRows, std::vector<int>(numCols, 0));
}

void Grid::Print() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw(threepp::Scene &scene) {
    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;

    // Calculate the center of the grid, taking into account the grid's width
    // Calculate the center of the grid
    float centerX = -gridWidth / 2.0;
    float centerY = gridHeight / 2.0;

    // Clear the scene at the beginning of each frame
    scene.clear();

    // Bruk en smart peker til å administrere Mesh-objektene
    std::vector<std::shared_ptr<Mesh>> cubes;

    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];

            // Create a cube geometry to represent the grid cell
            auto geometry = BoxGeometry::create(20, 20, 1);

            // Create a material with the color from your color vector
            auto material = MeshBasicMaterial::create();
            material->color = colors[cellValue];

            // Create a mesh using the geometry and material
            auto cube = Mesh::create(geometry, material);

            // Calculate the cube's position
            float x = centerX + column * cellSize;
            float y = centerY - row * cellSize; // Negative Y because Y-axis in 3D space is typically inverted
            float z = 0;

            cube->position.x = x;
            cube->position.y = y;
            cube->position.z = z;

            cubes.push_back(cube);
        }
    }

    // Legg til alle Mesh-objektene til scenen
    for (const auto &cube: cubes) {
        scene.add(cube);
    }
}

