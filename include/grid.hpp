#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <vector>
#include "threepp/threepp.hpp"
#include "../include/colors.hpp"

class Grid {
public:
    Grid();

    void initialize();

    void Print() const;

    void Draw(threepp::Scene &scene) const;

    int ClearFullRows();

    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
    int cellSize;

private:
    [[nodiscard]] bool IsRowFull(int row) const;

    void ClearRow(int row);

    void MoveRowDown(int row, int numRows);


};

#endif // GRID_HPP

