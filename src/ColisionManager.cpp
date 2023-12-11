#include "../include/ColisionManager.hpp"

CollisionManager::CollisionManager(const Grid &gameGrid) : gameGrid(gameGrid) {
}

//skrevet av AI
bool CollisionManager::IsCollision(const Block &block, int rows, int columns) const {
    const auto cellPositions = block.GetCellPositionsAfterMove(rows, columns);

    return std::any_of(cellPositions.begin(), cellPositions.end(),
                       [this](const Position &newPos) {
                           return !IsCellPositionValid(newPos);
                       });
}

//
bool CollisionManager::IsCellPositionValid(const Position &newPos) const {
    return (newPos.row >= 0 && newPos.row < gameGrid.GetNumRows() &&
            newPos.column >= 0 && newPos.column < gameGrid.GetNumCols() &&
            gameGrid.GetCellValue(newPos.row, newPos.column) == 0);
}

bool CollisionManager::IsBlockOutside(const Block &block) const {
    const auto &newPositions = block.GetCellPositionsAfterMove(0, 0);

    return std::any_of(newPositions.begin(), newPositions.end(),
                       [this](const Position &newPos) {
                           return newPos.row < 0 || newPos.row >= gameGrid.GetNumRows() ||
                                  newPos.column < 0 || newPos.column >= gameGrid.GetNumCols() ||
                                  gameGrid.GetCellValue(newPos.row, newPos.column) != 0;
                       });
}
