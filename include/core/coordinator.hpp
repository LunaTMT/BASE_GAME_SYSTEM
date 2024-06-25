#pragma once
#include <memory>

#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "system_manager.hpp"

class Coordinator{
public:
    void Init(){
        m_componentManager = std::make_unique<ComponentManger>();
        m_entityManager    = std::make_unique<EntityManager>();
        m_systemManager    = std::make_unique<SystemManager>();

    }

    Entity CreateEntity(){
        return m_entityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity){
        m_entityManager->DestroyEntity(entity);
        m_componentManager->EntityDestroyed(entity);
        m_systemManager->EntityDestroyed(entity);
    }

    template<typename T>
    void RegisterComponent(){
        m_componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component){
        m_componentManager->AddComponent<T>(entity, component);

        auto signature = m_entityManager->GetSignature(entity);
        
        /*
        Optional parameter. If set to true (default), the bit at position pos is set to 1. 
        If set to false, the bit at position pos is set to 0.
        given the component we get its type which is an std::uint8_t; (8 bit signed int)
        We switch the bit on for that index 

        e.g 
        Set bit at position 2 to true (1)
        bits.set(2);
        */
        signature.set(m_componentManager->GetComponentType<T>(), true);
        m_entityManager->SetSignature(entity, signature);
        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity){
        m_componentManager->RemoveComponent<T>(entity);
        auto signature = m_entityManager->GetSignature();
        signature.set(m_componentManager->GetComponentType<T>(), false);
        m_entityManager->SetSignature(entity, signature);
        m_systemManager->EntitySignatureChanged(entity, signature);
    }


    template<typename T>
    T& GetComponent(Entity entity){
        return m_componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType(){
        return m_componentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> RegisterSystem(){
        return m_systemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature){
        m_systemManager->SetSignature<T>(signature);
    }



private:
    std::unique_ptr<ComponentManger> m_componentManager;
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<SystemManager> m_systemManager;
};