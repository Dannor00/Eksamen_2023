#include "../include/game.hpp"

Game::Game() : grid(Grid()), rd(), gen(rd()), collisionManager(grid) {
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;  // Initialize the score to zero
}

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }

    std::uniform_int_distribution<std::size_t> dist(0, blocks.size() - 1);
    std::size_t randomIndex = dist(gen);

    auto iter = blocks.begin() + static_cast<std::ptrdiff_t>(randomIndex);
    Block block = std::move(*iter);
    blocks.erase(iter);

    return block;
}


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
    MarkBlockDirty(&currentBlock);
}

void Game::MoveBlockDown(threepp::Scene &scene) {
    if (elapsedSinceLastFall >= BlockFallInterval) {
        elapsedSinceLastFall = 0.0f;

        // Attempt to move the block down
        if (!IsCollision(currentBlock, 1, 0)) {
            MoveBlock(1, 0);
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

bool Game::IsGameOver() const {
    // Check if the current block is outside the top two rows of the grid
    return collisionManager.IsBlockOutside(currentBlock);
}

void Game::MoveBlock(int rows, int columns) {
        currentBlock.Move(rows, columns);
}

void Game::RotateBlock() {
    currentBlock.Rotate();
}

void Game::LockBlock(threepp::Scene &scene) {
    const std::vector<Position> blockPositions = currentBlock.GetCellPositions();

    // Reserve space for the new locked blocks
    lockedBlocks.reserve(lockedBlocks.size() + blockPositions.size());

    for (const auto &pos: blockPositions) {
        int lockedRow = pos.row;
        int lockedColumn = pos.column;
        grid.grid[lockedRow][lockedColumn] = currentBlock.id;

        // Use emplace_back for smart pointers
        lockedBlocks.emplace_back(std::make_unique<LockedBlock>(pos));
    }

    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    int clearedRows = grid.ClearFullRows();
    UpdateScore(clearedRows, 0);

    // Erase locked blocks that are above cleared rows
    lockedBlocks.erase(std::remove_if(lockedBlocks.begin(), lockedBlocks.end(),
                                      [clearedRows](const std::shared_ptr<LockedBlock> &lockedBlock) {
                                          return lockedBlock->position.row < clearedRows;
                                      }),
                       lockedBlocks.end());

    // Adjust the positions of remaining locked blocks
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

            auto it = blockTypeMap.find(blockId);
            if (it != blockTypeMap.end()) {
                Position blockPosition(row, col);
                std::shared_ptr<Block> blockInstance = it->second;
                blockInstance->DrawAtPosition(scene, blockPosition);
            }
        }
    }
}

Game::LockedBlock::LockedBlock(Position position) : position(position) {
}

void Game::Reset() {
    grid.Initialize();
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

bool Game::IsCollision(const Block &block, int rows, int columns) const {
    return collisionManager.IsCollision(block, rows, columns);
}