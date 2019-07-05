#include "Behavior.h"

#include "framework\Macros.h"
#include "components\ComponentTransform.h"

#include <iostream>

namespace gi
{
	void BehaviorContainer::Update(float dt)
	{
		for(auto& it : m_behaviors)
		{
			if(it->GetActive())
			{
				it->Run(dt);
			}
		}
	}

	void BehaviorContainer::AddBehavior(Behavior* pBehavior, bool active)
	{
		pBehavior->SetActive(active);

		m_behaviors.push_back(pBehavior);
	}

	void BehaviorContainer::RemoveBehavior(Behavior* pBehavior)
	{
		for(auto& it = m_behaviors.begin(); it != m_behaviors.end(); it++)
		{
			if(*it == pBehavior)
			{
				m_behaviors.erase(it);
				return;
			}
		}
	}

	void BehaviorContainer::Clear()
	{
		m_behaviors.clear();
	}

	void BehaviorContainer::SetAllActive(bool active)
	{
		for(auto& it : m_behaviors)
		{
			it->SetActive(active);
		}
	}

	Behavior::Behavior(Entity* pOwner)
		: m_pOwner(pOwner)
	{
		
	}

	Behavior::~Behavior()
	{

	}

	bool Behavior::GetActive() const
	{
		return m_active;
	}

	void Behavior::SetActive(bool active)
	{
		m_active = active;
	}

	void Behavior::Run(float dt)
	{
		std::cout << "Behavior : Test\n";
		GI_UNUSED_PARAM(dt);
	}

	Entity* Behavior::GetTarget() const
	{
		return m_pTarget;
	}

	void Behavior::SetTarget(Entity* pEntity)
	{
		m_pTarget = pEntity;
	}

	bool Behavior::IsDone() const
	{
		return !m_active;
	}

	/*void FiniteTimeBehavior::Init()
	{
		std::function<void(float)> f = [=](float dt)
		{
			//m_pTarget->G
		};

		 m_functions.push_back(f);
	}

	void FiniteTimeBehavior::Run(float dt)
	{
		GI_UNUSED_PARAM(dt);
		std::cout << "Finite Time Behavior : Test\n";
	}

	Entity* FiniteTimeBehavior::GetTarget() const
	{
		return m_pTarget;
	}

	void FiniteTimeBehavior::SetTarget(Entity* pEntity)
	{
		m_pTarget = pEntity;
	}*/
}
