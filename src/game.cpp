#include <algorithm>
#include "../include/game.hpp"

Game::Game() : grid(Grid()), rd(), gen(rd()) {
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }

    std::uniform_int_distribution<std::size_t> dist(0, blocks.size() - 1);
    std::size_t randomIndex = dist(gen);


    auto iter = blocks.begin() + static_cast<std::ptrdiff_t>(randomIndex);
    Block block = *iter;
    blocks.erase(iter);

    return block;
}


void Game::Update(threepp::Scene &scene, float deltaTime) {
    if (gameOver) {
        // Game is over, do not update anything
        return;
    }

    elapsedSinceLastFall += deltaTime;

    // Function to handle block movement
    auto moveBlock = [this](int rows, int columns) {
        if (!IsCollision(currentBlock, rows, columns)) {
            currentBlock.Move(rows, columns);
            markBlockDirty(&currentBlock);
        }
    };

    if (elapsedSinceLastFall >= blockFallInterval) {
        elapsedSinceLastFall = 0.0f;

        // Attempt to move the block down
        if (!IsCollision(currentBlock, 1, 0)) {
            moveBlock(1, 0);
        } else {
            // Lock the block if it cannot move down
            LockBlock(scene);

            // Check for game over condition after locking the block
            if (IsGameOver()) {
                gameOver = true;
                return;
            }
        }
    }

    // Check other movements and rotations
    moveBlock(-1, 0);
    moveBlock(0, -1);
    moveBlock(0, 1);
    moveBlock(1, 0);

    // Draw the updated elements
    Draw(scene);
    markBlockDirty(&currentBlock);

}

void Game::Draw(threepp::Scene &scene) {
    if (gameOver) {
        // Game is over, do not draw anything
        return;
    }

    // Clear the scene before rendering
    scene.clear();

    // Redraw only the dirty Tetris blocks
    for (const auto &block: dirtyBlocks) {
        block->Draw(scene, 0, 0);
    }

    // Optionally, redraw other static elements that don't change frequently
    grid.Draw(scene);
    nextBlock.Draw(scene, 300, -300);

    // Clear the list of dirty Tetris blocks for the next frame
    dirtyBlocks.clear();
}


bool Game::IsGameOver() {
    // Check if the current block is outside the top two rows of the grid
    return IsBlockOutside(currentBlock);
}


bool Game::IsCollision(const Block &block, int rows, int columns) {
    const auto &cellPositions = block.GetCellPositionsAfterMove(rows, columns);

    return std::any_of(cellPositions.begin(), cellPositions.end(),
                       [this](const Position &newPos) {
                           return newPos.row < 0 || newPos.column < 0 ||
                                  newPos.row >= grid.numRows || newPos.column >= grid.numCols ||
                                  grid.grid[newPos.row][newPos.column] != 0;
                       });
}



void Game::moveCurrentBlock(int rows, int columns) {
    currentBlock.Move(rows, columns);
}

void Game::RotateBlock() {
    currentBlock.Rotate();
}

void Game::LockBlock(threepp::Scene &scene) {
    const std::vector<Position> blockPositions = currentBlock.GetCellPositions();

    for (const auto &pos: blockPositions) {
        int lockedRow = pos.row;
        int lockedColumn = pos.column;
        grid.grid[lockedRow][lockedColumn] = currentBlock.id;

        lockedBlocks.emplace_back(Position(0, 0));
        lockedBlocks.back().position = pos;
    }

    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    int clearedRows = grid.ClearFullRows();
    UpdateScore(clearedRows, 0);

    lockedBlocks.erase(std::remove_if(lockedBlocks.begin(), lockedBlocks.end(),
                                      [clearedRows](const LockedBlock &lockedBlock) {
                                          return lockedBlock.position.row < clearedRows;
                                      }), lockedBlocks.end());

    for (auto &lockedBlock: lockedBlocks) {
        if (lockedBlock.position.row >= clearedRows) {
            lockedBlock.position.row -= clearedRows;
        }
    }

    RedrawLockedBlocks(scene);
}


void Game::RedrawLockedBlocks(threepp::Scene &scene) {
    const std::vector<Block> blockTypes = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};

    for (int row = 0; row < grid.numRows; ++row) {
        for (int col = 0; col < grid.numCols; ++col) {
            int blockId = grid.grid[row][col];

            if (blockId != 0 && static_cast<std::size_t>(blockId - 1) < blockTypes.size()) {
                Position blockPosition(row, col);
                blockTypes[blockId - 1].DrawAtPosition(scene, blockPosition);
            }
        }
    }
}


Game::LockedBlock::LockedBlock(Position position) : position(position) {
}


bool Game::IsBlockOutside(const Block &block) {
    const std::vector<Position> newPositions = block.GetCellPositionsAfterMove(0, 0);

    return std::any_of(newPositions.begin(), newPositions.end(), [this](const Position &newPos) {
        return newPos.row < 0 || newPos.row >= grid.numRows || newPos.column < 0 || newPos.column >= grid.numCols ||
               grid.grid[newPos.row][newPos.column] != 0;
    });
}

void Game::Reset() {
    grid.initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}


void Game::UpdateScore(int linesCleared, int moveDownPoints) {
    constexpr int scoreValues[] = {0, 100, 300, 500};

    if (linesCleared >= 1 && linesCleared <= 3) {
        score += scoreValues[linesCleared];
    }

    score += moveDownPoints;
}


