#include "../include/game.hpp"

Game::Game() : grid(Grid()), rd(), gen(rd()), collisionManager(grid) {
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

//modifisert av Ai
std::shared_ptr<Block> Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }

    std::uniform_int_distribution<std::size_t> dist(0, blocks.size() - 1);
    std::size_t randomIndex = dist(gen);

    auto iter = blocks.begin() + static_cast<std::ptrdiff_t>(randomIndex);
    std::shared_ptr<Block> block = std::make_shared<Block>(**iter);
    blocks.erase(iter);

    return block;
}

//
void Game::Update(threepp::Scene &scene, float deltaTime) {
    if (gameOver) {
        // Game is over, do not update anything
        return;
    }

    elapsedSinceLastFall += deltaTime;

    // Attempt to move the block down
    MoveBlockDown(scene);

    // Check other movements and rotations
    MoveBlock(-1, 0);
    MoveBlock(0, -1);
    MoveBlock(0, 1);
    MoveBlock(1, 0);

    // Draw the updated elements
    Draw(scene);
}

void Game::MoveBlockDown(threepp::Scene &scene) {
    if (elapsedSinceLastFall >= BlockFallInterval) {
        elapsedSinceLastFall = 0.0f;

        // Moving the Block down
        if (!IsCollision(*currentBlock)) {
            MoveBlock(1, 0);
        } else {
            // Lock the block if it cannot move down
            LockBlock(scene);

            // Check for the game over condition after locking the block
            if (IsGameOver()) {
                gameOver = true;
                return;
            }
        }
    }
}

void Game::Draw(threepp::Scene &scene) {
    if (gameOver) {
        // Game is over, do not draw anything
        return;
    }

    // Clear the scene before rendering
    scene.clear();

    // Draw the entire grid
    grid.Draw(scene);

    // Draw the current block
    currentBlock->Draw(scene, 0, 0);

    // Draw the locked blocks
    RedrawLockedBlocks(scene);

    // Draw the next block
    nextBlock->Draw(scene, 300, -300);
}

void Game::MoveBlock(int rows, int columns) {
    currentBlock->Move(rows, columns);
}

void Game::RotateBlock() {
    currentBlock->Rotate();
}

//Laget av ai med modifiseringer.
void Game::LockBlock(threepp::Scene &scene) {
    const std::vector<Position> blockPositions = currentBlock->GetCellPositions();

    for (const auto &pos: blockPositions) {
        int lockedRow = pos.row;
        int lockedColumn = pos.column;
        grid.grid[lockedRow][lockedColumn] = currentBlock->id;

        lockedBlocks.emplace_back(std::make_shared<LockedBlock>(pos));
    }

    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    int clearedRows = grid.ClearFullRows();
    UpdateScore(clearedRows, 0);

    lockedBlocks.erase(std::remove_if(lockedBlocks.begin(), lockedBlocks.end(),
                                      [clearedRows](const auto &lockedBlock) {
                                          return lockedBlock->position.row < clearedRows;
                                      }),
                       lockedBlocks.end());

    for (auto &lockedBlock: lockedBlocks) {
        lockedBlock->position.row -= clearedRows;
    }

    RedrawLockedBlocks(scene);
}

void Game::RedrawLockedBlocks(threepp::Scene &scene) const {
    const std::unordered_map<int, std::shared_ptr<Block>> blockTypeMap = {
            {1, std::make_shared<LBlock>()},
            {2, std::make_shared<JBlock>()},
            {3, std::make_shared<IBlock>()},
            {4, std::make_shared<OBlock>()},
            {5, std::make_shared<SBlock>()},
            {6, std::make_shared<TBlock>()},
            {7, std::make_shared<ZBlock>()}
    };

    for (int row = 0; row < grid.numRows; ++row) {
        for (int col = 0; col < grid.numCols; ++col) {
            int blockId = grid.grid[row][col];

            auto blockTypeIt = blockTypeMap.find(blockId);
            if (blockTypeIt != blockTypeMap.end()) {
                Position blockPosition(row, col);
                blockTypeIt->second->DrawAtPosition(scene, blockPosition);
            }
        }
    }
}

Game::LockedBlock::LockedBlock(Position position) : position(position) {
}
//

void Game::Reset() {
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints) {
    score += (linesCleared >= 1 && linesCleared <= 3) ? (linesCleared * 100) : 0;
    score += moveDownPoints;
}

bool Game::IsCollision(const Block &block) const {
    return collisionManager.IsCollision(block, 1, 0);
}

bool Game::IsGameOver() const {
    // Check if the current block is outside the top two rows of the grid
    return collisionManager.IsBlockOutside(*currentBlock);
}
