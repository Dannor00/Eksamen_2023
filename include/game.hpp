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



    void Reset();

    bool gameOver = false;



    std::vector<Block *> dirtyBlocks;


    // Helper function to mark a block as dirty
    void MarkBlockDirty(Block *block) {
        dirtyBlocks.push_back(block);
    }

    static std::vector<Block> GetAllBlocks() {
        return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    }

    void MoveBlock(int i, int i1);

    void RedrawLockedBlocks(threepp::Scene &scene) const;

private:
    struct LockedBlock {


        explicit LockedBlock(Position position);

        Position position;
    };

    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    std::random_device rd;
    std::mt19937 gen;
    static constexpr float BlockFallInterval = 1.0f;
    float elapsedSinceLastFall = 0.0f;
    CollisionManager collisionManager;
    std::vector<std::shared_ptr<LockedBlock>> lockedBlocks;


    void MoveBlockDown(threepp::Scene &scene);


    [[nodiscard]] bool IsGameOver() const;

    [[nodiscard]] bool IsCollision(const Block &block, int rows, int columns) const;

    void Draw(threepp::Scene &scene);

    void LockBlock(threepp::Scene &scene);
};

#endif // EKSAMEN_2023_GAME_HPP
