#pragma once

#include "Engine.h"
#include "Entity.h"

namespace gi
{

  class CollisionManager
  {
  public:
    CollisionManager(Engine* pEngine, EntityList* pEntityList);
    ~CollisionManager() {}

    void Initialize();
    void ManageCollsion();

    //void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);

  private:
    EntityList* m_pEntityList;
    EntityList  m_collisionList;

    Engine* m_pEngine;

    friend class Engine;
  };
}