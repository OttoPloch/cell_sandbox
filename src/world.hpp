#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include <random>
#include <time.h>
#include <iostream>

class World
{
public:
    World();

    World(sf::RenderWindow& window);

    void create(sf::RenderWindow& window);

    void update();
private:
    std::array<std::array<int, 100>, 100> grid;

    sf::RenderWindow* window;

    std::array<sf::Vertex, 60000> vertices;
};