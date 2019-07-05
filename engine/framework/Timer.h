#pragma once

// TODO(JIN) : Precompiled
#include <Windows.h>
#include <SDL.h>
#include "Engine.h"

namespace gi
{
	class Timer
	{
	public:
		Timer(Engine* pEngine);
		~Timer();

		void Start();
		void Stop();

		float GetElapsedSec();
		float GetElapsedMlSec();
		float GetElapsedTimeMcSec();

    void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);

#if 0 
		int GetWindowRefreshRate(SDL_Window* pWnd);
		float GetSecondsElapsed(long lastCounter, long currCounter);

		void CapFrameRate();
#endif
	private:
		bool m_isStopped;
		float m_frequency;

		Uint64 m_currCount;
		Uint64 m_lastCount;

    Engine* m_pEngine;
#if 0
		int m_monitorRefreshHz;
		int m_gameUpdateHz;
		float m_targetSecondsPerFrame;
#endif
	};
}