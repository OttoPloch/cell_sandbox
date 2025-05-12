#include "cell.hpp"

Cell::Cell() {}

Cell::Cell(CellManager* cellManager, sf::Vector2f cellPosition)
{
    create(cellManager, cellPosition);
}

void Cell::create(CellManager* cellManager, sf::Vector2f cellPosition)
{
    this->cellManager = cellManager;

    grid = cellManager->grid;

    vertices = cellManager->vertices;

    this->cellPosition = cellPosition;

    this->cellSize = cellManager->cellSize;

    createVertices();
}

void Cell::createVertices()
{
    verticesIndex = vertices->size();
    
    std::array<sf::Vertex, 6> newVertices;

    newVertices[0].position = {cellPosition.x, cellPosition.y};
    newVertices[1].position = {cellPosition.x + cellSize, cellPosition.y};
    newVertices[2].position = {cellPosition.x, cellPosition.y + cellSize};
    newVertices[3].position = newVertices[2].position;
    newVertices[4].position = newVertices[1].position;
    newVertices[5].position = {cellPosition.x + cellSize, cellPosition.y + cellSize};

    for (int i = 0; i < 6; i++)
    {
        newVertices[i].color = sf::Color::Red;
    }

    vertices->insert(vertices->end(), &newVertices[0], &newVertices[newVertices.size()]);
}