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
    float ticksToProcess = 0.f;

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
                if (window.hasFocus())
                {
                    if (buttonClicked->button == sf::Mouse::Button::Left)
                    {
                        world.createCellFromClick();
                    }
                    if (buttonClicked->button == sf::Mouse::Button::Right)
                    {
                        world.step();
                    }
                }
            }
        }

        //std::cout << "FPS: " << 1.f / dt << '\n';

        ticksToProcess += (dt * 1000) / 50;

        while (ticksToProcess >= 1.f)
        {
            world.step();

            ticksToProcess -= 1.f;
        }

        window.clear();

        world.update();
        
        window.display();
    }
}