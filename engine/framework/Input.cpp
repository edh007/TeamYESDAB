#include "Input.h"
#include "components\ComponentPhysics.h"

namespace gi
{
  bool Input::IsKeyTriggered(SDL_Scancode key) const
  {
    return m_currKeyboardInputs[key] && !m_prevKeyboardInputs[key];
  }
  bool Input::IsKeyPressed(SDL_Scancode key) const
  {
    return m_currKeyboardInputs[key] && m_prevKeyboardInputs[key];
  }
  bool Input::IsKeyReleased(SDL_Scancode key) const
  {
    return !m_currKeyboardInputs[key] && m_prevKeyboardInputs[key];
  }

  bool Input::IsMouseTriggered(unsigned key) const
  {
    return m_currMouseInputs[key] && !m_prevMouseInputs[key];
  }

  bool Input::IsMousePressed(unsigned key)const
  {
    return m_currMouseInputs[key] && m_prevMouseInputs[key];
  }

  bool Input::IsMouseReleased(unsigned key) const
  {
    return !m_currMouseInputs[key] && m_prevMouseInputs[key];
  }

  Input::Input(Engine* pEngine) : m_pEngine(pEngine),
    m_mousePosX(0), m_mousePosY(0), m_maxKeyNum(0),
    m_prevKeyboardInputs(nullptr), m_currKeyboardInputs(nullptr)
  {

  }
  Input::~Input()
  {

  }


  void Input::Initialize()
  {
    // https://www.gamedev.net/forums/topic/441780-sdl_getkeystate-and-sdl_pumpevents/
    SDL_PumpEvents();

    m_currKeyboardInputs = const_cast<Uint8*>(SDL_GetKeyboardState(&m_maxKeyNum));
    m_prevKeyboardInputs = new Uint8[m_maxKeyNum];

    //std::memcpy(m_prevKeyboardInputs, m_currKeyboardInputs, sizeof(Uint8) * m_maxKeyNum);
  }
  void Input::Shutdown()
  {
    delete[] m_prevKeyboardInputs;
    m_prevKeyboardInputs = nullptr;
    m_currKeyboardInputs = nullptr;
  }
  void Input::ReceiveEvent(const SDL_Event& event)
  {
    // If the input is coming from keyboard
    if (event.key.keysym.scancode < 512 && event.key.keysym.scancode >= 0)
      Update(event);

    std::memcpy(m_prevKeyboardInputs, m_currKeyboardInputs, sizeof(Uint8) * m_maxKeyNum);
    SDL_PumpEvents();

    // Update keyboard inputs
    m_currKeyboardInputs = const_cast<Uint8*>(SDL_GetKeyboardState(nullptr));

    // Gets mouse location
    Uint32 currMouseState = SDL_GetMouseState(&m_mousePosX, &m_mousePosY);

    for (unsigned i = SDL_BUTTON_LEFT; i <= SDL_BUTTON_RIGHT/*SDL_BUTTON_X2*/; ++i)
    {
      m_currMouseInputs[i - 1] = static_cast<bool>(currMouseState & SDL_BUTTON(i));
    }
  }

  void Input::Update(const SDL_Event& event)
  {
    SDL_Scancode currScanCode = event.key.keysym.scancode;

    // If the key has been triggered
    if (IsKeyTriggered(currScanCode))
    {
      if (currScanCode == SDL_SCANCODE_ESCAPE)
        m_pEngine->AddMsg(nullptr, nullptr, Message::QUIT_PROGRAM);

      if (currScanCode == SDL_SCANCODE_SPACE)
        m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_SPACE);

      //  if (currScanCode == SDL_SCANCODE_W)
      //    m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_W_TRIGGERED);

      //  if (currScanCode == SDL_SCANCODE_S)
      //    m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_S_TRIGGERED);

      //  if (currScanCode == SDL_SCANCODE_A)
      //  {
      //    Entity* pEntity = m_pEngine->GetObjectList()->find("mainCharacter")->second;
      //    m_pEngine->AddMsg(pEntity, nullptr, Message::KEY_A_PRESSED);
      //  }

      //  if (currScanCode == SDL_SCANCODE_D)
      //  {
      //    Entity* pEntity = m_pEngine->GetObjectList()->find("mainCharacter")->second;
      //    m_pEngine->AddMsg(pEntity, nullptr, Message::KEY_D_PRESSED);
      //  }

      if (currScanCode == SDL_SCANCODE_UP)
        m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_UP);

