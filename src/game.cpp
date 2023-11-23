#include "iostream"
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
    std::vector<Position> newPositions = block.GetCellPositionsAfterMove(rows, columns);

    for (const auto &newPos : newPositions) {
        if (newPos.row < 0 || newPos.row >= grid.numRows || newPos.column < 0 || newPos.column >= grid.numCols) {
            return true;
        }

        if (grid.grid[newPos.row][newPos.column] != 0) {
            return true;
        }
    }

    return false;
}

bool Game::IsBlockOutside(const Block &block, int rows, int columns) {
    std::vector<Position> newPositions = block.GetCellPositionsAfterMove(rows, columns);

    for (const auto &newPos : newPositions) {
        if (newPos.row < 0) {
            if (rows == 1) {
                return false;
            }
            return true;
        }

        if (newPos.column < 0) {
            if (columns == -1) {
                return false;
            }
            return true;
        }
    }

    return false;
}

void Game::moveCurrentBlock(int rows, int columns) {
    currentBlock.Move(rows, columns);
}
