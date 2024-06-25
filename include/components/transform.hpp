#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/System/Vector2.hpp>

struct Transform {
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
};


#endif // TRANSFORM_H
