#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

class Cell;

class CellManager
{
public:
    CellManager();

    CellManager(std::vector<std::vector<std::shared_ptr<Cell>>>* grid, std::vector<sf::Vertex>* vertices);

    void create(std::vector<std::vector<std::shared_ptr<Cell>>>* grid, std::vector<sf::Vertex>* vertices);

    std::vector<std::vector<std::shared_ptr<Cell>>>* grid;

    std::vector<sf::Vertex>* vertices;

    std::vector<std::string> types;

    float cellSize;

    int cellColorVariance;

    // x/100 chance of wood burning from
    // fire in a step;
    int woodBurnChance;
};