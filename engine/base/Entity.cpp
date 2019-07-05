#include "Entity.h"

namespace gi
{
	Entity::Entity(Entity* pOwner, const std::string& name) :m_pParent(pOwner), m_components(this), m_name(name), m_isDead(false)
	{
		
	}

	Entity::~Entity()
	{

	}

	/*void Entity::AddComponent(std::shared_ptr<Component> pComponent)
	{
		m_pComponentArray[pComponent->m_type] = pComponent;
	}

	std::shared_ptr<Component> Entity::GetComponent(ComponentType componentType)
	{
		return m_pComponentArray[componentType];
	}

	bool Entity::HasComponent(ComponentType componentType)
	{
		return static_cast<bool>(m_pComponentArray[componentType]);
	}

	template <typename T>
	std::shared_ptr<T> Entity::GetComponent(ComponentType componentType)
	{
		// Verify that this component type is attached to the Entity so that the user doesn't try to read invalid memory.
		assert(m_pComponentArray[componentType]);
		return std::static_pointer_cast<T>(m_pComponentArray[componentType]);
	}

	void Entity::SetName(std::string name)
	{
		name = m_name;
	}

	std::string Entity::GetName()
	{
		return m_name;
	}*/
}