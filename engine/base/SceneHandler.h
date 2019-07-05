#pragma once

#include <vector>
#include "Engine.h"

namespace gi
{
	class Scene;

	class SceneHandler
	{
	public:
		Scene* GetCurrScene();
		void StartScene(Scene* pScene);
		void PushScene(Scene* pScene);
		void PopScene();

		void SetNextScene(Scene* pScene);
		void ReplaceScene(Scene* pScene);

    void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);

	private:
		SceneHandler(Engine* pEngine);
		~SceneHandler();

		Scene* m_pCurrScene;
		Scene* m_pNextScene;

		std::vector<Scene *> m_scenes;

    Engine* m_pEngine;

		friend class Engine;
	};
}