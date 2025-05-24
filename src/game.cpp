#include "game.hpp"

Game::Game() {}

void Game::start()
{
    window = sf::RenderWindow(sf::VideoMode({1000, 562}), "Sandbox", sf::Style::Close);
    window.setFramerateLimit(60);

    isFullscreen = false;

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
                    if (keyPressed->code == sf::Keyboard::Key::Enter)
                    {
                        world.createCellCircleFromClick(30, 85);
                    }
                    if (keyPressed->code == sf::Keyboard::Key::Escape)
                    {
                        window.close();
                    }
                    if (keyPressed->code == sf::Keyboard::Key::Num1)
                    {
                        if (!isFullscreen)
                        {
                            window.setSize({1000, 562});
                        }
                    }
                    if (keyPressed->code == sf::Keyboard::Key::Num2)
                    {
                        if (!isFullscreen)
                        {
                            window.setSize({1920, 1080});
                        }
                    }
                    if (keyPressed->code == sf::Keyboard::Key::F11)
                    {
                        isFullscreen = !isFullscreen;

                        window.close();

                        if (isFullscreen)
                        {
                            window.create(sf::VideoMode::getDesktopMode(), "Sandbox", sf::State::Fullscreen);
                        }
                        else
                        {
                            window.create(sf::VideoMode({1920, 1080}), "Sandbox", sf::Style::Close);
                        }
                    }
                }
            }
            else if (event->is<sf::Event::Resized>())
            {
                window.setView(sf::View({window.getSize().x / 2.f, window.getSize().y / 2.f}, {(float)window.getSize().x, (float)window.getSize().y}));
                sf::Transform transform;
                transform.translate({window.getView().getCenter().x - world.cellManager.cellSize * (world.cellManager.gridSize.x / 2.f), window.getView().getCenter().y - world.cellManager.cellSize * (world.cellManager.gridSize.y / 2.f)});
                world.states.transform = transform;
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

            ticksToProcess += (dt * 1000) / (100.f / 6.f);
    
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