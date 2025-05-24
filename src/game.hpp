#pragma once

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include <iostream>

class Game
{
public:
    Game();
    
    void start();
private:
    void run();

    sf::RenderWindow window;

    sf::Clock dtClock;

    World world;

    bool paused;

    bool isFullscreen;
};