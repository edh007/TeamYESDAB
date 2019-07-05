#include "components/RigidBodyComponent.h"

const std::string gi::RigidBodyComponent::COMPONENT_ID = "gi_cmp_rigidBody";

gi::RigidBodyComponent::RigidBodyComponent(Entity* pEntity)
  : Component(pEntity), m_rigidBodySize(0.f)
{
}

gi::RigidBodyComponent::~RigidBodyComponent()
{
	m_pOwner = nullptr;
}

gi::RigidBodyComponent* gi::RigidBodyComponent::CreateRigidBodyComponent(Entity* pOwner)
{
  RigidBodyComponent* pRigidBody = new RigidBodyComponent(pOwner);

	return pRigidBody;
}

void gi::RigidBodyComponent::SetRigidBodySize(float size)
{
  m_rigidBodySize = size;
}

float gi::RigidBodyComponent::GetRigidBodySize() const
{
  return m_rigidBodySize;
}