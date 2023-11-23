#include "../include/game.hpp"


Game::Game() : grid(Grid()), rd(), gen(rd()) {
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }

    std::uniform_int_distribution<int> dist(0, blocks.size() - 1);
    int randomIndex = dist(gen);

    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Update(threepp::Scene &scene) {
    if (!IsBlockOutside(currentBlock, -1, 0) && !IsCollision(currentBlock, -1, 0)) {
        currentBlock.Move(-1, 0);
    }

    if (!IsBlockOutside(currentBlock, 0, -1) && !IsCollision(currentBlock, 0, -1)) {
        currentBlock.Move(0, -1);
    }

    if (!IsBlockOutside(currentBlock, 0, 1) && !IsCollision(currentBlock, 0, 1)) {
        currentBlock.Move(0, 1);
    }

    if (!IsBlockOutside(currentBlock, 1, 0) && !IsCollision(currentBlock, 1, 0)) {
        currentBlock.Move(1, 0);
    }

    currentBlock.Draw(scene);
}

void Game::Draw(threepp::Scene &scene) {
    grid.Draw(scene);
    currentBlock.Draw(scene);
}

bool Game::IsCollision(const Block &block, int rows, int columns) {
    return false;
}

bool Game::IsBlockOutside(const Block& block, int rows, int columns) {
    std::vector<Position> newPositions = block.GetCellPositionsAfterMove(rows, columns);

    // Check if any of the new positions are outside the grid boundaries
    for (const auto& newPos : newPositions) {
        // Allow blocks to reach the topmost position of the grid
        if (newPos.row < 0) {
            continue; // Allow block to move to the top
        }

        // Allow blocks to reach the leftmost position of the grid
        if (newPos.column < 0) {
            continue; // Allow block to move to the left
        }

        if (newPos.row >= grid.numRows || newPos.column >= grid.numCols) {
            return true; // Collision with right or bottom boundary
        }

        if (grid.grid[newPos.row][newPos.column] != 0) {
            return true; // Collision with existing occupied cell in the grid
        }
    }

    return false; // Block is within the grid
}

void Game::moveCurrentBlock(int rows, int columns) {
    currentBlock.Move(rows, columns);
}

void Game::RotateBlock() {
    currentBlock.Rotate();
}