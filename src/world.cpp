#include "world.hpp"

World::World() {}

World::World(sf::RenderWindow& window)
{
    create(window);
}

void World::create(sf::RenderWindow& window)
{
    this->window = &window;

    int gridSize = 1000;

    grid.resize(gridSize);

    for (int i = 0; i < grid.size(); i++)
    {
        grid[i].resize(gridSize);

        for (int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j] = nullptr;
        }
    }

    cellManager.create(&grid, &vertices);

    cellManager.cellSize = 1000 / grid.size();
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

void World::createCellFromClick()
{
    sf::Vector2i mouseGridPos = getMouseGridPosition();

    if (mouseGridPos.x > 0 && mouseGridPos.x < grid[0].size() && mouseGridPos.y > 0 && mouseGridPos.y < grid.size())
    {
        sf::Vector2f cellPosition = {(float)(mouseGridPos.x * cellManager.cellSize), (float)(mouseGridPos.y * cellManager.cellSize)};
    
        createCell(mouseGridPos, cellPosition);
    }
}

void World::createCell(sf::Vector2i gridPos, sf::Vector2f cellPosition)
{
    grid[gridPos.y][gridPos.x] = std::unique_ptr<Cell> (new Cell(&cellManager, cellPosition)).get();
}

sf::Vector2i World::getMouseGridPosition()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    return {(int)((mousePos.x - (mousePos.x % cellManager.cellSize)) / cellManager.cellSize), (int)((mousePos.y - (mousePos.y % cellManager.cellSize)) / cellManager.cellSize)};
}