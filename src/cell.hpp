#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include "cell_manager.hpp"

class Cell
{
public:
    Cell();

    Cell(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos);

    void create(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos);

    void moveCell(sf::Vector2i newGridPos);

    void moveCell(int xChange, int yChange);

    void step();

    sf::Vector2i getGridPos();
private:
    CellManager* cellManager;

    std::vector<std::vector<std::shared_ptr<Cell>>>* grid;

    std::vector<std::vector<std::shared_ptr<Cell>>>* nextGrid;

    std::vector<sf::Vertex>* vertices;

    sf::Vector2f cellPosition;

    sf::Vector2i gridPos;

    int cellSize;

    unsigned int verticesIndex;

    void createVertices();

    void setVerticesPositions(std::array<sf::Vertex, 6>& verticesToChange);

    void changeVerticesPositions(std::array<sf::Vertex*, 6>& verticesToChange);
};