#pragma once

#include "math\Vec2.h"
#include <string>
#include <vector>

namespace gi
{
	class Entity;
	class Component;

	class Space
	{
		typedef std::vector<Entity*> EntityList;
	public:
		//void AddComponentToObject(Entity* pOwner, Component* pComponent);

		explicit Space(){}
		~Space(){}

		void Initialize();
		void Shutdown(/*bool clearAll = true*/);

		Entity* FindEntity(const std::string& entityName);
		// TODO (JIN) : check id can be more useful if id is string, not unsigned int
		//Entity* FindEntity(unsigned int entityID);

		void AddEntity(Entity* pEntity);
		void RemoveEntity(Entity* pEntity);
		void RemoveEntity(const std::string& entityName);
		// TODO (JIN) : this function remove all the entities that dead state is true, so change the name
		void UpdateEntities();

		void UpdateBehaviors(float dt);


		void TogglePause();
		bool GetPauseState() const;

		//Vec2 GetWorldSize2D() const;
		//Vec2 GetMouseWorldPos() const;

		//void AddComponentToObject(Entity* pOwner, Component* pComponent);

	private:
		EntityList m_entities;
		//EntityList m_deadEntities;
		// TODO (JIN) : need functions to help chaning cameras
		Component* m_pMainCamera; 
		bool m_pause;

	};
}