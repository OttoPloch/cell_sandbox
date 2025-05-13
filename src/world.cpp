#include "world.hpp"

World::World() {}

World::World(sf::RenderWindow& window)
{
    create(window);
}

void World::create(sf::RenderWindow& window)
{
    this->window = &window;

    int gridSize = 500;

    grid.resize(gridSize);
    nextGrid.resize(gridSize);

    for (int i = 0; i < grid.size(); i++)
    {
        grid[i].resize(gridSize);
        nextGrid[i].resize(gridSize);
    }
    
    cellManager.create(&grid, &nextGrid, &vertices);
    
    cellManager.cellSize = window.getSize().y / grid.size();

    // for (int j = 0; j < gridSize; j++)
    // {
    //     for (int i = 0; i < 10; i++)
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
    // updates cells
    for (int i = 0; i < cells.size(); i++)
    {
        cells[i]->step();
    }

    // applies changes to the grid
    for (int i = 0; i < cells.size(); i++)
    {   
        sf::Vector2i cellGridPos = cells[i]->getGridPos();
        sf::Vector2i cellLastGridPos = cells[i]->getLastGridPos();

        grid[cellLastGridPos.y][cellLastGridPos.x] = nullptr;
        grid[cellGridPos.y][cellGridPos.x] = std::move(nextGrid[cellGridPos.y][cellGridPos.x]);
    }

    // for (int i = 0; i < grid.size(); i++)
    // {
    //     for (int j = 0; j < grid[i].size(); j++)
    //     {
    //         if (grid[i][j] == nullptr)
    //         {
    //             std::cout << "0 - ";
    //         }
    //         else {
    //             std::cout << "1 - ";
    //         }
    //     }
        
    //     std::cout << '\n';
    // }

    // std::cout << '\n';
}

void World::createCellFromClick()
{
    sf::Vector2i mouseGridPos = getMouseGridPosition();

    if (mouseGridPos.x >= 0 && mouseGridPos.x < grid[0].size() && mouseGridPos.y >= 0 && mouseGridPos.y < grid.size())
    {
        if (grid[mouseGridPos.y][mouseGridPos.x] == nullptr)
        {
            sf::Vector2f cellPosition = {(float)(mouseGridPos.x * cellManager.cellSize), (float)(mouseGridPos.y * cellManager.cellSize)};
        
            createCell(mouseGridPos, cellPosition);
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
            
                createCell(cellsToMake[i], cellPosition);
            }
        }
    }
}

void World::createCell(sf::Vector2i gridPos, sf::Vector2f cellPosition)
{
    grid[gridPos.y][gridPos.x] = std::make_shared<Cell>(&cellManager, cellPosition, gridPos, "sand");

    cells.push_back(grid[gridPos.y][gridPos.x].get());
}

sf::Vector2i World::getMouseGridPosition()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    return {(int)((mousePos.x - (mousePos.x % cellManager.cellSize)) / cellManager.cellSize), (int)((mousePos.y - (mousePos.y % cellManager.cellSize)) / cellManager.cellSize)};
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