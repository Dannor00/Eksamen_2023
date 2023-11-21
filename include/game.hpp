#ifndef EKSAMEN_2023_GAME_HPP
#define EKSAMEN_2023_GAME_HPP

#pragma once

#include <random>
#include "grid.hpp"
#include "../src/blocks.cpp"

class Game {
public:
    Game();

    Block GetRandomBlock();

    static std::vector<Block> GetAllBlocks();

    std::random_device rd;
    std::mt19937 gen;

    void Draw(threepp::Scene &scene);

    Grid grid;

    void Game::moveCurrentBlock(int rows, int columns);

    void Update();


private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};

#endif // EKSAMEN_2023_GAME_HPP

