#pragma once

#include <string>

namespace gi
{
  /*enum ComponentType
  {
    CT_TRANSFORM,
    CT_CAMERA,
    CT_HEALTH,
    CT_BULLET,
    CT_LIFETIME,
    CT_PARTICLE,

    CT_COUNT
  };

  class Component
  {
  public:
    Component(ComponentType componentType) : m_type(componentType) {}
    virtual ~Component() {}

    const ComponentType m_type;

  private:
  };

  typedef std::shared_ptr<Component> ComponentPtr;*/

	class Entity;

	class Component
	{
	public:
		explicit Component(Entity* pOwner);
		virtual ~Component() = 0;
		

	protected:

		virtual Entity* GetOwner() const { return m_pOwner; }

		Entity* m_pOwner;
	};
}
