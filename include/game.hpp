#ifndef EKSAMEN_2023_GAME_HPP
#define EKSAMEN_2023_GAME_HPP

#include <random>
#include <memory>
#include "grid.hpp"
#include "../src/blocks.cpp"
#include "ColisionManager.hpp"

class Game {
public:
    Game();

    std::shared_ptr<Block> GetRandomBlock();

    void Update(threepp::Scene &scene, float deltaTime);

    void RotateBlock();

    void UpdateScore(int linesCleared, int moveDownPoints);

    int score;
    Grid grid;

    void Reset();

    bool gameOver = false;

    std::vector<std::shared_ptr<Block>> dirtyBlocks;

    // Helper function to mark a block as dirty
    void MarkBlockDirty(std::shared_ptr<Block> block) {
        dirtyBlocks.push_back(block);
    }

    static std::vector<std::shared_ptr<Block>> GetAllBlocks() {
        return {std::make_shared<IBlock>(), std::make_shared<JBlock>(), std::make_shared<LBlock>(),
                std::make_shared<OBlock>(), std::make_shared<SBlock>(), std::make_shared<TBlock>(),
                std::make_shared<ZBlock>()};
    }

    void MoveBlock(int rows, int columns);

    void RedrawLockedBlocks(threepp::Scene &scene) const;

private:
    struct LockedBlock {
        explicit LockedBlock(Position position);

        Position position;
    };

    std::vector<std::shared_ptr<Block>> blocks;
    std::shared_ptr<Block> currentBlock;
    std::shared_ptr<Block> nextBlock;
    std::random_device rd;
    std::mt19937 gen;
    static constexpr float BlockFallInterval = 1.0f;
    float elapsedSinceLastFall = 0.0f;
    CollisionManager collisionManager;
    std::vector<std::shared_ptr<LockedBlock>> lockedBlocks;

    void MoveBlockDown(threepp::Scene &scene);

    [[nodiscard]] bool IsGameOver() const;

    [[nodiscard]] bool IsCollision(const Block &block) const;

    void Draw(threepp::Scene &scene);

    void LockBlock(threepp::Scene &scene);
};

#endif // EKSAMEN_2023_GAME_HPP
