#include "vector"
#include "threepp/threepp.hpp"
#include "../include/colors.hpp"

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
};
