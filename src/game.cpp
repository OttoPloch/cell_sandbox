#include "game.hpp"

Game::Game() {}

void Game::start()
{
    window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Sandbox");
    //window.setFramerateLimit(60);

    dtClock.start();

    world.create(window);

    paused = true;

    run();
}

void Game::run()
{
    float ticksToProcess = 0.f;

    float highestFrameTime = 0.f;

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
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (window.hasFocus())
                {
                    if (keyPressed->code == sf::Keyboard::Key::Q)
                    {
                        world.cycleTool();
                    }
                    if (keyPressed->code == sf::Keyboard::Key::Tab)
                    {
                        paused = !paused;
                    }
                }
            }
        }

        float FPS = 1.f / dt;

        if (dt * 1000 > highestFrameTime)
        {
            highestFrameTime = dt * 1000;

            //std::cout << highestFrameTime << "ms\n";
        }

        if (!paused)
        {
            //std::cout << "FPS: " << FPS << "; frame time: " << dt * 1000 << "ms; highest frame time: " << highestFrameTime << "ms\n";

            //std::cout << "cells created: " << world.getCellsCreated() << "; current cells: " << world.getCellCount() << '\n';

            ticksToProcess += (dt * 1000) / 20;
    
            while (ticksToProcess >= 1.f)
            {
                world.step();
    
                ticksToProcess -= 1.f;
            }
        }

        window.clear(sf::Color(15, 15, 15));

        world.update();
        
        window.display();
    }
}