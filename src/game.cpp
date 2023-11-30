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
    // Automatic downward movement based on elapsed time
    elapsedSinceLastFall += deltaTime;

    if (elapsedSinceLastFall >= blockFallInterval) {
        elapsedSinceLastFall = 0.0f;

        // Attempt to move the block down
        if (!IsBlockOutside(currentBlock, 1, 0) && !IsCollision(currentBlock, 1, 0)) {
            currentBlock.Move(1, 0);
        } else {
            // Block cannot move down anymore, lock it in place
            std::cout << "Attempting to lock the block." << std::endl;
            LockBlock(scene);

            // Reset the elapsed time to avoid continuous locking
            elapsedSinceLastFall = 0.0f;
        }
    }

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

    // Draw the game scene
    //std::cout << "Drawing the game scene." << std::endl;
    currentBlock.Draw(scene);
}


void Game::Draw(threepp::Scene &scene) {
    grid.Draw(scene);
    currentBlock.Draw(scene);
}

bool Game::IsCollision(const Block &block, int rows, int columns) {
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
void Game::LockBlock(threepp::Scene &scene) {
    // Get the current position of the block
    std::vector<Position> blockPositions = currentBlock.GetCellPositions();

    // Lock the block in place and add it to the list of locked blocks
    for (const auto &pos : blockPositions) {
        int lockedRow = pos.row;
        int lockedColumn = pos.column;
        grid.grid[lockedRow][lockedColumn] = currentBlock.id;

        // Create a LockedBlock structure and add it to the list
        LockedBlock lockedBlock(Position(0, 0));
        lockedBlock.blockId = currentBlock.id;
        lockedBlock.position = pos;
        lockedBlocks.push_back(lockedBlock);
    }

    // Generate a new block
    currentBlock = GetRandomBlock();

    // Clear full rows in the grid
    int clearedRows = grid.ClearFullRows();

    // Remove cleared rows from lockedBlocks
    lockedBlocks.erase(std::remove_if(lockedBlocks.begin(), lockedBlocks.end(),
                                      [clearedRows](const LockedBlock& lockedBlock) {
                                          return lockedBlock.position.row < clearedRows;
                                      }), lockedBlocks.end());

    // Update the positions of remaining locked blocks
    for (auto& lockedBlock : lockedBlocks) {
        if (lockedBlock.position.row >= clearedRows) {
            lockedBlock.position.row -= clearedRows;
        }
    }

    RedrawLockedBlocks(scene);
}


// Function to redraw the locked blocks
void Game::RedrawLockedBlocks(threepp::Scene &scene) {
    for (const auto &lockedBlock : lockedBlocks) {
        Block lockedBlockType; // Initialize the correct block type based on blockId

        switch (lockedBlock.blockId) {
            case 1:
                lockedBlockType = LBlock();
                break;
            case 2:
                lockedBlockType = JBlock();
                break;
            case 3:
                lockedBlockType = IBlock();
                break;
            case 4:
                lockedBlockType = OBlock();
                break;
            case 5:
                lockedBlockType = SBlock();
                break;
            case 6:
                lockedBlockType = TBlock();
                break;
            case 7:
                lockedBlockType = ZBlock();
                break;
            default:
                // Handle the case for unknown block ID
                break;
        }

        // Draw the block at the specified position
        lockedBlockType.DrawAtPosition(scene, lockedBlock.position);
    }
}



Game::LockedBlock::LockedBlock(Position position) : position(position) {

}
