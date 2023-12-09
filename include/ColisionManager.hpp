#ifndef EKSAMEN_2023_COLLISIONMANAGER_HPP
#define EKSAMEN_2023_COLLISIONMANAGER_HPP

#include "grid.hpp"
#include "Block.hpp"

#pragma once


class CollisionManager {
public:
    explicit CollisionManager(const Grid &gameGrid);

    [[nodiscard]] bool IsCollision(const Block &block, int rows, int columns) const;

    [[nodiscard]] bool IsBlockOutside(const Block &block) const;

private:
    const Grid &gameGrid;

    [[nodiscard]] bool IsCellPositionValid(const Position &newPos) const;
};

#endif // EKSAMEN_2023_COLLISIONMANAGER_HPP