#pragma once

#include "math/Math.h"
#include "base/Component.h"

#include <string>

namespace gi
{
  class ComponentPhysics : public Component
  {
  public:
    static const std::string COMPONENT_ID;

    static ComponentPhysics* CreateComponentPhysics(Entity* pOwner);

    void SetVelocity(Vec3 velocity);
    void SetVelocityX(float x);
    void SetVelocityY(float y);
    void SetVelocityZ(float z);

    Vec3 GetVelocity() const;

    void AddVelocity(Vec3 velocity);
    void AddVelocityX(float x);
    void AddVelocityY(float y);
    void AddVelocityZ(float z);

  private:

    explicit ComponentPhysics(Entity* pEntity);
    virtual ~ComponentPhysics();

    Vec3 m_velocity;
    float m_maxVelocity;
  };
}