#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "cell_manager.hpp"
#include "cell.hpp"

class World
{
public:
    World();

    World(sf::RenderWindow& window);

    void create(sf::RenderWindow& window);

    void update();

    sf::Vector2i getMouseGridPosition();
    
    void createCellFromClick();
private:
    sf::RenderWindow* window;

    std::vector<std::vector<Cell*>> grid;

    std::vector<sf::Vertex> vertices;

    std::vector<Cell*> cells;

    CellManager cellManager;

    void createCell(sf::Vector2i gridPos, sf::Vector2f cellPosition);
};