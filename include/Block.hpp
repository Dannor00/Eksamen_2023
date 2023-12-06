#ifndef EKSAMEN_2023_BLOCK_HPP
#define EKSAMEN_2023_BLOCK_HPP

#include "CommonUnits.hpp"

class Block {
public:
    Block();

    ~Block() = default;

    void Draw(threepp::Scene &scene, int offsetX, int offsetY);

    void Move(int rows, int columns);

    void Rotate();

    void DrawAtPosition(threepp::Scene &scene, const Position &position);

    void CreateWhiteBox(threepp::Scene &scene, const Position &position, float customWidth, float customHeight,
                        float customDepth) const;

    [[nodiscard]] std::vector<Position> GetCellPositions() const;

    [[nodiscard]] std::vector<Position> GetCellPositionsAfterMove(int rows, int columns) const;

    int cellSize;
    int rotationState;
    int id;
    int rowOffset;
    int columnOffset;
    std::vector<threepp::Color> colors;
    std::map<int, std::vector<Position>> cells;

private:


    static std::vector<Position> AdjustPositionsWithOffset(const std::vector<Position> &positions, int rowOffset,
                                                           int columnOffset);


    // Constants for block dimensions
    static const int BLOCK_WIDTH_FACTOR = 10;
    static const int BLOCK_HEIGHT_FACTOR = 20;


};

#endif //EKSAMEN_2023_BLOCK_HPP
