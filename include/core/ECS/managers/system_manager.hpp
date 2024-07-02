#pragma once

#include "system.hpp"
#include "types.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>


class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

		auto system = std::make_shared<T>();
        auto systemPair = std::make_pair(typeName, system);

  
        m_systems.insert(systemPair);
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

		m_signatures.insert({typeName, signature});
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : m_systems)
		{
			auto const& system = pair.second;


			system->m_entities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : m_systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = m_signatures[type];

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->m_entities.insert(entity);
			}
			else
			{
				system->m_entities.erase(entity);
			}
		}
	}

private:
	std::unordered_map<const char*, Signature> m_signatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
};