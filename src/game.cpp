#include "game.hpp"

Game::Game() {}

void Game::start()
{
    window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Sandbox");
    window.setFramerateLimit(300);

    dtClock.start();

    world.create(window);

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
            else if (const auto* buttonClicked = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (buttonClicked->button == sf::Mouse::Button::Left) {
                    world.createCellFromClick();
                }
            }
        }

        std::cout << "FPS: " << 1.f / dt << '\n';

        window.clear();

        world.update();
        
        window.display();
    }
}