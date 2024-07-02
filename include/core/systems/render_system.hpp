#pragma once
#include "globals.hpp" 
#include "system.hpp"

#include <iostream>
#include "sprite_component.hpp"
#include "transform_component.hpp"


class RenderSystem : public System {
public:
    void Render(sf::RenderWindow& window) {
        for (auto const& entity : m_entities) {
            auto& render = g_coordinator.GetComponent<Sprite>(entity);
            auto& transform = g_coordinator.GetComponent<Transform>(entity);

            auto& rigidbody = g_coordinator.GetComponent<RigidBody>(entity);

            // Apply transform data to the render rectangle
            render.sprite.setPosition(transform.position);
            render.sprite.setRotation(transform.rotation);
            render.sprite.setScale(transform.scale);
           

            // Draw the rectangle
            window.draw(render.sprite);
            
        }
    }
};