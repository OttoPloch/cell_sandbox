#include "cell.hpp"

Cell::Cell() {}

Cell::Cell(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos, std::string type)
{
    create(cellManager, cellPosition, gridPos, type);
}

void Cell::create(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos, std::string type)
{
    this->cellManager = cellManager;

    grid = cellManager->grid;

    vertices = cellManager->vertices;

    this->cellPosition = cellPosition;

    this->gridPos = gridPos;

    this->type = type;

    falling = true;

    this->cellSize = cellManager->cellSize;

    createVertices();
}

void Cell::createVertices()
{
    verticesIndex = vertices->size();
    
    std::array<sf::Vertex, 6> newVertices;

    setVerticesPositions(newVertices);

    sf::Color myColor;
    
    if (type == "sand")
    {
        myColor = sf::Color(252, 191, 98);
    }
    else if (type == "water")
    {
        myColor = sf::Color(19, 94, 186);
    }
    else if (type == "wood")
    {
        myColor = sf::Color(102, 69, 24);
    }

    int random = getRandomInt(cellManager->cellColorVariance);

    int red = myColor.r;
    int green = myColor.g;
    int blue = myColor.b;

    red -= random;
    green -= random;
    blue -= random;

    if (red < 0) red = 0;
    if (green < 0) green = 0;
    if (blue < 0) blue = 0;

    myColor.r = red;
    myColor.g = green;
    myColor.b = blue;

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
    // moves cell to new grid spot
    (*grid)[newGridPos.y][newGridPos.x] = std::move((*grid)[gridPos.y][gridPos.x]);
    
    // changes this cell's position variables
    gridPos = newGridPos;
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
    std::cout << "next grid pos is " << gridPos.x + xChange << ", " << gridPos.y + yChange << '\n';

    // moves cell to new grid spot
    (*grid)[gridPos.y + yChange][gridPos.x + xChange] = std::move((*grid)[gridPos.y][gridPos.x]);

    // changes this cell's position variables
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

void Cell::swap(sf::Vector2i swapPosition)
{
    std::shared_ptr<Cell> swap = (*grid)[gridPos.y][gridPos.x];

    (*grid)[swapPosition.y][swapPosition.x]->moveCell(gridPos);
    
    // moves cell to new grid spot
    (*grid)[swapPosition.y][swapPosition.x] = std::move(swap);
    
    // changes this cell's position variables
    gridPos = swapPosition;
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

void Cell::step(bool printThoughts)
{
    std::shared_ptr<Cell> topNeighbor = nullptr;
    std::shared_ptr<Cell> topLeftNeighbor = nullptr;
    std::shared_ptr<Cell> topRightNeighbor = nullptr;

    std::shared_ptr<Cell> bottomNeighbor = nullptr;
    std::shared_ptr<Cell> bottomLeftNeighbor = nullptr;
    std::shared_ptr<Cell> bottomRightNeighbor = nullptr;
    
    std::shared_ptr<Cell> leftNeighbor = nullptr;
    std::shared_ptr<Cell> rightNeighbor = nullptr;

    ////////// assigning neighbors //////////

    if (gridPos.y > 0)
    {
        topNeighbor = (*grid)[gridPos.y - 1][gridPos.x];

        if (gridPos.x > 0)
        {
            topLeftNeighbor = (*grid)[gridPos.y - 1][gridPos.x - 1];
        }

        if (gridPos.x < (*grid)[gridPos.y].size() - 1)
        {
            topRightNeighbor = (*grid)[gridPos.y - 1][gridPos.x + 1];
        }
    }

    if (gridPos.y < (*grid).size() - 1)
    {
        bottomNeighbor = (*grid)[gridPos.y + 1][gridPos.x];

        if (gridPos.x > 0)
        {
            bottomLeftNeighbor = (*grid)[gridPos.y + 1][gridPos.x - 1];
        }

        if (gridPos.x < (*grid)[gridPos.y].size() - 1)
        {
            bottomRightNeighbor = (*grid)[gridPos.y + 1][gridPos.x + 1];
        }
    }

    if (gridPos.x > 0)
    {
        leftNeighbor = (*grid)[gridPos.y][gridPos.x - 1];
    }

    if (gridPos.x < (*grid)[gridPos.y].size() - 1)
    {
        rightNeighbor = (*grid)[gridPos.y][gridPos.x + 1];
    }

    /////////////////////////////////////////

    int gridTop = 0;
    int gridBottom = (*grid).size() - 1;
    int gridLeft = 0;
    int gridRight = (*grid)[gridPos.y].size() - 1;

    int x = gridPos.x;
    int y = gridPos.y;

    if (type == "sand")
    {
        if (y < gridBottom)
        {
            if (bottomNeighbor == nullptr)
            {
                moveCell(0, 1);
            }
            else if (bottomNeighbor->getType() == "water")
            {
                swap(bottomNeighbor->getGridPos());
            }
            else
            {
                if (bottomLeftNeighbor == nullptr && x > gridLeft && bottomRightNeighbor == nullptr && x < gridRight)
                {
                    if (getRandomInt(1) == 0)
                    {
                        moveCell(-1, 1);
                    }
                    else
                    {
                        moveCell(1, 1);
                    }
                }
                else
                {
                    if (bottomLeftNeighbor == nullptr && x > gridLeft)
                    {
                        moveCell(-1, 1);
                    }
                    else if (bottomRightNeighbor == nullptr && x < gridRight)
                    {
                        moveCell(1, 1);
                    }
                    else if (bottomLeftNeighbor->getType() == "water" && x > gridLeft && bottomRightNeighbor->getType() == "water" && x < gridRight)
                    {
                        if (getRandomInt(1) == 0)
                        {
                            swap(bottomLeftNeighbor->getGridPos());
                        }
                        else
                        {
                            swap(bottomRightNeighbor->getGridPos());
                        }
                    }
                    else
                    {
                        if (bottomLeftNeighbor->getType() == "water" && x > gridLeft)
                        {
                            swap(bottomLeftNeighbor->getGridPos());
                        }
                        else if (bottomRightNeighbor->getType() == "water" && x < gridRight)
                        {
                            swap(bottomRightNeighbor->getGridPos());
                        }
                    }
                }
            }
        }
        else
        {
            falling = false;
        }
    }
    else if (type == "water")
    {
        if (y < gridBottom)
        {
            if (bottomNeighbor == nullptr)
            {
                moveCell(0, 1);
            }
            else
            {
                if (bottomLeftNeighbor == nullptr && x > gridLeft && bottomRightNeighbor == nullptr && x < gridRight)
                {
                    if (getRandomInt(1) == 0)
                    {
                        moveCell(-1, 1);
                    }
                    else
                    {
                        moveCell(1, 1);
                    }
                }
                else
                {
                    if (bottomLeftNeighbor == nullptr && x > gridLeft)
                    {
                        moveCell(-1, 1);
                    }
                    else if (bottomRightNeighbor == nullptr && x < gridRight)
                    {
                        moveCell(1, 1);
                    }
                    else if (leftNeighbor == nullptr && x > gridLeft && rightNeighbor == nullptr && x < gridRight)
                    {
                        if (getRandomInt(1) == 0)
                        {
                            moveCell(-1, 0);
                        }
                        else
                        {
                            moveCell(1, 0);
                        }
                    }
                    else
                    {
                        if (leftNeighbor == nullptr && x > gridLeft)
                        {
                            moveCell(-1, 0);
                        }
                        else if (rightNeighbor == nullptr && x < gridRight)
                        {
                            moveCell(1, 0);
                        }
                    }
                }
            }
        }
        else
        {
            falling = false;
        }
    }
    else if (type == "wood")
    {

    }
}

sf::Vector2i Cell::getGridPos()
{
    return gridPos;
}

sf::Vector2f Cell::getCellPosition()
{
    return cellPosition;
}

bool Cell::isFalling()
{
    return falling;
}

std::string Cell::getType()
{
    return type;
}