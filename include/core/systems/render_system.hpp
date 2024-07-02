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
            auto& render = gCoordinator.GetComponent<Rendering>(entity);
            auto& transform = gCoordinator.GetComponent<Transform>(entity);

            auto& rigidbody = gCoordinator.GetComponent<RigidBody>(entity);

            // Apply transform data to the render rectangle
            render.sprite.setPosition(transform.position);
            render.sprite.setRotation(transform.rotation);
            render.sprite.setScale(transform.scale);
           

            // Draw the rectangle
            window.draw(render.sprite);
            
        }
    }
};