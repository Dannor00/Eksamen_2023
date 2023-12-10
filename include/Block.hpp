#ifndef EKSAMEN_2023_BLOCK_HPP
#define EKSAMEN_2023_BLOCK_HPP

#include "CommonUnits.hpp"

class Block {
public:
    Block();

    ~Block() = default;

    void Draw(threepp::Scene &scene, int offsetX, int offsetY) const;
    void Move(int rows, int columns);
    void Rotate();
    void DrawAtPosition(threepp::Scene &scene, const Position &position) const;
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
    std::vector<std::shared_ptr<threepp::Mesh>> boxes;


private:
    static std::vector<Position> AdjustPositionsWithOffset(const std::vector<Position> &positions, int rowOffset,
                                                           int columnOffset);
    static const int BLOCK_WIDTH_FACTOR = 10;
    static const int BLOCK_HEIGHT_FACTOR = 20;

    std::shared_ptr<threepp::Mesh> DrawBox(threepp::Scene &scene, const Position &item, int offsetX, int offsetY) const;

    std::shared_ptr<threepp::Mesh>
    DrawBoxAtPosition(threepp::Scene &scene, const Position &item, const Position &position) const;
};

#endif // EKSAMEN_2023_BLOCK_HPP