#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    
    void start();
private:
    void run();

    sf::RenderWindow window;

    sf::Clock dtClock;
};