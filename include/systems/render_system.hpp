#pragma once
#include "globals.hpp" 
#include "system.hpp"

#include <iostream>
#include "render.hpp"
#include "transform.hpp"


class RenderSystem : public System {
public:
    void Render(sf::RenderWindow& window) {
        for (auto const& entity : m_entities) {
            auto& render = gCoordinator.GetComponent<Rendering>(entity);
            auto& transform = gCoordinator.GetComponent<Transform>(entity);

            auto& rigidbody = gCoordinator.GetComponent<RigidBody>(entity);

            // Apply transform data to the render rectangle
            render.rectangle.setPosition(transform.position);
            render.rectangle.setRotation(transform.rotation);
            render.rectangle.setScale(transform.scale);

       

            // Draw the rectangle
            window.draw(render.rectangle);
        }
    }
};