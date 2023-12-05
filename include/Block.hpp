#ifndef EKSAMEN_2023_BLOCK_HPP
#define EKSAMEN_2023_BLOCK_HPP
#pragma once

#include "map"
#include "vector"
#include "Position.hpp"
#include "colors.hpp"
#include "threepp/threepp.hpp"

class Block {
public:
    Block();
    void Draw(threepp::Scene &scene, int offsetX, int offsetY);
    void Move(int rows, int columns);
    int id;
    std::map<int, std::vector<Position>> cells;
    std::vector<Position> GetCellPositions();
    std::vector<Position> GetCellPositionsAfterMove(int rows, int columns) const;
    bool IsBlockOutside(const Block& block, int rows, int columns);
    void DrawAtPosition(threepp::Scene &scene, const Position &position);
    int rowOffset;
    int columnOffset;

    void Rotate();

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;

};

#endif //EKSAMEN_2023_BLOCK_HPP


