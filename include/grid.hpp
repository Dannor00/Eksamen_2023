#ifndef EKSAMEN_2023_GRID_H
#define EKSAMEN_2023_GRID_H

#include <vector>
#include "threepp/threepp.hpp"

using namespace threepp;

class Grid {
public:
    Grid();

    void initialize();

    void Print();

    void Draw(threepp::Scene &scene);

private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<std::vector<int>> grid;  // 2D vector to replace C array
    std::vector<Color> colors;
};

#endif // EKSAMEN_2023_GRID_H
