#ifndef GRID_HPP
#define GRID_HPP

#include "CommonUnits.hpp"

class Grid {
public:
    Grid();

    void initialize();

    void Print() const;

    void Draw(threepp::Scene &scene) const;

    int ClearFullRows();


    int cellSize;
    int numRows;
    int numCols;

    std::vector<std::vector<int>> grid;
    const int DEFAULT_CUBE_SIZE = 20;
    const int CUBE_HEIGHT = 1;
    const int EMPTY_CELL = 0;



private:
    [[nodiscard]] bool IsRowFull(int row) const;

    void ClearRow(int row);

    void MoveRowDown(int row, int numRows);


};

#endif // GRID_HPP

