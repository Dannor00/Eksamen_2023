#include "vector"
#include "../include/game.hpp"
#include <random>


Game::Game() : grid(Grid()) {
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, blocks.size() - 1);
    int randomIndex = dist(gen);

    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(threepp::Scene& scene) {
    grid.Draw(scene);
    currentBlock.Draw(scene);
}

void Game::Update() {
    // Add your game logic here
    // For example, handling block movements, collisions, etc.
    // Example: currentBlock.move(1, 0); // Move the current block down
}


void Game::moveCurrentBlock(int rows, int columns) {
    currentBlock.Move(rows, columns);
}

// Other member function definitions...
