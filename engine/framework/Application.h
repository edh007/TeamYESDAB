#pragma once

#include  "SDL.h"
#include "Engine.h"

namespace gi
{

	class Application
	{
	public:
		void ChangeWindowSize(unsigned w, unsigned h);
		void ToggleFullScreen();

		// TODO(JIN) : Change return value to Vec2(width, height)
		unsigned GetWindowWidth() const;
		unsigned GetWindowHeight() const;

		bool CheckFullScreen() const;

    SDL_Window* GetWindow() { return m_pWindow; }
	private:		
    Application(Engine* pEngine);
    ~Application();

    void Initialize();
    void Update();
    void Shutdown();
    void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);

		void ReceiveEvent(const SDL_Event& event);

		// member variable
		bool m_isFullscreen;

		unsigned m_wndWidth;
		unsigned m_wndHeight;

    Engine* m_pEngine;
    SDL_Window* m_pWindow;

		friend class Engine;
	};

};