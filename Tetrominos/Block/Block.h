//
// Created by Danie on 24.10.2023.
//

#ifndef EKSAMEN_2023_BLOCK_H
#define EKSAMEN_2023_BLOCK_H
#pragma once
#include "map"
#include "vector"
#include "../Position/Position.h"

class Block {

public:
    Block();
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize;
    int rotationState;

};


#endif //EKSAMEN_2023_BLOCK_H
