#ifndef EKSAMEN_2023_GAME_HPP
#define EKSAMEN_2023_GAME_HPP

#include <random>
#include "grid.hpp"
#include "../src/blocks.cpp"
#include "ColisionManager.hpp"


class Game {
public:
    Game();

    Block GetRandomBlock();

    void Update(threepp::Scene &scene, float deltaTime);

    void RotateBlock();

    void UpdateScore(int linesCleared, int moveDownPoints);

    int score;
    Grid grid;

    void RedrawLockedBlocks(threepp::Scene &scene);


    void Reset();

    bool gameOver = false;

    void Draw(threepp::Scene &scene);

    std::vector<Block *> dirtyBlocks;


    // Helper function to mark a block as dirty
    void MarkBlockDirty(Block *block) {
        dirtyBlocks.push_back(block);
    }

    static std::vector<Block> GetAllBlocks() {
        return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    }

    void MoveBlock(int i, int i1);

private:
    struct LockedBlock {


        explicit LockedBlock(Position position);

        Position position;
    };

    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    std::vector<LockedBlock> lockedBlocks;
    std::random_device rd;
    std::mt19937 gen;
    const float blockFallInterval = 1.0f;
    float elapsedSinceLastFall = 0.0f;
    CollisionManager collisionManager;

    bool IsCollision(const Block &block, int rows, int columns);


    void LockBlock(threepp::Scene &scene);

    bool IsGameOver();


    void MoveBlockDown(threepp::Scene &scene);


};

#endif // EKSAMEN_2023_GAME_HPP
