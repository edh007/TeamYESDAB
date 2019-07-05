#include "Application.h"

namespace gi
{
	// public 
	void Application::ChangeWindowSize(unsigned w, unsigned h)
	{
		m_wndWidth = w;
		m_wndHeight = h;
	}

	void Application::ToggleFullScreen()
	{
    //if (!m_isFullscreen)
    //{
    //  /* Grab the mouse so that we don't end up with unexpected movement
    //  * when the dimension/position of the window changes. */
    //  SDL_SetRelativeMouseMode(SDL_TRUE);

    //  /* Convert flag enum to unsigned and Check the fullscreen state
    //  * Uint32 FullscreenFlag= SDL_WINDOW_FULLSCREEN; */
    //  m_isFullscreen = (SDL_GetWindowFlags(m_pWindow) == SDL_WINDOW_FULLSCREEN);
    //  //m_isFullscreen = SDL_GetWindowFlags(m_pWindow) & FullscreenFlag;

    //  // Toggle Fullscreen
    //  //SDL_SetWindowFullscreen(m_pWindow, m_isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    //  SDL_SetWindowFullscreen(m_pWindow, m_isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);

    //  // TODO (JIN) : It should be controlled in application
    //  SDL_ShowCursor(m_isFullscreen);

    //  // TODO (JIN) : Recalculate Resolution to set appropriate font sizes/UI positions.
    //}

    //SDL_SetRelativeMouseMode(SDL_TRUE);

    if (m_isFullscreen)
      m_isFullscreen = false;
    else
       m_isFullscreen = true;

    SDL_SetWindowFullscreen(m_pWindow, m_isFullscreen);
    //SDL_ShowCursor(m_isFullscreen);
	}

	unsigned Application::GetWindowWidth() const
	{
		return m_wndWidth;
	}

	unsigned Application::GetWindowHeight() const
	{
		return m_wndHeight;
	}

	bool Application::CheckFullScreen() const
	{
		return m_isFullscreen;
	}

	// private
	Application::Application(Engine* pEngine) : m_pEngine(pEngine),
		m_isFullscreen(false), m_wndWidth(800), m_wndHeight(600), m_pWindow(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize()
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			// TODO (JIN) : Need to change in a waythat DEBUG_ASSERT can get SDL_GetError() as parameter.
			// DEBUG_ASSERT("SDL couln't initialize! SDL_ERROR: %s\n", SDL_GetError());

			// TODO (JIN) : Close the application
            return;
		}

		m_pWindow = SDL_CreateWindow("gam300", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_wndWidth, m_wndWidth, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		// DEBUG_ASSERT(! m_pWindow, "Failed to create window\n");
	}

	void Application::Shutdown()
	{
		SDL_DestroyWindow(m_pWindow);

		m_pWindow = nullptr;

		SDL_Quit();
	}

	void Application::ReceiveEvent(const SDL_Event& event)
	{
		event;
	}

  void Application::HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
  {
    if (msg == Message::FULL_SCREEN)
      ToggleFullScreen();
  }
}
