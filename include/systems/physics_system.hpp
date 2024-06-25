#pragma once

#include "system.hpp"
#include "coordinator.hpp"

extern Coordinator m_coordinator;

class PhysicsSystem : public System {

public:
    void Init() {};
 

    void Update(float dt)
    {
        for (auto const& entity : m_entities)
        {
            auto& rigidBody = m_coordinator.GetComponent<RigidBody>(entity);
            auto& transform = m_coordinator.GetComponent<Transform>(entity);

            // Forces
            auto const& gravity = m_coordinator.GetComponent<Gravity>(entity);

            transform.position += rigidBody.velocity * dt;

            rigidBody.velocity += gravity.force * dt;
        }
    }
};