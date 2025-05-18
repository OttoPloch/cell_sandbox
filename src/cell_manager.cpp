#include "cell_manager.hpp"

#include "cell.hpp"

CellManager::CellManager() {}

CellManager::CellManager(std::vector<std::vector<std::shared_ptr<Cell>>>* grid, std::vector<sf::Vertex>* vertices)
{
    create(grid, vertices);
}

void CellManager::create(std::vector<std::vector<std::shared_ptr<Cell>>>* grid, std::vector<sf::Vertex>* vertices)
{
    this->grid = grid;

    this->vertices = vertices;

    types = {
        "sand",
        "water",
        "wood",
        "fire"
    };

    cellSize = 10;

    cellColorVariance = 50;

    woodBurnChance = 0;
}