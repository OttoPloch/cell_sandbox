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

    void swap(sf::Vector2i swapPosition);

    void step(bool printThoughts);

    sf::Vector2i getGridPos();

    sf::Vector2f getCellPosition();

    std::string getType();

    void changeType(std::string newType);
private:
    CellManager* cellManager;

    std::vector<std::vector<std::shared_ptr<Cell>>>* grid;

    std::vector<sf::Vertex>* vertices;

    sf::Vector2f cellPosition;

    sf::Vector2i gridPos;

    float cellSize;

    unsigned int verticesIndex;

    std::string type;

    void createVertices();

    std::array<sf::Vertex, 6> setColor(std::array<sf::Vertex, 6>& vertices);

    std::array<sf::Vertex*, 6> changeColor(std::array<sf::Vertex*, 6>& vertices);
    
    std::array<sf::Vertex, 6> setVerticesPositions(std::array<sf::Vertex, 6>& verticesToChange);
    
    std::array<sf::Vertex*, 6> changeVerticesPositions(std::array<sf::Vertex*, 6>& verticesToChange);
};