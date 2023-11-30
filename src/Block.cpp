#include <iostream>
#include "../include/Block.hpp"
#include "threepp/threepp.hpp"


Block::Block() {
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(threepp::Scene &scene) {
    float blockWidth = 10 * cellSize;
    float blockHeight = 20 * cellSize;

    float centerX = -blockWidth / 2.0;
    float centerY = blockHeight / 2.0;

    std::vector<std::shared_ptr<threepp::Mesh>> boxes;

    std::vector<Position> tiles = GetCellPositions();
    for (const Position &item : tiles) {
        float x = centerX + (item.column * cellSize);
        float y = centerY - (item.row * cellSize);
        float z = 0;

        float width = cellSize - 1;
        float height = cellSize - 1;

        auto geometry = threepp::BoxGeometry::create(width, height, 2);
        auto material = threepp::MeshBasicMaterial::create({{"color", colors[id]}});
        auto boxMesh = threepp::Mesh::create(geometry, material);

        boxMesh->position.x = x;
        boxMesh->position.y = y;
        boxMesh->position.z = z;

        boxes.push_back(boxMesh);
    }

    for (const auto &box : boxes) {
        scene.add(box);
    }
}

void Block::Move(int rows, int columns) {
    rowOffset += rows;
    columnOffset += columns;

    // Optional: Add boundary checks to restrict movement
    rowOffset = std::max(-1, rowOffset);  // Ensure the block stays within the top boundary
     columnOffset = std::max(-1, columnOffset);  // Ensure the block stays within the left boundary
}

std::vector<Position> Block::GetCellPositions() {
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> moveTiles;
    for (Position item : tiles) {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        moveTiles.push_back(newPos);
    }
    return moveTiles;
}


std::vector<Position> Block::GetCellPositionsAfterMove(int rows, int columns) const {
    std::vector<Position> tiles = cells.at(rotationState);
    std::vector<Position> moveTiles;
    for (Position item : tiles) {
        Position newPos = Position(item.row + rowOffset + rows, item.column + columnOffset + columns);
        moveTiles.push_back(newPos);
    }
    return moveTiles;
}
void Block::Rotate() {
    rotationState ++;
    if (rotationState ==(int) cells.size())
    {
        rotationState =0;
    }
}
void Block::DrawAtPosition(threepp::Scene &scene, const Position &position) {
    float blockWidth = 10 * cellSize;
    float blockHeight = 20 * cellSize;

    float centerX = -blockWidth / 2.0;
    float centerY = blockHeight / 2.0;

    std::vector<std::shared_ptr<threepp::Mesh>> boxes;

    std::vector<Position> tiles = GetCellPositions();
    for (const Position &item : tiles) {
        float x = centerX + (item.column ) + position.column * cellSize;
        float y = centerY - (item.row ) - position.row * cellSize;
        float z = 0;

        float width = cellSize - 1;
        float height = cellSize - 1;

        auto geometry = threepp::BoxGeometry::create(width, height, 2);
        auto material = threepp::MeshBasicMaterial::create({{"color", colors[id]}});
        auto boxMesh = threepp::Mesh::create(geometry, material);

        boxMesh->position.x = x;
        boxMesh->position.y = y;
        boxMesh->position.z = z;

        boxes.push_back(boxMesh);
    }

    for (const auto &box : boxes) {
        scene.add(box);
    }
}

