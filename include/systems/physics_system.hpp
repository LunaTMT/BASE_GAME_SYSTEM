// physics_system.hpp
#pragma once
#include "globals.hpp" 
#include "system.hpp"

#include "gravity.hpp"
#include "rigidbody.hpp"
#include "transform.hpp"

#include <iostream>

// Include the globals header

class PhysicsSystem : public System {

public:
    void Init() {};
 
    void Update(float dt)
    {
        for (auto const& entity : m_entities)
        {
            auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
            auto& transform = gCoordinator.GetComponent<Transform>(entity);
            auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

            rigidBody.velocity += gravity.force * dt;
            rigidBody.velocity += rigidBody.acceleration * dt;

            transform.position += rigidBody.velocity * dt;
            
            
            //std::cout << rigidBody.velocity.x << " " << rigidBody.velocity.y << "   " <<  transform.position.x << " " <<  transform.position.y << " " << dt << std::endl;
            //std::cin.get();
        }
    }
};
