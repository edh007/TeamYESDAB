#include "base/CollisionManager.h"
#include "Space.h"

namespace gi
{
  CollisionManager::CollisionManager(Engine* pEngine, EntityList* pEntityList) : m_pEngine(pEngine),
    m_pEntityList(pEntityList)
  {

  }

  void CollisionManager::Initialize()
  {

  }

  void CollisionManager::ManageCollsion()
  {
    // First assign collision objects to the list
    EntityList::iterator it = m_pEntityList->begin();
    for (; it != m_pEntityList->end(); ++it)
    {
      if ((*it)->GetComponentContainer().HasComponent(RigidBodyComponent::COMPONENT_ID))
        m_collisionList.push_back(*it);
    }

    // Check if there are more than one collision objects in the list
    if (m_collisionList.size() > 1)
    {
      EntityList::iterator it1 = m_collisionList.begin();
      EntityList::iterator it2 = it1;
      ++it2;

      for (; it1 != m_collisionList.end(); ++it1)
      {
        for (; it2 != m_collisionList.end(); ++it2)
        {
          if (it1 != it2)
          {
            Vec3 pos1 = (*it1)->GetComponentContainer().GetComponent<ComponentTransform>()->GetPositionVec();
            Vec3 pos2 = (*it2)->GetComponentContainer().GetComponent<ComponentTransform>()->GetPositionVec();

            float size1 = (*it1)->GetComponentContainer().GetComponent<RigidBodyComponent>()->GetRigidBodySize();
            float size2 = (*it2)->GetComponentContainer().GetComponent<RigidBodyComponent>()->GetRigidBodySize();

            // Do sphere collision
            if (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2)) < size1 + size2)
            {
              if (std::find(m_markForErase.begin(), m_markForErase.end(), *it1) == m_markForErase.end())
                m_markForErase.push_back(*it1);

              if (std::find(m_markForErase.begin(), m_markForErase.end(), *it2) == m_markForErase.end())
                m_markForErase.push_back(*it2);
            }
          }
        }
      }
    }

    m_collisionList.clear();
  }

  /*void CollisioinManager::HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
  {
  }*/
}