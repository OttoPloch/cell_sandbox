#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <tgmath.h>
#include "cell_manager.hpp"
#include "cell.hpp"
#include "get_index.hpp"

class World
{
public:
    sf::RenderStates states;

    CellManager cellManager;

    World();

    World(sf::RenderWindow& window);

    void create(sf::RenderWindow& window);

    void update();

    void step();

    sf::Vector2i getMouseGridPosition();

    std::vector<sf::Vector2i> getMouseGridPositionsFromRadius(int radius);

    std::vector<sf::Vector2i> getMouseGridPositionsFromSquare(int length);
    
    void createCellFromClick();

    // chanceOfCreation is the x/100 chance that a
    // cell in a spot in the radius will be created
    void createCellCircleFromClick(int radius, int chanceOfCreation);

    // chanceOfCreation is the x/100 chance that a
    // cell in a spot in the radius will be created
    void createCellSquareFromClick(int length, int chanceOfCreation);

    int getCellCount();

    int getCellsCreated();

    void cycleTool();

    void setTool(std::string tool);
private:
    sf::RenderWindow* window;

    std::vector<std::vector<std::shared_ptr<Cell>>> grid;

    std::vector<sf::Vertex> vertices;

    int toolIndex;
    
    std::string cellCreationType;

    int cellsCreated;

    void createCell(sf::Vector2i gridPos, sf::Vector2f cellPosition, std::string type);
};