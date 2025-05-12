#include "world.hpp"

World::World() {}

World::World(sf::RenderWindow& window)
{
    create(window);
}

void World::create(sf::RenderWindow& window)
{
    this->window = &window;

    int gridSize = 100;

    grid.resize(gridSize);
    nextGrid.resize(gridSize);

    for (int i = 0; i < grid.size(); i++)
    {
        grid[i].resize(gridSize);
        nextGrid[i].resize(gridSize);
    }
    
    cellManager.create(&grid, &nextGrid, &vertices);
    
    cellManager.cellSize = window.getSize().y / grid.size();
}

void World::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            createCellFromClick();
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

void World::createCell(sf::Vector2i gridPos, sf::Vector2f cellPosition)
{
    grid[gridPos.y][gridPos.x] = std::make_shared<Cell>(&cellManager, cellPosition, gridPos);

    cells.push_back(grid[gridPos.y][gridPos.x].get());
}

sf::Vector2i World::getMouseGridPosition()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    return {(int)((mousePos.x - (mousePos.x % cellManager.cellSize)) / cellManager.cellSize), (int)((mousePos.y - (mousePos.y % cellManager.cellSize)) / cellManager.cellSize)};
}