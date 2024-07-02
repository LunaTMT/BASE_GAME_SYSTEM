#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Sprite {
    sf::Sprite sprite;

    // Default constructor
    Sprite() = default;

    // Constructor with texture parameter
    Sprite(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }
};
