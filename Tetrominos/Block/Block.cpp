//
// Created by Danie on 24.10.2023.
//

#include "Block.h"
#include "threepp/threepp.hpp"


Block::Block() {
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
}

void Block::Draw(threepp::Scene* scene)
{
    std::vector<Position> tiles = cells[rotationState];
    for (Position items : tiles)
    {
        float x = items.colum * cellSize + 1;
        float y = items.row * cellSize + 1;
        float z = 0;
        float width = cellSize - 1;
        float height = cellSize - 1;

        auto geometry = BoxGeometry::create(width,height,1);
        auto material = MeshBasicMaterial::create({{"color", colors[id]}});
        auto boxMesh = Mesh::create(geometry, material);

        boxMesh->position.x = x;
        boxMesh->position.y = y;
        boxMesh->position.z = z;

        scene->add(boxMesh);
    }
}

