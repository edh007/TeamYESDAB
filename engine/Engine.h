#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "base/Entity.h"
#include "base/Message.h"
#include "graphics/Camera.h"

#include <unordered_map>
#include <vector>

namespace gi
{
	class TestObject : public Entity
	{
	public:
		TestObject() :Entity(nullptr, "new") {}
		~TestObject() override {}

	};


	class Application;
	class Renderer;
	class Timer;
	class Input;
	class Space;
	class SoundManager;
	//TODO(Dongho) : Working on IMGUI
	class GuiManager;

  typedef std::vector<Entity*> ObjectList;
  typedef std::vector<std::pair<Message, std::pair<Entity*, Entity*>>> MessageList;

    //TODO(Dongho) : Working on IMGUI
    class GuiManager;

	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run();
		void Quit();

    void AddMsg(Entity* pEntity1, Entity* pEntity2, Message msg);
    void SendOutMsgs();
    void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);

    float GetDT();
    ObjectList* GetObjectList();
    Entity* GetMainCharacterEntity();
		Space* GetSpace() const;

		void Initialize();
        SoundManager* GetSoundManager() { return m_pSoundManager; }
        Renderer* GetRenderer() { return m_pRenderer; }
        int m_leftBullet = 10;
	private:
		void Shutdown();

		void ProcessEvents();

    // Temporary function for object movement
    void HandleMovement();
    void ClearObjectsMarkedDelete();
    void SolveCollision();

		bool m_quit;
		SDL_Event m_event;

		Application* m_pApp;
		Renderer*    m_pRenderer;
		Input*       m_pInput;
		Timer*       m_pFrameHandler;
    SoundManager* m_pSoundManager;
    
    Entity* m_pMainCharacterEntity;

    ObjectList m_objectList;
    ObjectList m_collisionObjectList;
    std::vector<Entity*> m_markForErase;
    MessageList m_messageList;

    //unsigned m_deleteObject;
		//TODO(Dongho) : Working on IMGUI
		GuiManager* m_pGui;
		Space* m_pSpace;
    
		float m_dt;
	};

	extern Engine* g_pEngine;
}
