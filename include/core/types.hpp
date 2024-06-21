#pragma once
#include <SFML/Graphics.hpp>
#include <bitset>
#include <cstdint> // Ensure <cstdint> is included for fixed-width integer types

// Type alias for Entity
using Entity = std::uint32_t;
static constexpr Entity MAX_ENTITIES = 5000; // Maximum number of entities

// Type alias for ComponentType
using ComponentType = std::uint8_t;
static constexpr ComponentType MAX_COMPONENTS = 32; // Maximum number of component types

// Signature type for entities
using Signature = std::bitset<MAX_COMPONENTS>;



// Component representing gravity
struct Gravity {
    sf::Vector2f force; // Use sf::Vector2f for consistency with SFML
};

// Component representing a rigid body in physics
struct RigidBody {
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

// Component representing the transform (position, rotation, scale) of an entity
struct Transform {
    sf::Vector2f position;
    sf::Vector2f rotation;
    sf::Vector2f scale;
};
