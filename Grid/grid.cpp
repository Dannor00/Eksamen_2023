
//
// Created by Danie on 12.10.2023.
//
#include "threepp/threepp.hpp"
#include "grid.h"
#include "iostream"
#include "colors.h"


Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    initialize();
    colors = GetCellColors();
}

void Grid::initialize() {
    for (int row = 0; row < numRows; row++)
    {
        for (int colum = 0; colum < numCols; colum++)
        {
            grid[row][colum] =0;
        }

    }
}
void Grid::Print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int colum =0; colum < numCols; colum++)
        {
            std::cout << grid[row][colum] <<" ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw(threepp::Scene* scene) {
    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;

    // Calculate the center of the grid
    float centerX = -gridWidth / 2.0;
    float centerY = gridHeight / 2.0;

    int column;
    for (int row = 0; row < numRows; row++) {
        for (column = 0; column < numCols; column++) {
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

            scene->add(cube);
        }
    }
}
