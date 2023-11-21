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
    void Draw(threepp::Scene &scene);
    void Move(int rows, int columns);
    int id;
    std::map<int, std::vector<Position>> cells;
    std::vector<Position> GetCellPositions();

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
    float maxSpeed_;
    threepp::Vector3 size_;
    threepp::Vector3 position_;

};


#endif //EKSAMEN_2023_BLOCK_HPP
