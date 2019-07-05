#pragma once

#include "math/Math.h"
#include "base/Component.h"

namespace gi
{
  class RigidBodyComponent : public Component
  {
    enum class RigidBodyType
    {
      CIRCLE_COLLISION,
      BOX_COLLISION,
      COUNT
    };

  public:
    static const std::string COMPONENT_ID;

    static RigidBodyComponent* CreateRigidBodyComponent(Entity* pOwner);

    void  SetRigidBodySize(float size);
    float GetRigidBodySize() const;

  private:

    explicit RigidBodyComponent(Entity* pEntity);
    virtual ~RigidBodyComponent();

    // Rigid body is made of a sphere (or a circle)
    float m_rigidBodySize;
  };
}