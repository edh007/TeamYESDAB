#pragma once

#include "ComponentContainer.h"
#include "Behavior.h"

#include <vector>
#include <string>

namespace gi
{
	//typedef unsigned int EntityID;

	class Entity
	{
	public:
		Entity(Entity* pOwner, const std::string& name);
		virtual ~Entity() = 0;

		std::string GetName() const { return m_name; }
		bool IsDead() const { return m_isDead; }
        void SetName(std::string _name) { m_name = _name; }

		Entity* GetParentPtr() const { return m_pParent; }
        std::vector<Entity*> GetChildPtr() const { return m_childs; }
        std::vector<Entity*>::iterator* GetChildIterator() { return &m_childs.begin(); }
        void SetChild(Entity* _entity) { m_childs.push_back(_entity); }
        void SetParent(Entity* _entity) { m_pParent = _entity; }
		ComponentContainer& GetComponentContainer() { return m_components; }
		BehaviorContainer& GetBehaviorContainer() { return m_behaviors; }

		bool _isSelected = false;
		//std::string _name;
		bool _isActive = true;      /*!< Can be used by Core's to determine if an actor should be processed or not */
		//bool        _savedIsActive; /*!< Value used when reseting the entity to it's original state */

	private:
		std::string m_name;
		bool m_isDead;

		Entity* m_pParent;
		std::vector<Entity*> m_childs;

		ComponentContainer m_components;
		BehaviorContainer m_behaviors;

		friend class Space;
	};

}

	/*class Entity
	{
	public:

		//void AddComponent(std::shared_ptr<Component> component);
		//std::shared_ptr<Component> GetComponent(ComponentType componentType);
		//bool HasComponent(ComponentType componentType);
		//template <typename T>
		//std::shared_ptr<T> GetComponent(ComponentType componentType);

		//void SetName(std::string name);
		std::string GetName();

		//#define GET_COMPONENT( type ) \
		//  GetComponent<type>(CT_##type)

	private:
		//std::shared_ptr<Component> m_pComponentArray[CT_COUNT];
		std::string m_name;
	};*/