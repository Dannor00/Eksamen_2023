#include "vector"
#include "threepp/threepp.hpp"
#include "../include/colors.hpp"

class Grid {
public:
    Grid();

    void initialize();
    void Print();
    void Draw(threepp::Scene &scene);


    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
private:
    int cellSize;
    // 2D vector to replace C array
};
