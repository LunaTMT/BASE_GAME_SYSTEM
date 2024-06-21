#pragma once
#include <memory>

#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "system_manager.hpp"

class Coordinator{
public:
    void Init(){
        m_ComponentManager = std::make_unique<ComponentManger>();
        m_EntityManager    = std::make_unique<EntityManager>();
        m_SystemManager    = std::make_unique<SystemManager>();

    }

    Entity CreateEntity(){
        return m_EntityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity){
        m_EntityManager->DestroyEntity(entity);
        m_ComponentManager->EntityDestroyed(entity);
        m_SystemManager->EntityDestroyed(entity);
    }

    template<typename T>
    void RegisterComponent(){
        m_ComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component){
        m_ComponentManager->AddComponent<T>(entity, component);

        auto signature = m_EntityManager->GetSignature(entity);
        
        /*
        Optional parameter. If set to true (default), the bit at position pos is set to 1. 
        If set to false, the bit at position pos is set to 0.
        given the component we get its type which is an std::uint8_t; (8 bit signed int)
        We switch the bit on for that index 

        e.g 
        Set bit at position 2 to true (1)
        bits.set(2);
        */
        signature.set(m_ComponentManager->GetComponentType<T>(), true);
        m_EntityManager->SetSignature(entity, signature);
        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity){
        m_ComponentManager->RemoveComponent<T>(entity);
        auto signature = m_EntityManager->GetSignature();
        signature.set(m_ComponentManager->GetComponentType<T>(), false);
        m_EntityManager->SetSignature(entity, signature);
        m_SystemManager->EntitySignatureChanged(entity, signature);
    }


    template<typename T>
    T& getComponent(Entity entity){
        return m_ComponentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType(){
        return m_ComponentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> ReigsterSystem(){
        return m_SystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature){
        m_SystemManager->SetSignature<T>(signature);
    }



private:
    std::unique_ptr<ComponentManger> m_ComponentManager;
    std::unique_ptr<EntityManager> m_EntityManager;
    std::unique_ptr<SystemManager> m_SystemManager
}