      if (currScanCode == SDL_SCANCODE_DOWN)
        m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_DOWN);

      if (currScanCode == SDL_SCANCODE_LEFT)
        m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_LEFT);

      if (currScanCode == SDL_SCANCODE_RIGHT)
        m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_RIGHT);

      if (currScanCode == SDL_SCANCODE_Z)
      {
        Entity* pEntity = m_pEngine->GetMainCharacterEntity();
        m_pEngine->AddMsg(pEntity, nullptr, Message::FIRE_BULLET);
      }

      if (currScanCode == SDL_SCANCODE_R)
          m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_R);
    }

    //// If the key has been pressed
    //if (IsKeyPressed(currScanCode))
    //{
    //  if (currScanCode == SDL_SCANCODE_W)
    //    m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_W_PRESSED);

    //  if (currScanCode == SDL_SCANCODE_A)
    //  {
    //    Entity* pEntity = m_pEngine->GetObjectList()->find("mainCharacter")->second;
    //    m_pEngine->AddMsg(pEntity, nullptr, Message::KEY_A_PRESSED);
    //  }

    //  if (currScanCode == SDL_SCANCODE_S)
    //    m_pEngine->AddMsg(nullptr, nullptr, Message::KEY_S_PRESSED);

    //  if (currScanCode == SDL_SCANCODE_D)
    //  {
    //    Entity* pEntity = m_pEngine->GetObjectList()->find("mainCharacter")->second;
    //    m_pEngine->AddMsg(pEntity, nullptr, Message::KEY_D_PRESSED);
    //  }
    //}

    //if (IsKeyReleased(currScanCode))
    //{
    //  if (currScanCode == SDL_SCANCODE_A)
    //  {
    //    Entity* pEntity = m_pEngine->GetObjectList()->find("mainCharacter")->second;
    //    m_pEngine->AddMsg(pEntity, nullptr, Message::KEY_A_RELEASED);
    //  }

    //  if (currScanCode == SDL_SCANCODE_D)
    //  {
    //    Entity* pEntity = m_pEngine->GetObjectList()->find("mainCharacter")->second;
    //    m_pEngine->AddMsg(pEntity, nullptr, Message::KEY_D_RELEASED);
    //  }
    //}



    // Loop through alphabet keyboard inputs
    int it = SDL_Scancode::SDL_SCANCODE_A;
    Entity* pEntity = nullptr;

    while (it <= SDL_SCANCODE_Z)
    {
      if (it == SDL_SCANCODE_W || it == SDL_SCANCODE_S || it == SDL_SCANCODE_A || it == SDL_SCANCODE_D
        || it == SDL_SCANCODE_Z)
        pEntity = m_pEngine->GetMainCharacterEntity();

      if (IsKeyTriggered(static_cast<SDL_Scancode>(it)))
      {
        int letterA = static_cast<int>(Message::KEY_A_TRIGGERED);
        m_pEngine->AddMsg(pEntity, nullptr, static_cast<Message>(letterA + it - SDL_Scancode::SDL_SCANCODE_A));
      }
      else if (IsKeyPressed(static_cast<SDL_Scancode>(it)))
      {
        int letterA = static_cast<int>(Message::KEY_A_PRESSED);
        m_pEngine->AddMsg(pEntity, nullptr, static_cast<Message>(letterA + it - SDL_Scancode::SDL_SCANCODE_A));
      }
      else if (IsKeyReleased(static_cast<SDL_Scancode>(it)))
      {
        int letterA = static_cast<int>(Message::KEY_A_RELEASED);
        m_pEngine->AddMsg(pEntity, nullptr, static_cast<Message>(letterA + it - SDL_Scancode::SDL_SCANCODE_A));
      }

      pEntity = nullptr;
      ++it;
    }
  }

  void Input::HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
  {
  }
}