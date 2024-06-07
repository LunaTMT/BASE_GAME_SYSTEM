#pragma once 

#include <unordered_map>
#include "types.hpp"
#include <memory>
#include "component_array.hpp"

class ComponentManger{

public:

    template<typename T>
    void RegisterComponent(){
        const char* typeName = typeid(T).name();

        assert(mCompontentTypes.find)

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
        const char* typeName = typeid(T).name();
        assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
    }
};