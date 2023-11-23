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
    void Rotate();
    void Draw(threepp::Scene &scene);
    void Move(int rows, int columns);
    std::map<int, std::vector<Position>> cells;
    std::vector<Position> GetCellPositions();
    std::vector<Position> GetCellPositionsAfterMove(int rows, int columns) const;
    bool IsBlockOutside(const Block &block, int rows, int columns);
    int rowOffset;
    int columnOffset;
    int id;


private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;

};


#endif //EKSAMEN_2023_BLOCK_HPP



