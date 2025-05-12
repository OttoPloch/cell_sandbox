#include "cell.hpp"

Cell::Cell() {}

Cell::Cell(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos)
{
    create(cellManager, cellPosition, gridPos);
}

void Cell::create(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos)
{
    this->cellManager = cellManager;

    grid = cellManager->grid;

    nextGrid = cellManager->nextGrid;

    vertices = cellManager->vertices;

    this->cellPosition = cellPosition;

    this->gridPos = gridPos;

    lastGridPos = gridPos;

    this->cellSize = cellManager->cellSize;

    createVertices();
}

void Cell::createVertices()
{
    verticesIndex = vertices->size();
    
    std::array<sf::Vertex, 6> newVertices;

    setVerticesPositions(newVertices);

    srand(time(0));

    sf::Color myColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);

    for (int i = 0; i < 6; i++)
    {
        newVertices[i].color = myColor;
    }

    vertices->insert(vertices->end(), &newVertices[0], &newVertices[newVertices.size()]);
}

void Cell::setVerticesPositions(std::array<sf::Vertex, 6>& verticesToChange)
{
    verticesToChange[0].position = {cellPosition.x, cellPosition.y};
    verticesToChange[1].position = {cellPosition.x + cellSize, cellPosition.y};
    verticesToChange[2].position = {cellPosition.x, cellPosition.y + cellSize};
    verticesToChange[3].position = verticesToChange[2].position;
    verticesToChange[4].position = verticesToChange[1].position;
    verticesToChange[5].position = {cellPosition.x + cellSize, cellPosition.y + cellSize};
}

void Cell::changeVerticesPositions(std::array<sf::Vertex*, 6>& verticesToChange)
{
    verticesToChange[0]->position = {cellPosition.x, cellPosition.y};
    verticesToChange[1]->position = {cellPosition.x + cellSize, cellPosition.y};
    verticesToChange[2]->position = {cellPosition.x, cellPosition.y + cellSize};
    verticesToChange[3]->position = verticesToChange[2]->position;
    verticesToChange[4]->position = verticesToChange[1]->position;
    verticesToChange[5]->position = {cellPosition.x + cellSize, cellPosition.y + cellSize};
}

void Cell::moveCell(sf::Vector2i newGridPos)
{
    //copies the current cell to its next spot
    (*nextGrid)[newGridPos.y][newGridPos.x] = (*grid)[gridPos.y][gridPos.x];

    // changes this cell's position variables
    gridPos = {newGridPos.x, newGridPos.y};
    cellPosition = {(float)(gridPos.x * cellSize), (float)(gridPos.y * cellSize)};

    ////////// changes the vertices //////////
    
    std::array<sf::Vertex*, 6> verticesToChange;

    for (int i = 0; i < verticesToChange.size(); i++)
    {
        verticesToChange[i] = &(*vertices)[verticesIndex + i];
    }

    changeVerticesPositions(verticesToChange);
    
    //////////////////////////////////////////

}

void Cell::moveCell(int xChange, int yChange)
{
    // copies cell to nextGrid
    (*nextGrid)[gridPos.y + yChange][gridPos.x + xChange] = (*grid)[gridPos.y][gridPos.x];
    
    // changes this cell's position variables
    lastGridPos = gridPos;
    gridPos = {gridPos.x + xChange, gridPos.y + yChange};
    cellPosition = {(float)(gridPos.x * cellSize), (float)(gridPos.y * cellSize)};

    ////////// changes the vertices //////////
    
    std::array<sf::Vertex*, 6> verticesToChange;

    for (int i = 0; i < verticesToChange.size(); i++)
    {
        verticesToChange[i] = &(*vertices)[verticesIndex + i];
    }

    changeVerticesPositions(verticesToChange);
    
    //////////////////////////////////////////
}

void Cell::step()
{
    std::shared_ptr<Cell> topNeighbor = nullptr;
    std::shared_ptr<Cell> bottomNeighbor = nullptr;
    std::shared_ptr<Cell> leftNeighbor = nullptr;
    std::shared_ptr<Cell> rightNeighbor = nullptr;

    if (gridPos.y > 0)
    {
        topNeighbor = (*grid)[gridPos.y - 1][gridPos.x];
    }

    if (gridPos.y < (*grid).size() - 1)
    {
        bottomNeighbor = (*grid)[gridPos.y + 1][gridPos.x];
    }

    if (gridPos.x > 0)
    {
        leftNeighbor = (*grid)[gridPos.y][gridPos.x - 1];
    }

    if (gridPos.x < (*grid)[gridPos.y].size() - 1)
    {
        rightNeighbor = (*grid)[gridPos.y][gridPos.x + 1];
    }

    if (bottomNeighbor == nullptr && gridPos.y < (*grid).size() - 1)
    {
        moveCell(0, 1);
    }
    else 
    {
        lastGridPos = gridPos;
        (*nextGrid)[gridPos.y][gridPos.x] = (*grid)[gridPos.y][gridPos.x];
    }
}

sf::Vector2i Cell::getGridPos()
{
    return gridPos;
}

sf::Vector2i Cell::getLastGridPos()
{
    return lastGridPos;
}

sf::Vector2f Cell::getCellPosition()
{
    return cellPosition;
}