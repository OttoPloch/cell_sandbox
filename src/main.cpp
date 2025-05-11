#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "getPaths.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920, 1080}), "CMake SFML Project");

    sf::Texture backgroundTexture(getProjectPath().string() + "/images/wallpaper.png");

    std::array<sf::Vertex, 6> backgroundVertices;

    backgroundVertices[0].position = {0, 0};
    backgroundVertices[0].texCoords = {0, 0};
    backgroundVertices[1].position = {1920, 0};
    backgroundVertices[1].texCoords = {4633, 0};
    backgroundVertices[2].position = {0, 1277};
    backgroundVertices[2].texCoords = {0, 3083};

    backgroundVertices[3].position = {0, 1277};
    backgroundVertices[3].texCoords = {0, 3083};
    backgroundVertices[4].position = {1920, 0};
    backgroundVertices[4].texCoords = {4633, 0};
    backgroundVertices[5].position = {1920, 1277};
    backgroundVertices[5].texCoords = {4633, 3083};

    sf::RenderStates states;
    states.texture = &backgroundTexture;

    window.setMouseCursorVisible(false);

    sf::CircleShape mouseCircle(10.f);
    mouseCircle.setOrigin({10.f, 10.f});
    mouseCircle.setFillColor(sf::Color(125, 125, 145));
    mouseCircle.setOutlineColor(sf::Color::Black);
    mouseCircle.setOutlineThickness(3.f);

    sf::CircleShape movingBall(30.f);
    movingBall.setOrigin({30.f, 30.f});
    movingBall.setFillColor(sf::Color::Blue);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        movingBall.setPosition({window.getSize().x / 2.f + sin(clock.getElapsedTime().asSeconds()) * 100, window.getSize().y / 2.f + sin(clock.getElapsedTime().asSeconds() * 2) * 30});

        mouseCircle.setPosition({(float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y});



        window.clear();

        window.draw(&backgroundVertices[0], backgroundVertices.size(), sf::PrimitiveType::Triangles, states);

        window.draw(movingBall);

        window.draw(mouseCircle);
        
        window.display();
    }
}
