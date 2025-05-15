#include "world.hpp"

World::World() {}

World::World(sf::RenderWindow& window)
{
    create(window);
}

void World::create(sf::RenderWindow& window)
{
    this->window = &window;

    int gridLength = 500;
    int gridHeight = 500;

    grid.resize(gridHeight);
    nextGrid.resize(gridHeight);

    for (int i = 0; i < grid.size(); i++)
    {
        grid[i].resize(gridLength);
        nextGrid[i].resize(gridLength);
    }
    
    cellManager.create(&grid, &nextGrid, &vertices);
    
    cellManager.cellSize = (float)window.getSize().y / (float)grid.size();

    cellsCreated = 0;

    cellCreationType = "sand";

    // for (int j = 0; j < gridLength; j++)
    // {
    //     for (int i = 0; i < 1; i++)
    //     {
    //         createCell({j, i}, {(float)j * cellManager.cellSize, (float)i * cellManager.cellSize}, "sand");
    //     }
    // }
}

void World::update()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
        {
            createCellFromClick();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        {
            createCellCircleFromClick(10);
        }
    }

    window->draw(&vertices[0], vertices.size(), sf::PrimitiveType::Triangles);
}

void World::step()
{
    // for (int i = 0; i < grid.size(); i++)
    // {
    //     for (int j = 0; j < grid[i].size(); j++)
    //     {
    //         if (grid[i][j] == nullptr)
    //         {
    //             std::cout << "0";
    //         }
    //         else {
    //             std::cout << "1";
    //         }
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << '\n';

    for (int y = grid.size() - 1; y >= 0; y--)
    {
        for (int x = grid[y].size() - 1; x >= 0; x--)
        {
            if (grid[y][x] != nullptr)
            {
                bool printThoughts = false;

                // if (getMouseGridPosition() == grid[y][x]->getGridPos())
                // {
                //     printThoughts = true;
                // }

                grid[y][x]->step(printThoughts);
            }
        }
    }

    for (int y = grid.size() - 1; y >= 0; y--)
    {
        for (int x = grid[y].size() - 1; x >= 0; x--)
        {
            if (grid[y][x] != nullptr || nextGrid[y][x] != nullptr)
            {
                grid[y][x] = std::move(nextGrid[y][x]);
            }
        }
    }

}

void World::createCellFromClick()
{
    sf::Vector2i mouseGridPos = getMouseGridPosition();

    if (mouseGridPos.x >= 0 && mouseGridPos.x < grid[0].size() && mouseGridPos.y >= 0 && mouseGridPos.y < grid.size())
    {
        if (grid[mouseGridPos.y][mouseGridPos.x] == nullptr)
        {
            sf::Vector2f cellPosition = {(float)(mouseGridPos.x * cellManager.cellSize), (float)(mouseGridPos.y * cellManager.cellSize)};
        
            createCell(mouseGridPos, cellPosition, cellCreationType);
        }
    }
}

void World::createCellCircleFromClick(int radius)
{
    std::vector<sf::Vector2i> cellsToMake = getMouseGridPositionsFromRadius(radius);

    for (int i = 0; i < cellsToMake.size(); i++)
    {
        if (cellsToMake[i].x >= 0 && cellsToMake[i].x < grid[0].size() && cellsToMake[i].y >= 0 && cellsToMake[i].y < grid.size())
        {
            if (grid[cellsToMake[i].y][cellsToMake[i].x] == nullptr)
            {
                sf::Vector2f cellPosition = {(float)(cellsToMake[i].x * cellManager.cellSize), (float)(cellsToMake[i].y * cellManager.cellSize)};
            
                createCell(cellsToMake[i], cellPosition, cellCreationType);
            }
        }
    }
}

void World::createCell(sf::Vector2i gridPos, sf::Vector2f cellPosition, std::string type)
{
    grid[gridPos.y][gridPos.x] = std::make_shared<Cell>(&cellManager, cellPosition, gridPos, type);

    cellsCreated++;
}

sf::Vector2i World::getMouseGridPosition()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    return {(int)((mousePos.x - (fmod(mousePos.x, cellManager.cellSize))) / cellManager.cellSize), (int)((mousePos.y - (fmod(mousePos.y, cellManager.cellSize))) / cellManager.cellSize)};
}

std::vector<sf::Vector2i> World::getMouseGridPositionsFromRadius(int radius)
{
    std::vector<sf::Vector2i> pointsInRadius;

    sf::Vector2i mouseGridPos = getMouseGridPosition();

    int centerX = mouseGridPos.x;
    int centerY = mouseGridPos.y;

    int xStart = centerX - radius;
    int xEnd = centerX + radius;
    int yStart = centerY - radius;
    int yEnd = centerY + radius;

    for (int x = xStart; x <= xEnd; x++)
    {
        for (int y = yStart; y <= yEnd; y++)
        {
            if (pow(x - centerX, 2) + pow(y - centerY, 2) <= radius * radius)
            {
                pointsInRadius.push_back({x, y});
            }
        }
    }

    return pointsInRadius;
}

int World::getCellCount()
{
    int cells = 0;

    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid[y].size(); x++)
        {
            if (grid[y][x] != nullptr)
            {
                cells++;
            }
        }
    }

    return cells;
}

int World::getCellsCreated()
{
    return cellsCreated;
}

void World::cycleTool()
{
    if (cellCreationType == "sand")
    {
        cellCreationType = "water";
    }
    else
    {
        cellCreationType = "sand";
    }

    std::cout << "new tool: " << cellCreationType << '\n';
}

void World::setTool(std::string tool)
{  
    cellCreationType = tool;

    std::cout << "new tool: " << cellCreationType << '\n';
}