#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Cell;

class CellManager
{
public:
    CellManager();

    CellManager(std::vector<std::vector<Cell*>>* grid, std::vector<sf::Vertex>* vertices);

    void create(std::vector<std::vector<Cell*>>* grid, std::vector<sf::Vertex>* vertices);

    std::vector<std::vector<Cell*>>* grid;

    std::vector<sf::Vertex>* vertices;

    int cellSize;
};