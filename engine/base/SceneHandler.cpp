#include "SceneHandler.h"

#include "Scene.h"

gi::Scene* gi::SceneHandler::GetCurrScene()
{
	return m_pCurrScene;
}

void gi::SceneHandler::StartScene(Scene* pScene)
{
	m_pCurrScene = pScene;
	// TODO(JIN) : Need to shutdown and delete
}

void gi::SceneHandler::PushScene(Scene* pScene)
{
	m_scenes.push_back(pScene);
	m_pNextScene = pScene;
}

void gi::SceneHandler::PopScene()
{

	//DEBUG_ASSERT(_pCurrScene == nullptr, "current scene shouldn't be null pointer\n");

	m_scenes.pop_back();

	if (m_scenes.size() == 0)
	{
		// TODO (JIN) : Shutdown system and quit window
	}
	//else
}

void gi::SceneHandler::SetNextScene(Scene* pScene)
{
	if(pScene)
		m_pNextScene = pScene;
}

void gi::SceneHandler::ReplaceScene(Scene* pScene)
{
	if (pScene)
	{
		m_pCurrScene->Shutdown();
		m_pCurrScene->Unload();

		m_pCurrScene = pScene;

		m_pCurrScene->Init();
		m_pCurrScene->Load();
	}		
}

gi::SceneHandler::SceneHandler(Engine* pEngine) : m_pEngine(pEngine)
{
}

gi::SceneHandler::~SceneHandler()
{
}
