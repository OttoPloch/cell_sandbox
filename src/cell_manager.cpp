#include "cell_manager.hpp"

#include "cell.hpp"

CellManager::CellManager() {}

CellManager::CellManager(std::vector<std::vector<std::shared_ptr<Cell>>>* grid, std::vector<std::vector<std::shared_ptr<Cell>>>* nextGrid, std::vector<sf::Vertex>* vertices)
{
    create(grid, nextGrid, vertices);
}

void CellManager::create(std::vector<std::vector<std::shared_ptr<Cell>>>* grid, std::vector<std::vector<std::shared_ptr<Cell>>>* nextGrid, std::vector<sf::Vertex>* vertices)
{
    this->grid = grid;

    this->nextGrid = nextGrid;

    this->vertices = vertices;

    cellSize = 10;

    cellColorVariance = 10;
}