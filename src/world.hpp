#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "cell_manager.hpp"
#include "cell.hpp"

class World
{
public:
    World();

    World(sf::RenderWindow& window);

    void create(sf::RenderWindow& window);

    void update();

    void step();

    sf::Vector2i getMouseGridPosition();

    std::vector<sf::Vector2i> getMouseGridPositionsFromRadius(int radius);
    
    void createCellFromClick();

    void createCellCircleFromClick(int radius);
private:
    sf::RenderWindow* window;

    std::vector<std::vector<std::shared_ptr<Cell>>> grid;

    std::vector<std::vector<std::shared_ptr<Cell>>> nextGrid;

    std::vector<sf::Vertex> vertices;

    std::vector<Cell*> cells;

    CellManager cellManager;

    void createCell(sf::Vector2i gridPos, sf::Vector2f cellPosition);
};