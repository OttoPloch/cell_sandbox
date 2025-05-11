#include "game.hpp"

Game::Game() {}

void Game::start()
{
    window = sf::RenderWindow(sf::VideoMode({1920, 1080}), "Sandbox");
    window.setFramerateLimit(300);

    dtClock.start();

    run();
}

void Game::run()
{
    while (window.isOpen())
    {
        float dt = dtClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }


        window.clear();
        
        window.display();
    }
}