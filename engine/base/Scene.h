#pragma once

#include <unordered_map>

#include "base/Entity.h"

namespace gi
{
	class Scene
	{
	public:
		virtual ~Scene() {}

		virtual void Load() {}
		virtual void Init() {}
		virtual void Update(float) {}
		virtual void Shutdown() {}
		virtual void Unload() {}

  private:
    std::unordered_map<std::string ,Entity*> m_entityMap;
	};
}
