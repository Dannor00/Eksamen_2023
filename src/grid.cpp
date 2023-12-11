#include <iostream>
#include "../include/grid.hpp"

Grid::Grid() : numRows(20), numCols(10), cellSize(30) {
    Initialize();
}

void Grid::Initialize() {
    grid.assign(numRows, std::vector<int>(numCols, EMPTY_CELL));
}

void Grid::Print() const {
    for (const auto &row: grid) {
        for (int cell: row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

//Kode Delvis omskrevet av Ai
void Grid::Draw(threepp::Scene &scene) const {
    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;

    // Calculate the center of the grid, taking into account the grid's width
    float gridCenterX = -gridWidth / 2.0;
    float gridCenterY = gridHeight / 2.0;

    // Use a single geometry and material for all cubes
    auto geometry = threepp::BoxGeometry::create(DEFAULT_CUBE_SIZE, DEFAULT_CUBE_SIZE, CUBE_HEIGHT);
    auto material = threepp::MeshBasicMaterial::create();

    // Iterate over the grid and create cubes
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            // Create a mesh using the shared geometry and material
            auto cube = threepp::Mesh::create(geometry, material);

            // Set cube position using CommonUtils functions
            float x = gridCenterX + column * cellSize;
            float y = gridCenterY - row * cellSize;
            float z = 0;
            CommonUtils::SetMeshPosition(cube, x, y, z);

            // Add cube to the scene using CommonUtils function
            CommonUtils::AddMeshToScene(scene, cube);
        }
    }
}

//
bool Grid::IsRowFull(int row) const {
    for (int column = 0; column < numCols; column++) {
        if (grid[row][column] == EMPTY_CELL) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (int &cell: grid[row]) {
        cell = EMPTY_CELL;
    }
}

void Grid::MoveRowDown(int row, int numRowsToMove) {
    for (int column = 0; column < numCols; column++) {
        grid[row + numRowsToMove][column] = grid[row][column];
        grid[row][column] = EMPTY_CELL;
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

int Grid::GetNumRows() const {
    return numRows;
}

int Grid::GetNumCols() const {
    return numCols;
}

int Grid::GetCellValue(int row, int col) const {
    return grid[row][col];
}
