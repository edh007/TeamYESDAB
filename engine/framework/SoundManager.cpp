#include "framework/SoundManager.h"
#include <windows.h>
#include "imgui.h"

namespace gi
{
  //SoundManager* SoundManager::sharedManager()
  //{
  //  if (instance == NULL)
  //    instance = new SoundManager;
  //
  //  return instance;
  //}

  SoundManager::SoundManager(Engine* pEngine) : m_pEngine(pEngine), 
    m_paused(true), m_volume(0.5f), m_bgmPlayed(false)
  {

  }

  void SoundManager::Initialize()
  {
    m_result = System_Create(&m_pSystem);
    ErrorCheck(m_result);
    m_result = m_pSystem->init(100, FMOD_INIT_NORMAL, m_pExtraDriverData);
    ErrorCheck(m_result);

    AddSound();
  }

  void SoundManager::AddSound()
  {
    m_result = m_pSystem->createSound("../../resources/audio/ingame_bgm.ogg", FMOD_DEFAULT, 0, &m_pSounds[BACKGROUND]);
    ErrorCheck(m_result);
    m_dir = "../../resources/audio/ingame_bgm.ogg";

    m_result = m_pSystem->createSound("../../resources/audio/alert.wav", FMOD_DEFAULT, 0, &m_pSounds[ALERT]);
    ErrorCheck(m_result);

    m_result = m_pSystem->createSound("../../resources/audio/gunshot.ogg", FMOD_DEFAULT, 0, &m_pSounds[GUNSHOT]);
    ErrorCheck(m_result);

    m_result = m_pSystem->createSound("../../resources/audio/explosion.ogg", FMOD_DEFAULT, 0, &m_pSounds[EXPLOSION]);
    ErrorCheck(m_result);
  }

  void SoundManager::Play(int type)
  {
    m_pSystem->update();
    m_result = m_pSystem->playSound(m_pSounds[type], 0, false, &m_ch[type]);
    m_ch[type]->setVolume(m_volume);
    ErrorCheck(m_result);
  }

  void SoundManager::Pause(int chNum)
  {
    m_ch[chNum]->setPaused(m_paused);
    m_paused = !m_paused;
  }

  void SoundManager::Stop(int chNum)
  {
    m_ch[chNum]->stop();
  }

  void SoundManager::SetVolume(int chNum)
  {
    m_ch[chNum]->setVolume(m_volume);
  }

  void SoundManager::ErrorCheck(FMOD_RESULT result)
  {
    if (result != FMOD_OK)
    {
      TCHAR szStr[256] = { 0 };
      MultiByteToWideChar(CP_ACP, NULL, FMOD_ErrorString(result), -1, (LPWSTR)szStr, 256);
      MessageBox(nullptr, szStr, (LPCSTR)"Sound Error", MB_OK);
    }
  }

  void SoundManager::PlayEffectSound(SoundType st)
  {
    bool isPlaying;

    m_ch[st]->isPlaying(&isPlaying);

    if (isPlaying == true)
      Stop(st);

    Play(st);
  }

  void SoundManager::HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
  {
    if (msg == Message::KEY_RIGHT && !m_bgmPlayed)
    {
      m_bgmPlayed = true;
      Play(BACKGROUND);
    }
    else if(msg == Message::KEY_LEFT)
    {
      Pause(BACKGROUND);
    }
    else if (msg == Message::KEY_DOWN)
    {
      m_volume -= 0.1f;
      if (m_volume < 0.f)
        m_volume = 0.f;

      SetVolume(BACKGROUND);
    }
    else if (msg == Message::KEY_UP)
    {
      m_volume += 0.1f;
      if (m_volume > 1.f)
        m_volume = 1.f;
      SetVolume(BACKGROUND);
    }
    else if (msg == Message::FIRE_BULLET)
    {
      bool isPlaying;

      m_ch[ALERT]->isPlaying(&isPlaying);

      if (isPlaying == true)
        Stop(ALERT);

      Play(ALERT);
    }
  }


  void SoundManager::DrawManager()
  {
      if (ImGui::CollapsingHeader("Sound Manager"))
      {
          ImGui::PushItemWidth(160);
          {

              float textWidth;
              float buttonSpacing;

              if (ImGui::GetWindowWidth() < 700)
              {
                  textWidth = 300 - (700 - ImGui::GetWindowWidth());
                  buttonSpacing = textWidth + 10;
              }
              else
              {
                  textWidth = 300;
                  buttonSpacing = 310;
              }

              // Actor name + active state
              {
                  static char buf2[32] = "";
                  ImGui::Text("Sound name: %s\n", m_dir.c_str());
                  ImGui::PushItemWidth(textWidth);
                  {
                      if (ImGui::InputText("Sound", buf2, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                      {
                          std::string dir = "../../resources/audio/";
                          m_dir = dir + buf2;
                          buf2[0] = '\0';

                          Stop(BACKGROUND);
                          m_result = m_pSystem->createSound(m_dir.c_str(), FMOD_DEFAULT, 0, &m_pSounds[BACKGROUND]);
                          ErrorCheck(m_result);
                          Play(BACKGROUND);
                      }
                      ImGui::PopItemWidth();
                  }
                  //ImGui::SameLine(buttonSpacing);

              }


          }
          ImGui::PopItemWidth();
      }

  }
}
