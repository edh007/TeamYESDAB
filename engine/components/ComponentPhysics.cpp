#include "components/ComponentPhysics.h"

const std::string gi::ComponentPhysics::COMPONENT_ID = "gi_cmp_physics";

gi::ComponentPhysics::ComponentPhysics(Entity* pEntity)
  : Component(pEntity), m_velocity(Vec3(0, 0, 0))
{
}

gi::ComponentPhysics::~ComponentPhysics()
{
	m_pOwner = nullptr;
}

gi::ComponentPhysics* gi::ComponentPhysics::CreateComponentPhysics(Entity* pOwner)
{
  ComponentPhysics* pPhysics = new ComponentPhysics(pOwner);

	return pPhysics;
}

void gi::ComponentPhysics::SetVelocity(Vec3 velocity)
{
  m_velocity = velocity;
}

void gi::ComponentPhysics::SetVelocityX(float x)
{
	m_velocity.x = x;
}
void gi::ComponentPhysics::SetVelocityY(float y)
{
	m_velocity.y = y;
}
void gi::ComponentPhysics::SetVelocityZ(float z)
{
	m_velocity.z = z;
}

Vec3 gi::ComponentPhysics::GetVelocity() const
{
  return m_velocity;
}


void gi::ComponentPhysics::AddVelocity(Vec3 velocity)
{
	m_velocity += velocity;
}
void gi::ComponentPhysics::AddVelocityX(float x)
{
	m_velocity.x += x;
}
void gi::ComponentPhysics::AddVelocityY(float y)
{
	m_velocity.y += y;
}
void gi::ComponentPhysics::AddVelocityZ(float z)
{
	m_velocity.z += z;
}