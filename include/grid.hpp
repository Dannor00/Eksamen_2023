#ifndef GRID_HPP
#define GRID_HPP

#include "CommonUnits.hpp"

class Grid {
public:
    Grid();

    void Initialize();

    void Print() const;

    void Draw(threepp::Scene &scene) const;

    int ClearFullRows();

    [[nodiscard]] int GetNumRows() const;

    [[nodiscard]] int GetNumCols() const;

    [[nodiscard]] int GetCellValue(int row, int col) const;

    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
private:
    [[nodiscard]] bool IsRowFull(int row) const;

    void ClearRow(int row);

    void MoveRowDown(int row, int numRows);

    const int DEFAULT_CUBE_SIZE = 20;
    const int CUBE_HEIGHT = 1;
    const int EMPTY_CELL = 0;

    int cellSize;

};

#endif // GRID_HPP
