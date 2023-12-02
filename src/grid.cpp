#include "iostream"
#include "../include/grid.hpp"


Grid::Grid() {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    initialize();
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
    float centerX = -gridWidth / 2.0;
    float centerY = gridHeight / 2.0;

    // Use a single geometry and material for all cubes
    auto geometry = threepp::BoxGeometry::create(20, 20, 1);
    auto material = threepp::MeshBasicMaterial::create();

    // Clear the scene at the beginning of each frame
    scene.clear();

    // Iterate over the grid and create cubes
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];

            // Create a mesh using the shared geometry and material
            auto cube = threepp::Mesh::create(geometry, material);

            // Set cube position
            float x = centerX + column * cellSize;
            float y = centerY - row * cellSize;
            float z = 0;
            cube->position.set(x, y, z);

            // Add cube to the scene
            scene.add(cube);
        }
    }
;}

bool Grid::IsRowFull(int row) {
    for(int column = 0; column < numCols; column++)
    {
        if(grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for(int column = 0; column < numCols; column++)
    {
        std::cout << "Clearing row " << row << ", column " << column << std::endl;
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int NumRows) {
    for (int column = 0; column < numCols; column++) {
        grid[row + NumRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}





int Grid::ClearFullRows() {
    int complete = 0;
    for (int row = numRows-1; row>=0; row--)
    {
        if(IsRowFull(row))
        {
            ClearRow(row);
            complete++;
        }
        else if (complete >0)
        {
            MoveRowDown(row, complete);
        }
    }
    return complete;
}

