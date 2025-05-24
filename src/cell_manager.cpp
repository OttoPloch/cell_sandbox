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
        "fire",
        "smoke"
    };

    cellSize = 10;

    cellColorVariance = 10;

    cellColors = {
        {"sand", {sf::Color(252, 191, 98)}},
        {"water", {sf::Color(19, 94, 186), sf::Color(24, 106, 191)}},
        {"wood", {sf::Color(102, 69, 24)}},
        {"fire", {sf::Color(227, 19, 0), sf::Color(255, 106, 0)}},
        {"smoke", {sf::Color(45, 45, 56)}}
    };

    woodBurnChance = 3;

    fireMoveChance = 10;
}