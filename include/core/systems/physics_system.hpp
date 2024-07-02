// physics_system.hpp
#pragma once
#include "globals.hpp" 
#include "system.hpp"

#include "gravity_component.hpp"
#include "rigidbody_component.hpp"
#include "transform_component.hpp"
#include "sprite_component.hpp"

#include <iostream>

// Include the globals header

class PhysicsSystem : public System {

public:
    void Init() {};

    void Update(float dt) {
        for (auto const& entity : m_entities) {
            auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
            auto& transform = gCoordinator.GetComponent<Transform>(entity);
            auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);
            auto const& render = gCoordinator.GetComponent<Rendering>(entity);

            // Apply gravity and acceleration to velocity
            rigidBody.velocity += gravity.force * dt;
            rigidBody.velocity += rigidBody.acceleration * dt;

            // Update position based on velocity
            transform.position += rigidBody.velocity * dt;

            // Collision detection with screen boundaries

            // Get global bounding rectangle
            sf::FloatRect bounds = render.sprite.getGlobalBounds();

            // X-axis collision
            if (bounds.left < 0) {
                transform.position.x = 0; 
                rigidBody.velocity.x *= -1; 
            } else if (bounds.left + bounds.width > WINDOW_WIDTH) {
                transform.position.x = WINDOW_WIDTH - bounds.width; 
                rigidBody.velocity.x *= -1; 
            }

            // Y-axis collision
            if (bounds.top < 0) {
                transform.position.y = 0; 
                rigidBody.velocity.y *= -1; 
            } else if (bounds.top + bounds.height > WINDOW_HEIGHT) {
                transform.position.y = WINDOW_HEIGHT - bounds.height; 
                rigidBody.velocity.y *= -1; 
            }


        }
    }


};
