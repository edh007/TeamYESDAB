#include "Space.h"

#include "Entity.h"

void gi::Space::Initialize()
{
}

void gi::Space::Shutdown()
{
}

gi::Entity* gi::Space::FindEntity(const std::string& entityName)
{
	for(auto& it : m_entities)
	{
		if (it->GetName() == entityName)
			return it;
	}

	return nullptr;
}

void gi::Space::AddEntity(Entity* pEntity)
{
	//size_t test = m_entities.size();
	//m_entities.emplace();
	m_entities.emplace_back(pEntity);
}

void gi::Space::RemoveEntity(Entity* pEntity)
{
	for(auto& it : m_entities)
	{
		if(it == pEntity)
			pEntity->m_isDead = true;
	}
}

void gi::Space::RemoveEntity(const std::string& entityName)
{
	for (auto& it : m_entities)
	{
		if (it->GetName() == entityName)
			it->m_isDead = true;
	}
}

void gi::Space::UpdateEntities()
{
	for(auto it = m_entities.begin(); it != m_entities.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->GetComponentContainer().ClearComponents();
			// TODO (JIN) : deleting object here looks bad. Fix it.
			delete (*it);
			m_entities.erase(it++);
			
		}
		else
			++it;
	}
}

void gi::Space::UpdateBehaviors(float dt)
{
	for(auto& it : m_entities)
	{
		it->m_behaviors.Update(dt);
	}
}

void gi::Space::TogglePause()
{
	m_pause = !m_pause;
}

bool gi::Space::GetPauseState() const
{
	return m_pause;
}

/*Vec2 gi::Space::GetMouseWorldPos() const
{
	return Vec2();
}*/
