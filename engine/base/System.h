#pragma once

#include <map>

#include "base/Message.h"
#include "Engine.h"

namespace gi
{
  enum class SystemType
  {
    APPLICATION,
    RENDERER,
    INPUT,
    TIMER,
    SYSTEM_COUNT
  };

  class System
  {
  public:

    System(Engine* pGameEngine) : m_pEngine(pGameEngine)
    {
    }
    virtual ~System() {}

    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
    virtual void AddMsg(Entity* pEntity1, Entity* pEntity2, Message msg) = 0;

  protected:
    Engine* m_pEngine;

    //std::unordered_map<Entity*> m_entityMap;
  };
}