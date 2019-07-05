#pragma once

// TEST
#include "components\ComponentTransform.h"
#include <functional>
#include <vector>

namespace gi
{
	class Entity;
	class Behavior;

	class BehaviorContainer
	{
	public:
		//static 

		void Update(float dt);

		void AddBehavior(Behavior* pBehavior, bool active);
		void RemoveBehavior(Behavior* pBehavior);
		void Clear();

		void SetAllActive(bool active);

	private:
		std::vector<Behavior*> m_behaviors;
	};

	class Behavior
	{
	public:
		Behavior(Entity* pOwner);
		virtual ~Behavior();

		virtual bool GetActive() const;
		virtual void SetActive(bool active);

		virtual void Run(float dt);

		virtual Entity* GetTarget() const;
		virtual void SetTarget(Entity* pEntity);

		virtual bool IsDone() const;

		//Entity* GetOriginalTarget() const;
		//Entity* SetOriginalTarget(Entity* pTarget);




		//void ReceiveEvent();
		///virtual void OnCreate

	protected:
		bool m_active;

		Entity* m_pOwner;
		//Entity* m_pOriginalTarget;
		Entity* m_pTarget;


	};

	/*class FiniteTimeBehavior : public Behavior
	{
	public :
		FiniteTimeBehavior(Entity* pOwner = nullptr) : Behavior(pOwner), m_duration(0.f) {}
		~FiniteTimeBehavior() {}

		void Init();

		virtual void Run(float dt);

		Entity* GetTarget() const;
		void SetTarget(Entity* pEntity);

	private:
		float m_duration;
		std::vector<std::function<void(float)>> m_functions;

		void Chase(float dt)
		{
			m_pTarget->GetComponentContainer().GetComponent<ComponentTransform>();
		}

		void Runaway(float dt)
		{
			m_pTarget->GetComponentContainer().GetComponent<ComponentTransform>();
		}

	};*/
}
