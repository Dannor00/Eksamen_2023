
//
// Created by Danie on 12.10.2023.
//
#include "threepp/threepp.hpp"
#include "grid.h"
#include "iostream"


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
std::vector<Color> Grid::GetCellColors()
{
    Color grey = {Color::grey};
    Color green = {Color::green};
    Color red = {Color::red};
    Color orange = {Color::orange};
    Color yellow = {Color::yellow};
    Color purple = {Color::purple};
    Color cyan = {Color::cyan};
    Color blue ={Color::blue};

    return {grey, green, red, orange, yellow, purple, cyan, blue};
}
void Grid::Draw(threepp::Scene* scene) {
    int column; // Declare column outside of the loop
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

            // Set the position of the cube
            cube->position.x = column * cellSize + 1;
            cube->position.y = row * cellSize + 1;

            scene->add(cube);
        }
    }
    auto sceneGrid = GridHelper::create(10);
    scene->add(sceneGrid);

}