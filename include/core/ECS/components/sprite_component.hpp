#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Rendering {
    sf::Sprite sprite;

    // Default constructor
    Rendering() = default;

    // Constructor with texture parameter
    Rendering(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }
};
