#ifndef EKSAMEN_2023_GAME_HPP
#define EKSAMEN_2023_GAME_HPP

#pragma once

#include <random>
#include "grid.hpp"
#include "../src/blocks.cpp"
#include "threepp/threepp.hpp"

class Game {
public:
    Game();
    Block GetRandomBlock();
    static std::vector<Block> GetAllBlocks();
    void Update(threepp::Scene &scene, float deltaTime);
    void Draw(threepp::Scene &scene);
    void moveCurrentBlock(int rows, int columns);
    void RotateBlock();




    Grid grid;

    void RedrawLockedBlocks(threepp::Scene &scene);

private:
    struct LockedBlock {
        LockedBlock(Position position);

        int blockId;
        Position position;

        // Getter function for the position
        Position getPosition() const {
            return position;
        }
    };
    bool IsBlockOutside(const Block &block, int rows, int columns);
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    std::vector<LockedBlock> lockedBlocks;  // Added to store locked blocks
    std::random_device rd;
    std::mt19937 gen;
    const float blockFallInterval = 1.0f;
    float elapsedSinceLastFall = 0.0f;



    bool IsCollision(const Block &block, int rows, int columns);

    void LockBlock(threepp::Scene &scene);

};

#endif // EKSAMEN_2023_GAME_HPP
