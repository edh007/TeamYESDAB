#pragma once

#include "SDL.h"
#include <bitset>
#include "Engine.h"

namespace gi
{
	class Input
	{
	public:
		bool IsKeyTriggered(SDL_Scancode key) const;
		bool IsKeyPressed(SDL_Scancode key) const;
		bool IsKeyReleased(SDL_Scancode key) const;
		bool IsMouseTriggered(unsigned key) const;
		bool IsMousePressed(unsigned key) const;
		bool IsMouseReleased(unsigned key) const;

    // TODO(DONGHO) : TEST FUNC FOR MOUSE X, Y
    float GetMouseX() { return static_cast<float>(m_mousePosX); }
    float GetMouseY() { return static_cast<float>(m_mousePosY); }

	private:
		Input(Engine* pEngine);
		~Input();

		void Initialize();
    void Update(const SDL_Event& event);
		void Shutdown();

    void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);
		void ReceiveEvent(const SDL_Event& event);

		//void ReceiveMouseEvent(const SDL_Event& event);
		void ReceiveKeyboardEvent(const SDL_KeyboardEvent& keyEvent);

		int m_maxKeyNum;
		Uint8* m_prevKeyboardInputs;
		Uint8* m_currKeyboardInputs;
		
		// TODO (JIN) : Need to change to Vector
		int m_mousePosX, m_mousePosY;
		std::bitset<SDL_BUTTON_RIGHT/*SDL_BUTTON_X2*/> m_prevMouseInputs;
		std::bitset<SDL_BUTTON_RIGHT/*SDL_BUTTON_X2*/> m_currMouseInputs;

    Engine* m_pEngine;

		friend class Engine;
	};

}