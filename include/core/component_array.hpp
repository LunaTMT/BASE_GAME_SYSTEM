#pragma once

#include "types.hpp"

#include <unordered_map>

/*
This class is an interface or abstract base class, denoted by the presence of at least one pure virtual function.
The class has a virtual destructor (virtual ~IComponentArray() = default;), indicating that it's designed to be a base class for polymorphic types.
It declares one pure virtual function EntityDestroyed(Entity entity) = 0;. This function serves as a contract that any derived class must implement.
The purpose of this interface is to define a common interface for component arrays that store components associated with entities in a game engine or similar application.
*/

class IComponentArray{
public:
    virtual ~IComponentArray();
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : IComponentArray{

public:
    void InsertData(Entity entity, T component){
        assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once");
        //If this evaluates to true it means the entity does not exist in the component array, thus it doesnt have this component

        size_t newIndex = m_size
        m_entityToIndexMap[entity] = index;
        m_indexToEntityMap[index] = entity;

        m_componentArray[newIndex] = component;
        ++m_size;
    }

    void RemoveData(Entity entity){
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Removing non-existent component.");

        size_t removed_entity_index = m_entityToIndexMap[entity];
        size_t last_entity_index = m_size - 1;

        m_componentArray[removed_entity_index] = m_componentArray[last_entity_index];

        Entity lastEntity = m_indexToEntityMap[last_entity_index];
        
        m_entityToIndexMap[lastEntity] = removed_entity_index;

        m_indexToEntityMap[removed_entity_index] = lastEntity;

        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(last_entity_index);

        --m_size;
    }

    T& GetData(Entity entity){
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Retrieving non-existent component.");
        return m_componentArray[m_indexToEntityMap[entity]];
    }

    void EntityDestroyed(Entity entity) override {
        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end()){
            RemoveData(entity);
        }
    }

    

private:
    std::array<T, MAX_ENTITIES> m_componentArray;

    std::unordered_map<Entity, size_t> m_entityToIndexMap;
    std::unordered_map<size_t, Entity> m_indexToEntityMap;

    size_t m_size;
    
};
