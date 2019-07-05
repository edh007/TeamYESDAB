#include "ComponentContainer.h"
#include "Component.h"


//gi::Component* gi::ComponentContainer::GetComponent(const std::string componentID) const
//{
//	auto& it = m_components.find(componentID);
//
//	if (it == m_components.end())
//		return nullptr;
//	else
//		return it->second;
//}

void gi::ComponentContainer::AddComponent(Component* pComponent, const std::string componentID)
{
	auto& it = m_components.find(componentID);

	if(it != m_components.end())
	{
		// ASSERT
	}

	m_components.emplace(componentID, pComponent);
}
void gi::ComponentContainer::RemoveComponent(const std::string componentID)
{
	m_components.erase(componentID);
}

void gi::ComponentContainer::ClearComponents()
{
	m_components.clear();
}

bool gi::ComponentContainer::IsEmpty() const
{
	return m_components.empty();
}

bool gi::ComponentContainer::HasComponent(const std::string componentID)
{
  if (m_components.find(componentID) == m_components.end())
    return false;
  else
    return true;
}

gi::ComponentContainer::ComponentContainer(Entity* pOwner)
	: m_pOwner(pOwner)
{

}

gi::ComponentContainer::~ComponentContainer()
{
	ClearComponents();
	m_pOwner = nullptr;
}
