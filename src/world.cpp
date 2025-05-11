#include "world.hpp"

World::World() {}

World::World(sf::RenderWindow& window)
{
    create(window);
}

void World::create(sf::RenderWindow& window)
{
    this->window = &window;

    srand(time(0));

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            grid[i][j] = rand() % 4;

            vertices[(i * grid[i].size() * 6 + j * 6)].position = {(float)j * 10, (float)i * 10};
            vertices[(i * grid[i].size() * 6 + j * 6) + 1].position = {(float)j * 10 + 10, (float)i * 10};
            vertices[(i * grid[i].size() * 6 + j * 6) + 2].position = {(float)j * 10, (float)i * 10 + 10};
            vertices[(i * grid[i].size() * 6 + j * 6) + 3].position = {(float)j * 10, (float)i * 10 + 10};
            vertices[(i * grid[i].size() * 6 + j * 6) + 4].position = {(float)j * 10 + 10, (float)i * 10};
            vertices[(i * grid[i].size() * 6 + j * 6) + 5].position = {(float)j * 10 + 10, (float)i * 10 + 10};

            switch(grid[i][j]) {
                case 0:
                    vertices[(i * grid[i].size() * 6 + j * 6)].color = sf::Color::Black;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 1].color = sf::Color::Black;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 2].color = sf::Color::Black;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 3].color = sf::Color::Black;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 4].color = sf::Color::Black;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 5].color = sf::Color::Black;
                    break;
                case 1:
                    vertices[(i * grid[i].size() * 6 + j * 6)].color = sf::Color::Red;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 1].color = sf::Color::Red;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 2].color = sf::Color::Red;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 3].color = sf::Color::Red;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 4].color = sf::Color::Red;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 5].color = sf::Color::Red;
                    break;
                case 2:
                    vertices[(i * grid[i].size() * 6 + j * 6)].color = sf::Color::Green;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 1].color = sf::Color::Green;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 2].color = sf::Color::Green;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 3].color = sf::Color::Green;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 4].color = sf::Color::Green;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 5].color = sf::Color::Green;
                    break;
                case 3:
                    vertices[(i * grid[i].size() * 6 + j * 6)].color = sf::Color::Blue;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 1].color = sf::Color::Blue;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 2].color = sf::Color::Blue;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 3].color = sf::Color::Blue;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 4].color = sf::Color::Blue;
                    vertices[(i * grid[i].size() * 6 + j * 6) + 5].color = sf::Color::Blue;
                    break;
            }
        }
    }
}

void World::update()
{
    window->draw(&vertices[0], vertices.size(), sf::PrimitiveType::Triangles);
}