//
// Created by Danie on 24.10.2023.
//

#ifndef EKSAMEN_2023_BLOCK_H
#define EKSAMEN_2023_BLOCK_H
#pragma once
#include "map"
#include "vector"
#include "Position.h"
#include "colors.h"
#include "threepp/threepp.hpp"

class Block {

public:
    Block();
    void Draw(threepp::Scene* scene);
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;


};


#endif //EKSAMEN_2023_BLOCK_H
