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
    void Draw(threepp::Scene &scene);
    void Game::moveCurrentBlock(int rows, int columns);
    void Update();
    Grid grid;

private:
    bool IsBlockOutide();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    std::random_device rd;
    std::mt19937 gen;
};

#endif // EKSAMEN_2023_GAME_HPP

