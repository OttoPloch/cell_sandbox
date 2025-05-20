#include "get_index.hpp"

#include <iostream>

int getIndexOfString(std::vector<std::string> theVector, std::string theObject)
{
    if (std::find(theVector.begin(), theVector.end(), theObject) != theVector.end())
    {
        return std::distance(theVector.begin(), std::find(theVector.begin(), theVector.end(), theObject));
    }
    else
    {
        return -1;
    }
}

// no custom operators would work so i had to resort to this
int getIndexOfVertex(std::vector<sf::Vertex> theVector, sf::Vertex theObject)
{
    for (int i = 0; i < theVector.size(); i++)
    {
        if (theVector[i].color == theObject.color && theVector[i].position == theObject.position)
        {
            std::cout << "index: " << i << '\n';

            return i;
        }
    }

    return -1;
}