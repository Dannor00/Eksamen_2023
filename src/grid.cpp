#include <iostream>
#include "../include/grid.hpp"

const int DEFAULT_CUBE_SIZE = 20;
const int CUBE_HEIGHT = 1;

Grid::Grid() : numRows(20), numCols(10), cellSize(30) {
    initialize();
}

void Grid::initialize() {
    // Initialize the 2D vector with zeros
    grid.assign(numRows, std::vector<int>(numCols, 0));
}

void Grid::Print() const {
    for (const auto &row: grid) {
        for (int cell: row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw(threepp::Scene &scene) const {
    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;

    // Calculate the center of the grid, taking into account the grid's width
    float centerX = -gridWidth / 2.0;
    float centerY = gridHeight / 2.0;

    // Use a single geometry and material for all cubes
    auto geometry = threepp::BoxGeometry::create(DEFAULT_CUBE_SIZE, DEFAULT_CUBE_SIZE, CUBE_HEIGHT);
    auto material = threepp::MeshBasicMaterial::create();

    // Clear the scene at the beginning of each frame
    // scene.clear();

    // Iterate over the grid and create cubes
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            // Create a mesh using the shared geometry and material
            auto cube = threepp::Mesh::create(geometry, material);

            // Set cube position using CommonUtils functions
            float x = centerX + column * cellSize;
            float y = centerY - row * cellSize;
            float z = 0;
            CommonUtils::SetMeshPosition(cube, x, y, z);

            // Add cube to the scene using CommonUtils function
            CommonUtils::AddMeshToScene(scene, cube);
        }
    }
}

bool Grid::IsRowFull(int row) const {
    for (int column = 0; column < numCols; column++) {
        if (grid[row][column] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (int &cell: grid[row]) {
        // std::cout << "Clearing row " << row << ", column " << &cell - &grid[row][0] << std::endl;
        cell = 0;
    }
}

void Grid::MoveRowDown(int row, int numRowsToMove) {
    for (int column = 0; column < numCols; column++) {
        grid[row + numRowsToMove][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

int Grid::ClearFullRows() {
    int complete = 0;
    for (int row = numRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            complete++;
        } else if (complete > 0) {
            MoveRowDown(row, complete);
        }
    }
    return complete;
}
