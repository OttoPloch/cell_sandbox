#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <map>

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

    std::map<std::string, std::vector<sf::Color>> cellColors;

    // x/100 chance of wood burning
    // from fire in a step
    int woodBurnChance;

    // x/100 chance of fire moving to
    // a random open spot in a step
    int fireMoveChance;
};