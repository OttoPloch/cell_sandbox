#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <string>
#include <random>
#include "cell_manager.hpp"
#include "get_random_number.hpp"

class Cell
{
public:
    Cell();

    Cell(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos, std::string type);

    void create(CellManager* cellManager, sf::Vector2f cellPosition, sf::Vector2i gridPos, std::string type);

    void moveCell(sf::Vector2i newGridPos);

    void moveCell(int xChange, int yChange);

    void step();

    sf::Vector2i getGridPos();

    sf::Vector2i getLastGridPos();

    sf::Vector2f getCellPosition();

    bool isFalling();
private:
    CellManager* cellManager;

    std::vector<std::vector<std::shared_ptr<Cell>>>* grid;

    std::vector<std::vector<std::shared_ptr<Cell>>>* nextGrid;

    std::vector<sf::Vertex>* vertices;

    sf::Vector2f cellPosition;

    sf::Vector2i gridPos;

    sf::Vector2i lastGridPos;

    bool falling;

    float cellSize;

    unsigned int verticesIndex;

    std::string type;

    void createVertices();

    void setVerticesPositions(std::array<sf::Vertex, 6>& verticesToChange);

    void changeVerticesPositions(std::array<sf::Vertex*, 6>& verticesToChange);
};