#include <iostream>
#include "../include/Block.hpp"


Block::Block()
        : cellSize(30), rotationState(0), id(0), rowOffset(0), columnOffset(0), colors(GetCellColors()) {
}


void Block::Draw(threepp::Scene &scene, int offsetX, int offsetY) {
    const std::pair<float, float> center = CommonUtils::CalculateCenter(BLOCK_WIDTH_FACTOR * cellSize,
                                                                        BLOCK_HEIGHT_FACTOR * cellSize);
    const float centerX = center.first;
    const float centerY = center.second;

    std::vector<std::shared_ptr<threepp::Mesh>> boxes;

    for (const Position &item: GetCellPositions()) {
        const float x = centerX + (item.column * cellSize) + offsetX;
        const float y = centerY - (item.row * cellSize) + offsetY;
        const float z = 0;

        const float width = cellSize - 1;
        const float height = cellSize - 1;

        auto geometry = threepp::BoxGeometry::create(width, height, 2);
        auto material = threepp::MeshBasicMaterial::create({{"color", colors[id]}});
        auto boxMesh = threepp::Mesh::create(geometry, material);

        CommonUtils::SetMeshPosition(boxMesh, x, y, z);
        boxes.push_back(boxMesh);
    }

    for (const auto &box: boxes) {
        CommonUtils::AddMeshToScene(scene, box);
    }
}

void Block::Move(int rows, int columns) {
    rowOffset += rows;
    columnOffset += columns;

    // Optional: Add boundary checks to restrict movement
    rowOffset = std::max(-1, rowOffset);  // Ensure the block stays within the top boundary
    columnOffset = std::max(-1, columnOffset);  // Ensure the block stays within the left boundary
}

std::vector<Position> Block::GetCellPositions() const {
    return AdjustPositionsWithOffset(cells.at(rotationState), rowOffset, columnOffset);
}

std::vector<Position> Block::GetCellPositionsAfterMove(int rows, int columns) const {
    return AdjustPositionsWithOffset(cells.at(rotationState), rowOffset + rows, columnOffset + columns);
}

void Block::Rotate() {
    rotationState = (rotationState + 1) % static_cast<int>(cells.size());
}

void Block::DrawAtPosition(threepp::Scene &scene, const Position &position) const {
    const std::pair<float, float> center = CommonUtils::CalculateCenter(BLOCK_WIDTH_FACTOR * cellSize,
                                                                        BLOCK_HEIGHT_FACTOR * cellSize);
    const float centerX = center.first;
    const float centerY = center.second;

    std::vector<std::shared_ptr<threepp::Mesh>> boxes;

    for (const Position &item: GetCellPositions()) {
        const float x = centerX + item.column + position.column * cellSize;
        const float y = centerY - item.row - position.row * cellSize;
        const float z = 0;

        const float width = cellSize - 1;
        const float height = cellSize - 1;

        auto geometry = threepp::BoxGeometry::create(width, height, 2);
        auto material = threepp::MeshBasicMaterial::create({{"color", colors[id]}});
        auto boxMesh = threepp::Mesh::create(geometry, material);

        CommonUtils::SetMeshPosition(boxMesh, x, y, z);
        boxes.push_back(boxMesh);
    }

    for (const auto &box: boxes) {
        CommonUtils::AddMeshToScene(scene, box);
    }
}

void Block::CreateWhiteBox(threepp::Scene &scene, const Position &position, float customWidth, float customHeight,
                           float customDepth) const {
    const std::pair<float, float> center = CommonUtils::CalculateCenter(BLOCK_WIDTH_FACTOR * cellSize,
                                                                        BLOCK_HEIGHT_FACTOR * cellSize);
    const float centerX = center.first;
    const float centerY = center.second;

    const float x = centerX + position.column * cellSize;
    const float y = centerY - position.row * cellSize;
    const float z = 0;

    const float width = customWidth - 1;    // Adjust the width
    const float height = customHeight - 1;  // Adjust the height
    const float depth = customDepth - 1;    // Adjust the depth

    auto geometry = threepp::BoxGeometry::create(width, height, depth);
    auto material = threepp::MeshBasicMaterial::create({{"color", 0xFFFFFF}}); // 0xFFFFFF corresponds to white
    auto whiteBox = threepp::Mesh::create(geometry, material);

    CommonUtils::SetMeshPosition(whiteBox, x, y, z);
    scene.add(whiteBox);
}


std::vector<Position>
Block::AdjustPositionsWithOffset(const std::vector<Position> &positions, int rowOffset, int columnOffset) {
    std::vector<Position> adjustedPositions;
    adjustedPositions.reserve(positions.size());

    for (const Position &item: positions) {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        adjustedPositions.push_back(newPos);
    }

    return adjustedPositions;
}