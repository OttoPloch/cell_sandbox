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

    nextGrid = cellManager->nextGrid;

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

    myColor.r -= getRandomInt(cellManager->cellColorVariance);
    myColor.g -= getRandomInt(cellManager->cellColorVariance);
    myColor.b -= getRandomInt(cellManager->cellColorVariance);

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
    // copies cell to nextGrid
    (*nextGrid)[newGridPos.y][newGridPos.x] = (*grid)[gridPos.y][gridPos.x];
    
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
    // copies cell to nextGrid
    (*nextGrid)[gridPos.y + yChange][gridPos.x + xChange] = (*grid)[gridPos.y][gridPos.x];
    
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

    std::shared_ptr<Cell> nextTopNeighbor = nullptr;
    std::shared_ptr<Cell> nextTopLeftNeighbor = nullptr;
    std::shared_ptr<Cell> nextTopRightNeighbor = nullptr;

    std::shared_ptr<Cell> nextBottomNeighbor = nullptr;
    std::shared_ptr<Cell> nextBottomLeftNeighbor = nullptr;
    std::shared_ptr<Cell> nextBottomRightNeighbor = nullptr;

    std::shared_ptr<Cell> nextLeftNeighbor = nullptr;
    std::shared_ptr<Cell> nextRightNeighbor = nullptr;

    ////////// assigning neighbors //////////

    if (gridPos.y > 0)
    {
        topNeighbor = (*grid)[gridPos.y - 1][gridPos.x];
        nextTopNeighbor = (*nextGrid)[gridPos.y - 1][gridPos.x];

        if (gridPos.x > 0)
        {
            topLeftNeighbor = (*grid)[gridPos.y - 1][gridPos.x - 1];
            nextTopLeftNeighbor = (*nextGrid)[gridPos.y - 1][gridPos.x - 1];
        }

        if (gridPos.x < (*grid)[gridPos.y].size() - 1)
        {
            topRightNeighbor = (*grid)[gridPos.y - 1][gridPos.x + 1];
            nextTopRightNeighbor = (*nextGrid)[gridPos.y - 1][gridPos.x + 1];
        }
    }

    if (gridPos.y < (*grid).size() - 1)
    {
        bottomNeighbor = (*grid)[gridPos.y + 1][gridPos.x];
        nextBottomNeighbor = (*nextGrid)[gridPos.y + 1][gridPos.x];

        if (gridPos.x > 0)
        {
            bottomLeftNeighbor = (*grid)[gridPos.y + 1][gridPos.x - 1];
            nextBottomLeftNeighbor = (*nextGrid)[gridPos.y + 1][gridPos.x - 1];
        }

        if (gridPos.x < (*grid)[gridPos.y].size() - 1)
        {
            bottomRightNeighbor = (*grid)[gridPos.y + 1][gridPos.x + 1];
            nextBottomRightNeighbor = (*nextGrid)[gridPos.y + 1][gridPos.x + 1];
        }
    }

    if (gridPos.x > 0)
    {
        leftNeighbor = (*grid)[gridPos.y][gridPos.x - 1];
        nextLeftNeighbor = (*nextGrid)[gridPos.y][gridPos.x - 1];
    }

    if (gridPos.x < (*grid)[gridPos.y].size() - 1)
    {
        rightNeighbor = (*grid)[gridPos.y][gridPos.x + 1];
        nextRightNeighbor = (*nextGrid)[gridPos.y][gridPos.x + 1];
    }

    /////////////////////////////////////////

    int gridTop = 0;
    int gridBottom = (*grid).size() - 1;
    int gridLeft = 0;
    int gridRight = (*grid)[gridPos.y].size() - 1;

    if (type == "sand")
    {
        bool stayStill = false;
        
        if (gridPos.y < gridBottom)
        {
            if (printThoughts) std::cout << "OK! So, im not on the bottom, and since\n";

            if (bottomNeighbor == nullptr)
            {
                if (nextBottomNeighbor == nullptr)
                {
                    if (printThoughts) std::cout << "the spot below me will be free next step, ill go there!\n";
                    moveCell(0, 1);
                    falling = true;
                } else {
                    stayStill = true;
                    falling = false;
                }
            }
            else if (bottomLeftNeighbor == nullptr && gridPos.x > gridLeft && nextBottomLeftNeighbor == nullptr)
            {
                if (printThoughts) std::cout << "i cant go down, and the spot below and to the left of me is gonna be free, ill go there!\n";
                moveCell(-1, 1);
                falling = true;
            }
            else if (bottomRightNeighbor == nullptr && gridPos.x < gridRight && nextBottomRightNeighbor == nullptr)
            {
                if (printThoughts) std::cout << "i cant go down or down and left, and the spot down and right to me is not reserved, ill go there!\n";
                moveCell(1, 1);
                falling = true;
            }
            else 
            {
                if (printThoughts) std::cout << "no spots are open, so ill just stay put!\n";
                stayStill = true;
                falling = false;
            }
        }
        else
        {
            if (printThoughts) std::cout << "Alright, well im on the bottom, so ill just stay here!\n";
            stayStill = true;
            falling = false;
        }

        if (stayStill)
        {
            (*nextGrid)[gridPos.y][gridPos.x] = (*grid)[gridPos.y][gridPos.x];
        }
    }
    else if (type == "water")
    {
        bool stayStill = false;
        
        if (gridPos.y < gridBottom)
        {
            if (nextBottomNeighbor == nullptr)
            {
                moveCell(0, 1);
                falling = true;
            }
            else if (gridPos.x > gridLeft && nextBottomLeftNeighbor == nullptr)
            {
                moveCell(-1, 1);
                falling = true;
            }
            else if (gridPos.x < gridRight && nextBottomRightNeighbor == nullptr)
            {
                moveCell(1, 1);
                falling = true;
            }
            else if (gridPos.x < gridRight && nextLeftNeighbor == nullptr)
            {
                moveCell(-1, 0);
                falling = true;
            }
            else if (gridPos.x > gridLeft && nextLeftNeighbor == nullptr)
            {
                moveCell(1, 0);
                falling = true;
            }
            else 
            {
                stayStill = true;
                falling = false;
            }
        }
        else
        {
            stayStill = true;
            falling = false;
        }

        if (stayStill)
        {
            (*nextGrid)[gridPos.y][gridPos.x] = (*grid)[gridPos.y][gridPos.x];
        }
    }

    // if (type == "sand")
    // {
    //     bool stayStill = false;

    //     if (gridPos.y < (*grid).size() - 1)
    //     {
    //         if (bottomNeighbor == nullptr)
    //         {
    //             if ((*nextGrid)[gridPos.y + 1][gridPos.x].get() == nullptr)
    //             {
    //                 //std::cout << gridPos.x << ", " << gridPos.y << " is going down...\n";
    //                 moveCell(0, 1);
    //                 falling = true;
    //             }
    //             else
    //             {
    //                 stayStill = true;
    //                 falling = false;
    //             }
    //         }
    //         else if (bottomNeighbor.get()->isFalling())
    //         {
    //             //std::cout << gridPos.x << ", " << gridPos.y << " is waiting...\n";
    //             stayStill = true;
    //             falling = true;
    //         }
    //         else if (bottomNeighbor.get()->getType() == "water")
    //         {
    //             bottomNeighbor.get()->moveCell(0, -1);
    //             moveCell(0, 1);
    //         }
    //         else if (bottomLeftNeighbor == nullptr && gridPos.x > 0 && (*nextGrid)[gridPos.y + 1][gridPos.x - 1].get() == nullptr)
    //         {
    //             //std::cout << gridPos.x << ", " << gridPos.y << " is going down-left...\n";
    //             moveCell(-1, 1);
    //             falling = true;
    //         }
    //         else if (bottomRightNeighbor == nullptr && gridPos.x < (*grid)[gridPos.y].size() - 1 && (*nextGrid)[gridPos.y + 1][gridPos.x + 1].get() == nullptr)
    //         {
    //             //std::cout << gridPos.x << ", " << gridPos.y << " is going down-right...\n";
    //             moveCell(1, 1);
    //             falling = true;
    //         }
    //         else
    //         {
    //             stayStill = true;
    //             falling = false;
    //         }
    //     }
    //     else 
    //     {
    //         stayStill = true;
    //         falling = false;
    //     }

    //     if (stayStill)
    //     {
    //         //std::cout << gridPos.x << ", " << gridPos.y << " is not falling...\n";
    //         lastGridPos = gridPos;
    //         (*nextGrid)[gridPos.y][gridPos.x] = (*grid)[gridPos.y][gridPos.x];
    //     }
    // }
    // else if (type == "water")
    // {
    //     bool stayStill = false;

    //     if (gridPos.y < (*grid).size() - 1)
    //     {
    //         if (bottomNeighbor == nullptr)
    //         {
    //             if ((*nextGrid)[gridPos.y + 1][gridPos.x].get() == nullptr)
    //             {
    //                 //std::cout << gridPos.x << ", " << gridPos.y << " is going down...\n";
    //                 moveCell(0, 1);
    //                 falling = true;
    //             }
    //             else
    //             {
    //                 stayStill = true;
    //                 falling = false;
    //             }
    //         }
    //         else if (bottomNeighbor.get()->isFalling())
    //         {
    //             //std::cout << gridPos.x << ", " << gridPos.y << " is waiting...\n";
    //             stayStill = true;
    //             falling = true;
    //         }
    //         else if (bottomLeftNeighbor == nullptr && gridPos.x > 0 && (*nextGrid)[gridPos.y + 1][gridPos.x - 1].get() == nullptr)
    //         {
    //             //std::cout << gridPos.x << ", " << gridPos.y << " is going down-left...\n";
    //             moveCell(-1, 1);
    //             falling = true;
    //         }
    //         else if (bottomRightNeighbor == nullptr && gridPos.x < (*grid)[gridPos.y].size() - 1 && (*nextGrid)[gridPos.y + 1][gridPos.x + 1].get() == nullptr)
    //         {
    //             //std::cout << gridPos.x << ", " << gridPos.y << " is going down-right...\n";
    //             moveCell(1, 1);
    //             falling = true;
    //         }
    //         else if (leftNeighbor == nullptr && gridPos.x > 0 && (*nextGrid)[gridPos.y][gridPos.x - 1].get() == nullptr)
    //         {
    //             //std::cout << gridPos.x << ", " << gridPos.y << " is going left...\n";
    //             moveCell(-1, 0);
    //             falling = true;
    //         }
    //         else
    //         {
    //             stayStill = true;
    //             falling = false;
    //         }
    //     }
    //     else 
    //     {
    //         stayStill = true;
    //         falling = false;
    //     }

    //     if (stayStill)
    //     {
    //         //std::cout << gridPos.x << ", " << gridPos.y << " is not falling...\n";
    //         lastGridPos = gridPos;
    //         (*nextGrid)[gridPos.y][gridPos.x] = (*grid)[gridPos.y][gridPos.x];
    //     }
    // }
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