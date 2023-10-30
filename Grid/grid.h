//
// Created by Danie on 09.10.2023.
//

#ifndef EKSAMEN_2023_GRID_H
#define EKSAMEN_2023_GRID_H
#pragma once
#include "vector"
#include "threepp/threepp.hpp"

using namespace threepp;

class Grid
{
public:
    Grid();
    void initialize();
    void Print();
    void Draw(threepp::Scene* scene);
    int grid[20][10];

private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};

#endif //EKSAMEN_2023_GRID_H
