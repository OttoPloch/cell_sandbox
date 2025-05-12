#include "cell_manager.hpp"

#include "cell.hpp"

CellManager::CellManager() {}

CellManager::CellManager(std::vector<std::vector<Cell*>>* grid, std::vector<sf::Vertex>* vertices)
{
    create(grid, vertices);
}

void CellManager::create(std::vector<std::vector<Cell*>>* grid, std::vector<sf::Vertex>* vertices)
{
    this->grid = grid;

    this->vertices = vertices;

    cellSize = 10;
}