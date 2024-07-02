#pragma once

#include "types.hpp"
#include <queue>
#include <cassert> 

class EntityManager{
    public: 
        EntityManager(){
            //Populate the queue with std::uint32_t; representing the ID of the entity for the maximum number of entities MAX_ENTITIES
            for (Entity entity=0; entity < MAX_ENTITIES; ++entity)
                m_availableEntities.push(entity);
        };
    

        Entity CreateEntity() {
            if (m_livingEntityCount >= MAX_ENTITIES) {
                throw std::runtime_error("Too many entities in existence. MAX_ENTITIES: " + std::to_string(MAX_ENTITIES) + " Current living entities: " + std::to_string(m_livingEntityCount));
            }

            // Get an available entity and return its ID
            Entity id = m_availableEntities.front();
            m_availableEntities.pop();
            ++m_livingEntityCount;

            return id;
        }

        void DestroyEntity(Entity entity){
            assert(entity < MAX_ENTITIES && "Entity out of range");

            m_signatures[entity].reset();
        };

        void SetSignature(Entity entity, Signature signature){
            assert(entity < MAX_ENTITIES && "Entity out of range");

            m_signatures[entity] = signature;
        };

        Signature GetSignature(Entity entity){
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return m_signatures[entity];
        };


        Signature GetSignature();

    private:
        std::queue<Entity> m_availableEntities{};
        std::array<Signature, MAX_ENTITIES> m_signatures{};
        std::uint32_t m_livingEntityCount = 0;
};