#pragma once

#include <unordered_map>

namespace gi
{
	class Entity;
	class Component;

	class ComponentContainer
	{
	public:
		template <class ComponentType>
		ComponentType* GetComponent() const;
		//Component* GetComponent(const std::string componentID) const;

		void AddComponent(Component* pComponent, const std::string componentID);

		void RemoveComponent(const std::string componentID);

		void ClearComponents();

    bool HasComponent(const std::string componentID);

		bool IsEmpty() const;

	private:
		ComponentContainer(Entity* m_pOwner);
		~ComponentContainer();

		Entity* m_pOwner;
		std::unordered_map<std::string, Component*> m_components;

		friend class Entity;
	};

	template <class ComponentType>
	ComponentType* ComponentContainer::GetComponent() const
	{
		auto& it = m_components.find(ComponentType::COMPONENT_ID);

		if (it == m_components.end())
			return nullptr;

		return dynamic_cast<ComponentType*>(it->second);
	}
}
