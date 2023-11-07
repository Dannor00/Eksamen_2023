//
// Created by Danie on 01.11.2023.
//

#ifndef EKSAMEN_2023_GAME_H
#define EKSAMEN_2023_GAME_H
#pragma once
#include "grid.h"
#include "blocks/blocks.cpp"

class Game{

public:
    Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw(threepp::Scene*scene);
    Grid grid;

private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};




#endif //EKSAMEN_2023_GAME_H
