#pragma once

#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

int getIndexOfString(std::vector<std::string> theVector, std::string theObject);

int getIndexOfVertex(std::vector<sf::Vertex> theVector, sf::Vertex theObject);