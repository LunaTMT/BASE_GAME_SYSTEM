#pragma once
#include <unordered_map>
#include "system.hpp"
#include <memory>

class SystemManager{

public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem(){
        const char* typeID = typeid(T).name()  // just same as type(X) in python

        assert( m_Systems.find(typeID) == m_Systems.end() && "Attemping to register system already registered")

        auto system = std::make_shared<T>();

    }

    template<typename T>
    void SetSignature(Signature Signature){
        const char* typeID = typeid(T).name()  // just same as type(X) in python

        assert( m_Systems.find(typeID) == m_Systems.end() && "Attemping to register system already registered")

        m_Systems[typeID] = signature;
    }

    void EntityDestroyed(Entity entity){

        for (auto const& pair: m_Systems){
            auto const& system = pair.second;
            system->m_Entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature){

        for (auto const& pair : m_Systems){
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = m_Signature[type];


            if ((entitySignature & systemSignature) == systemSignature){
                system->m_Entities.insert(entity);
            } else {
                system->m_Entities.erase(entity);
            }
        }
    }

private:
    std::unordered_map<const char*, Signature> m_Signature;
    std::unordered_map<const char*, std::shared_ptr<System>> m_Systems; 

};