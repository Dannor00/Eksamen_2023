#include "Block.h"
#include "threepp/threepp.hpp"

Block::Block() {
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(threepp::Scene* scene) {
    float blockWidth = 10 * cellSize;
    float blockHeight = 20 * cellSize;

    float centerX = -blockWidth / 2.0;
    float centerY = blockHeight / 2.0;

    std::vector<Position> tiles = GetCellPositions();
    for (Position item : tiles) {
        float x = centerX + (item.column * cellSize);
        float y = centerY - (item.row * cellSize); // Negative Y because Y-axis in 3D space is typically inverted
        float z = 0;

        float width = cellSize - 1;
        float height = cellSize - 1;

        auto geometry = BoxGeometry::create(width, height, 2);
        auto material = MeshBasicMaterial::create({{"color", colors[id]}});
        auto boxMesh = Mesh::create(geometry, material);

        boxMesh->position.x = x;
        boxMesh->position.y = y;
        boxMesh->position.z = z;

        scene->add(boxMesh);
    }
}

void Block::Move(int rows, int columns) {
    rowOffset += rows;
    columnOffset += columns;
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
