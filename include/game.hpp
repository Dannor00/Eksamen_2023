#ifndef EKSAMEN_2023_GAME_HPP
#define EKSAMEN_2023_GAME_HPP

#include <random>
#include <vector>
#include <iostream>
#include "grid.hpp"
#include "../src/blocks.cpp"
#include "threepp/threepp.hpp"

class Game {
public:
    Game();

    Block GetRandomBlock();

    void Update(threepp::Scene &scene, float deltaTime);

    void moveCurrentBlock(int rows, int columns);

    void RotateBlock();

    void UpdateScore(int linesCleared, int moveDownPoints);

    int score;
    Grid grid;

    void RedrawLockedBlocks(threepp::Scene &scene);


    void Reset();

    bool gameOver = false;

    void Draw(threepp::Scene &scene);

    static std::vector<Block> GetAllBlocks() {
        return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    }

private:
    struct LockedBlock {
        explicit LockedBlock(Position position);
        Position position;
    };

    bool IsBlockOutside(const Block &block);

    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    std::vector<LockedBlock> lockedBlocks;
    std::random_device rd;
    std::mt19937 gen;
    const float blockFallInterval = 1.0f;
    float elapsedSinceLastFall = 0.0f;


    bool IsCollision(const Block &block, int rows, int columns);

    void LockBlock(threepp::Scene &scene);

    bool IsGameOver();


};

#endif // EKSAMEN_2023_GAME_HPP
