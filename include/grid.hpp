#include "vector"
#include "threepp/threepp.hpp"
#include "../include/colors.hpp"

class Grid {
public:
    Grid();

    void initialize();

    void Print();

    void Draw(threepp::Scene &scene);

    int ClearFullRows();
    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int NumRows);
    int cellSize;

};
