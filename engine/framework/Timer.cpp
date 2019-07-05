#include "Timer.h"

namespace gi
{
  Timer::Timer(Engine* pEngine) : m_pEngine(pEngine),
    m_isStopped(false), m_currCount(0), m_lastCount(0), m_frequency(0.f)
  {
    m_frequency = static_cast<float>(SDL_GetPerformanceFrequency());

#if 0
    m_monitorRefreshHz = GetWindowRefreshRate();
    m_gameUpdateHz = m_monitorRefreshHz / 2;
    m_targetSecondsPerFrame = 1.f / static_cast<float>(m_monitorRefreshHz);
#endif

  }

  Timer::~Timer()
  {
  }

  void Timer::Start()
  {
    m_isStopped = false;
    m_lastCount = SDL_GetPerformanceCounter();
  }

  void Timer::Stop()
  {
    m_isStopped = true;
    m_currCount = SDL_GetPerformanceCounter();
  }

  float Timer::GetElapsedSec()
  {
    return GetElapsedMlSec() * 0.001f;/*0.000001f;*/
  }

  float Timer::GetElapsedMlSec()
  {
    return GetElapsedTimeMcSec() * 0.001f;
  }

  float Timer::GetElapsedTimeMcSec()
  {
    if (!m_isStopped)
    {
      m_currCount = SDL_GetPerformanceCounter();
    }

    return (m_currCount - m_lastCount) * (1000000.0f / m_frequency);
  }

  void Timer::HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
  {

  }
}


#if 0 
int gi::Timer::GetWindowRefreshRate(SDL_Window* pWnd)
{
	SDL_DisplayMode mode;
	int displayIndex = SDL_GetWindowDisplayIndex(pWnd);

	// If we can't find the refresh rate, it will return this:
	int defaultRefreshRate = 60;

	if (SDL_GetDesktopDisplayMode(displayIndex, &mode) != 0
		|| mode.refresh_rate == 0)
		return defaultRefreshRate;

	return mode.refresh_rate;
}

float gi::Timer::GetSecondsElapsed(long lastCounter, long currCounter)
{
	return static_cast<float>(currCounter - lastCounter) / m_frequency;
}

void gi::Timer::CapFrameRate()
{
	if(GetSecondsElapsed(m_lastCounter, SDL_GetPerformanceCounter()) < m_targetSecondsPerFrame)
	{
		while (GetSecondsElapsed(m_lastCounter, SDL_GetPerformanceCounter()) < m_targetSecondsPerFrame)
		{
			SDL_Delay((m_targetSecondsPerFrame - GetSecondsElapsed(m_lastCounter, SDL_GetPerformanceCounter())) * 1000.f);

		}
	}
	else
	{
		// TODO(JIN) : MISSED FRAME RATE!
		// TODO(JIN) : Logging
	}



	if(GetSecondsElapsed(m_lastCounter, SDL_GetPerformanceCounter()) < m_targetSecondsPerFrame)
	{
		unsigned timeToSleep = ((m_targetSecondsPerFrame - GetSecondsElapsed(m_lastCounter, SDL_GetPerformanceCounter())) * 1000) - 1;
		SDL_Delay(timeToSleep);
		//Assert(GetSecondsElapsed(m_lastCounter, SDL_GetPerformanceCounter()) < m_targetSecondsPerFrame)
		while (GetSecondsElapsed(m_lastCounter, SDL_GetPerformanceCounter()) < m_targetSecondsPerFrame)
		{
			
		}
	}
}

#endif
