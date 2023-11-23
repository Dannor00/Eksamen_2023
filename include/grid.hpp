#include "vector"
#include "threepp/threepp.hpp"
#include "../include/colors.hpp"

class Grid {
public:
    Grid();
    void initialize();
    void Print();
    void Draw(threepp::Scene &scene) const;
    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
private:
    int cellSize;
};
