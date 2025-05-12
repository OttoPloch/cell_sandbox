#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "cell_manager.hpp"

class Cell
{
public:
    Cell();

    Cell(CellManager* cellManager, sf::Vector2f cellPosition);

    void create(CellManager* cellManager, sf::Vector2f cellPosition);
private:
    CellManager* cellManager;

    std::vector<std::vector<Cell*>>* grid;

    std::vector<sf::Vertex>* vertices;

    sf::Vector2f cellPosition;

    int cellSize;

    unsigned int verticesIndex;

    void createVertices();
};