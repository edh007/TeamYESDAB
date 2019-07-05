#pragma once

#include <fmod.hpp>
#include <fmod_dsp.h>
#include <fmod_errors.h>

#include "Engine.h"

//#pragma comment(lib, "fmod_vc.lib")

namespace gi
{
  enum SoundType
  {
    BACKGROUND,
    ATTACK,
    KILLED,
    ALERT,
    GUNSHOT,
    EXPLOSION,

    SOUND_COUNT
  };

  class SoundManager
  {
  public:
    SoundManager(Engine* pEngine);
    ~SoundManager() {}

    //static SoundManager* instance;
    //static SoundManager* sharedManager();

    void Initialize();
    void AddSound();
    void Play(int type);
    void Pause(int chNum);
    void Stop(int chNum);
    void SetVolume(int chNum);
    void ErrorCheck(FMOD_RESULT result);

    // Test func
    void PlayEffectSound(SoundType st);

    void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);
    void DrawManager();
  private:
    FMOD::System*  m_pSystem;
    FMOD::Channel* m_ch[10];
    FMOD::Sound*   m_pSounds[10];
    FMOD_RESULT    m_result;
    float          m_volume;
    void*          m_pExtraDriverData = 0;

    bool m_paused;
    bool m_bgmPlayed;

    Engine* m_pEngine;

    friend class Engine;

    std::string m_dir;
  };
}