#include <iostream>
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

void Game::Update(threepp::Scene &scene, float deltaTime) {
    if (gameOver) {
        // Game is over, do not update anything
        return;
    }

    elapsedSinceLastFall += deltaTime;

    if (elapsedSinceLastFall >= blockFallInterval) {
        elapsedSinceLastFall = 0.0f;

        if (!IsCollision(currentBlock, 1, 0)) {
            currentBlock.Move(1, 0);
        } else {
            std::cout << "Attempting to lock the block." << std::endl;
            LockBlock(scene);
            elapsedSinceLastFall = 0.0f;

            // Check for game over condition after locking the block
            if (IsGameOver()) {
                std::cout << "Game Over!" << std::endl;
                gameOver = true;
                return;
            }
        }
    }

    if (!IsCollision(currentBlock, -1, 0)) {
        currentBlock.Move(-1, 0);
    }

    if (!IsCollision(currentBlock, 0, -1)) {
        currentBlock.Move(0, -1);
    }

    if (!IsCollision(currentBlock, 0, 1)) {
        currentBlock.Move(0, 1);
    }

    if (!IsCollision(currentBlock, 1, 0)) {
        currentBlock.Move(1, 0);
    }

    currentBlock.Draw(scene);
}


void Game::Draw(threepp::Scene &scene) {
    if (gameOver) {
        // Game is over, do not draw anything
        return;
    }

    grid.Draw(scene);
    currentBlock.Draw(scene);
}

bool Game::IsGameOver() {
    // Check if the current block is outside the top two rows of the grid
    return IsBlockOutside(currentBlock, 0, 0);
}

bool Game::IsCollision(const Block &block, int rows, int columns) {
    std::vector<Position> newPositions = block.GetCellPositionsAfterMove(rows, columns);

    for (const auto &newPos : newPositions) {
        if (newPos.row < 0) {
            continue;
        }
        if (newPos.column < 0) {
            continue;
        }
        if (newPos.row >= grid.numRows || newPos.column >= grid.numCols) {
            return true;
        }
        if (grid.grid[newPos.row][newPos.column] != 0) {
            return true;
        }
    }
    return false;
}

void Game::moveCurrentBlock(int rows, int columns) {
    currentBlock.Move(rows, columns);
}

void Game::RotateBlock() {
    currentBlock.Rotate();
}

void Game::LockBlock(threepp::Scene &scene) {
    std::vector<Position> blockPositions = currentBlock.GetCellPositions();

    for (const auto &pos : blockPositions) {
        int lockedRow = pos.row;
        int lockedColumn = pos.column;
        grid.grid[lockedRow][lockedColumn] = currentBlock.id;

        LockedBlock lockedBlock(Position(0, 0));
        lockedBlock.blockId = currentBlock.id;
        lockedBlock.position = pos;
        lockedBlocks.push_back(lockedBlock);
    }

    currentBlock = GetRandomBlock();

    int clearedRows = grid.ClearFullRows();

    std::cout << "Grid after clearing " << clearedRows << " row(s):" << std::endl;
    grid.Print();

    lockedBlocks.erase(std::remove_if(lockedBlocks.begin(), lockedBlocks.end(),
                                      [clearedRows](const LockedBlock &lockedBlock) {
                                          return lockedBlock.position.row < clearedRows;
                                      }), lockedBlocks.end());

    for (auto &lockedBlock : lockedBlocks) {
        if (lockedBlock.position.row >= clearedRows) {
            lockedBlock.position.row -= clearedRows;
        }
    }

    RedrawLockedBlocks(scene);
}

void Game::RedrawLockedBlocks(threepp::Scene &scene) {
    std::vector<Block> blockTypes = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};

    for (int row = 0; row < grid.numRows; ++row) {
        for (int col = 0; col < grid.numCols; ++col) {
            int blockId = grid.grid[row][col];

            if (blockId != 0 && blockId <= blockTypes.size()) {
                Position blockPosition(row, col);
                blockTypes[blockId - 1].DrawAtPosition(scene, blockPosition);
            }
        }
    }
}

Game::LockedBlock::LockedBlock(Position position) : position(position) {
}

bool Game::IsBlockOutside(const Block &block, int rows, int columns) {
    std::vector<Position> newPositions = block.GetCellPositionsAfterMove(rows, columns);

    for (const auto &newPos : newPositions) {
        if (newPos.row < 0 || newPos.row >= grid.numRows) {
            return true;
        }
        if (newPos.column < 0 || newPos.column >= grid.numCols) {
            return true;
        }
        if (grid.grid[newPos.row][newPos.column] != 0) {
            return true;
        }
    }
    return false;
}
