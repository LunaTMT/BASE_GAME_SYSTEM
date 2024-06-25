#pragma once 

#include <unordered_map>
#include "types.hpp"
#include <memory>
#include "component_array.hpp"

class ComponentManger{

public:

    template<typename T>
    void RegisterComponent(){
        const char* typeID = typeid(T).name();

        assert(m_componentTypes.find(typeID) == m_componentTypes.end() && "Registering component type more than once."); 
        
        m_componentTypes.insert({typeID, m_nextComponentType});
        m_componentArrays.insert({typeID, std::make_shared<ComponentArray<T>>()});

        m_nextComponentType++;
    }

    template<typename T>
    ComponentType GetComponentType(){
        const char* typeID = typeid(T).name();

        assert(m_componentTypes.find(typeID) != m_componentTypes.end() && "Component not registered before use.");

        return m_componentTypes[typeID];
    }

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

    template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

    template<typename T>
    T& GetComponent(Entity entity){
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity){
        for (auto const& pair : m_componentArrays){
            auto const& componentArray = pair.second;
            componentArray->EntityDestroyed(entity);
        }
    }


private:
    // map of the types of components available, e.g. transform, rigidbody
    std::unordered_map<const char*, ComponentType> m_componentTypes;

    // Map from type string pointer to a component array
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;


    /*
     It initializes mNextComponentType with an empty initializer list, {}, 
     which effectively initializes it with the default value of the type ComponentType. 
     For built-in numeric types like std::uint8_t, this would initialize mNextComponentType to 0.
    */
    ComponentType m_nextComponentType{};

    // Convenience function to get the statically casted pointer to the ComponentArray of type T.
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray(){
        
        //Given the calling component array we get its type id  (typeName)
        const char* typeID = typeid(T).name();

        //Assert that is exists in the registered list of component arrays
        assert(m_componentTypes.find(typeID) != m_componentTypes.end() && "Component not registered before use.");

        //Casting the IComponentArray to its given Component Array <template> e.g. ComponentArray<Gravity> contains all gravity component signatures
		return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeID]);
    }
};