#include "Engine.h"

#include "framework\Application.h"
#include "graphics\Renderer.h"
#include "framework\Input.h"
#include "framework\Timer.h"
#include "framework\SoundManager.h"
#include <math.h>

#include "components\ComponentTransform.h"
#include "components/ComponentModel.h"
#include "components/ComponentPhysics.h"

#include "components/RigidBodyComponent.h"

// Test
#include "base\Space.h"

// TODO(JIN) : Test for timer
#include <Windows.h>
#include "framework\Debug.h"

//TODO(Dongho) : Working on IMGUI
#include "graphics/GuiManager.h"

namespace gi
{
	//Engine g_pEngine;

	// public member functions
	Engine::Engine()
		: m_pApp(nullptr), m_pRenderer(nullptr), m_pInput(nullptr), m_pSpace(nullptr), m_pGui(nullptr),
    m_pFrameHandler(nullptr), m_quit(false), m_dt(0.f)
	{
		// DebugAssert if g_pEngine is not nullptr
    /*assert(g_pEngine == nullptr);
		g_pEngine = this;*/

	}

  Engine::~Engine()
  {

  }

  void Engine::Run()
  {
    //Initialize();
    m_pFrameHandler->Start();
    m_dt = m_pFrameHandler->GetElapsedSec();

    m_pSoundManager->Play(BACKGROUND);
    
    while (!m_quit)
    {
      // Handle all the events from the SDL
      ProcessEvents();

      // Update
      // TODO (JIN) : Test for Space
      m_pSpace->UpdateBehaviors(m_dt);

      HandleMovement();
      SolveCollision();

      // Draw
      //TODO(Dongho) : Working on IMGUI
      m_pGui->StartNewFrame();
      m_pGui->Update();
      m_pRenderer->Update(m_dt);

      m_pGui->EndOfFrame();

    // Swap window
      SDL_GL_SwapWindow(m_pApp->GetWindow());
      //TODO(Dongho) : Working on IMGUI

      if (m_pInput->IsKeyPressed(SDL_SCANCODE_ESCAPE))
        m_quit = true;
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_W))
        m_pRenderer->GetCamera()->ProcessKeyboard(FORWARD, m_dt);
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_A))
        m_pRenderer->GetCamera()->ProcessKeyboard(LEFT, m_dt);
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_S))
        m_pRenderer->GetCamera()->ProcessKeyboard(BACKWARD, m_dt);
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_D))
        m_pRenderer->GetCamera()->ProcessKeyboard(RIGHT, m_dt);
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_UP))
        m_pRenderer->GetCamera()->ProcessKeyboard(PITCH_UP, m_dt);
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_DOWN))
        m_pRenderer->GetCamera()->ProcessKeyboard(PITCH_DOWN, m_dt);
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_RIGHT))
        m_pRenderer->GetCamera()->ProcessKeyboard(YAW_UP, m_dt);
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_LEFT))
        m_pRenderer->GetCamera()->ProcessKeyboard(YAW_DOWN, m_dt);




      // TODO(JIN) : Test code for input

      if (m_pInput->IsKeyPressed(SDL_SCANCODE_LALT)
        && m_pInput->IsKeyPressed(SDL_SCANCODE_0))

      {
        m_quit = true;
      }
      if (m_pInput->IsKeyPressed(SDL_SCANCODE_LALT)
        && m_pInput->IsKeyPressed(SDL_SCANCODE_1))
      {
        m_quit = true;
      }

      //m_pInput->Update(m_event);

      // Draw
      m_dt = m_pFrameHandler->GetElapsedSec();
      m_pFrameHandler->Start();

      // TODO (JIN) : Test for Space
      m_pSpace->UpdateEntities();

      if (!m_markForErase.empty())
        ClearObjectsMarkedDelete();

      SendOutMsgs();
    }
    Shutdown();
  }

  void Engine::Quit()
  {
    m_quit = true;
  }

  Space* Engine::GetSpace() const
  {
    return m_pSpace;
  }

  // private member functions
  void Engine::Initialize()
  {
    // Initialize App System
    m_pApp = new Application(this);
    m_pApp->Initialize();

    m_pRenderer = new Renderer(this);
    m_pRenderer->Initialize(m_pApp->GetWindow());

    //TODO(Dongho) : Working on IMGUI
    m_pGui = new GuiManager(this);
    m_pGui->Initialize(m_pApp->GetWindow());

    // Initialize Input Framework
    m_pInput = new Input(this);
    m_pInput->Initialize();

    // TODO(JIN) : Test for frame
    // Initialize Frame System
    m_pFrameHandler = new Timer(this);
    //m_pFrameHandler->Initialize();

    // Initialize Space
    m_pSpace = new Space();


    m_pSoundManager = new SoundManager(this);
    m_pSoundManager->Initialize();

    TestObject* pObj;
    ComponentTransform* pTransform;
    RigidBodyComponent* pRigidBody;
    ComponentModel* pModel;
    ParticleComponent* pParticle;

    for (int i = 0; i < 28; ++i)
    {
        pObj = new TestObject;
        pObj->SetName("Cylindrical");

        pTransform = ComponentTransform::CreateComponentTransform(pObj);
        pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(-28.f + 2.1f * i, -1.75f, -28.f);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(1.f, 0.5f, 1.f);

        pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
        pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(1.f);

        pModel = ComponentModel::CreateComponentModel(pObj);
        pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByType(ModelType::CYLINDER);

        pParticle = ParticleComponent::CreateParticleComponent(pObj);
        pParticle->SetParticleVariables(ParticleType::P_BOMB);
        pObj->GetComponentContainer().AddComponent(pParticle, ParticleComponent::COMPONENT_ID);

        m_objectList.push_back(pObj);
    }

    for (int i = 0; i < 27; ++i)
    {
        pObj = new TestObject;
        pObj->SetName("Cylindrical");

        pTransform = ComponentTransform::CreateComponentTransform(pObj);
        pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(-27.9f, -1.75f, -26.f + 2.1f * i);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(1.f, 0.5f, 1.f);

        pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
        pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(1.f);

        pModel = ComponentModel::CreateComponentModel(pObj);
        pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByType(ModelType::CYLINDER);

        pParticle = ParticleComponent::CreateParticleComponent(pObj);
        pParticle->SetParticleVariables(ParticleType::P_BOMB);
        pObj->GetComponentContainer().AddComponent(pParticle, ParticleComponent::COMPONENT_ID);

        m_objectList.push_back(pObj);
    }

    for (int i = 0; i < 25; ++i)
    {
        pObj = new TestObject;
        pObj->SetName("Cylindrical");

        pTransform = ComponentTransform::CreateComponentTransform(pObj);
        pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(-25.f + 2.1f * i, -1.75f, 29.f);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(1.f, 0.5f, 1.f);

        pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
        pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(1.f);

        pModel = ComponentModel::CreateComponentModel(pObj);
        pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByType(ModelType::CYLINDER);

        pParticle = ParticleComponent::CreateParticleComponent(pObj);
        pParticle->SetParticleVariables(ParticleType::P_BOMB);
        pObj->GetComponentContainer().AddComponent(pParticle, ParticleComponent::COMPONENT_ID);

        m_objectList.push_back(pObj);
    }

    for (int i = 0; i < 26; ++i)
    {
        pObj = new TestObject;
        pObj->SetName("Cylindrical");

        pTransform = ComponentTransform::CreateComponentTransform(pObj);
        pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(29.f, -1.75f, -25.f + 2.1f * i);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(1.f, 0.5f, 1.f);

        pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
        pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(1.f);

        pModel = ComponentModel::CreateComponentModel(pObj);
        pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByType(ModelType::CYLINDER);

        pParticle = ParticleComponent::CreateParticleComponent(pObj);
        pParticle->SetParticleVariables(ParticleType::P_BOMB);
        pObj->GetComponentContainer().AddComponent(pParticle, ParticleComponent::COMPONENT_ID);

        m_objectList.push_back(pObj);
    }

    pObj = new TestObject;
    pObj->SetName("Barrel");
    pTransform = ComponentTransform::CreateComponentTransform(pObj);
    pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(-15.f, -0.5f, -5.f);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(0.5f, 0.5f, 0.5f);
    pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
    pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(2.f);
    pModel = ComponentModel::CreateComponentModel(pObj);
    pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByPath("../../resources/obj/Barrel.obj");
    pParticle = ParticleComponent::CreateParticleComponent(pObj);
    pParticle->SetParticleVariables(ParticleType::P_BOMB);
    pObj->GetComponentContainer().AddComponent(pParticle, ParticleComponent::COMPONENT_ID);
    m_objectList.push_back(pObj);

    pObj = new TestObject;
    pObj->SetName("Chest");
    pTransform = ComponentTransform::CreateComponentTransform(pObj);
    pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(15.f, -1.5f, -15.f);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(0.5f, 0.5f, 0.5f);
    pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
    pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(3.f);
    pModel = ComponentModel::CreateComponentModel(pObj);
    pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByPath("../../resources/obj/chest.obj");
    pParticle = ParticleComponent::CreateParticleComponent(pObj);
    pParticle->SetParticleVariables(ParticleType::P_BOMB);
    pObj->GetComponentContainer().AddComponent(pParticle, ParticleComponent::COMPONENT_ID);
    m_objectList.push_back(pObj);

    pObj = new TestObject;
    pObj->SetName("Barrel");
    pTransform = ComponentTransform::CreateComponentTransform(pObj);
    pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(0.f, 0.f, -15.f);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(1.f, 1.f, 1.f);
    pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
    pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(1.f);
    pModel = ComponentModel::CreateComponentModel(pObj);
    pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByPath("../../resources/obj/sword.obj");
    pParticle = ParticleComponent::CreateParticleComponent(pObj);
    pParticle->SetParticleVariables(ParticleType::P_BOMB);
    pObj->GetComponentContainer().AddComponent(pParticle, ParticleComponent::COMPONENT_ID);
    m_objectList.push_back(pObj);

    pObj = new TestObject;
    pObj->SetName("Plane");

    pTransform = ComponentTransform::CreateComponentTransform(pObj);
    pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(0.f, -3.f, 0.f);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(30.f, 30.f, 30.f);

    pModel = ComponentModel::CreateComponentModel(pObj);
    pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByType(ModelType::PLANE);

    m_objectList.push_back(pObj);

    pObj = new TestObject;
    pObj->SetName("mainCharacter");
	
    pTransform = ComponentTransform::CreateComponentTransform(pObj);
    pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(-2.f, -1.f, 3.f);
    pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(0.5f, 0.5f, 0.5f);

    ComponentPhysics* pPhysics = ComponentPhysics::CreateComponentPhysics(pObj);
    pObj->GetComponentContainer().AddComponent(pPhysics, ComponentPhysics::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocity(Vec3(0.f, 0.f, 0.f));

    pModel = ComponentModel::CreateComponentModel(pObj);
    pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByPath("../../resources/obj/character.obj");
	
    pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
    pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
    pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(1.f);

    m_pMainCharacterEntity = pObj;
    m_objectList.push_back(pObj);
  }

  void Engine::Shutdown()
  {
    // Shutdown App System
    m_pApp->Shutdown();
    delete m_pApp;
    m_pApp = nullptr;

    m_pRenderer->Shutdown();
    delete m_pRenderer;
    m_pRenderer = nullptr;

    //TODO(Dongho) : Working on IMGUI
    m_pGui->Shutdown();
    delete m_pGui;
    m_pGui = nullptr;

    // Shutdown Input Framework
    m_pInput->Shutdown();
    delete m_pInput;
    m_pInput = nullptr;

    // TODO(JIN) : Test for frame
    // Shutdown Frame System
    //m_pFrameHandler->Shutdown();
    delete m_pFrameHandler;
    m_pFrameHandler = nullptr;

    delete m_pSoundManager;
    m_pSoundManager = nullptr;
  }

  void Engine::ProcessEvents()
  {
    while (SDL_PollEvent(&m_event))
    {
      //TODO(Dongho) : Working on IMGUI
      m_pGui->HandleEvent(&m_event);

      // Window Event
      if (m_event.type >= 0x200 /*SDL_WINDOWEVENT*/ && m_event.type < 0x300 /*SDL_KEYUP*/)
      {
        m_pApp->ReceiveEvent(m_event);
      }
      else if (m_event.type >= 0x300 /*SDL_KEYDOWN*/ && m_event.type < 0x900 /*SDL_CLIPBOARDUPDATE*/)
      {
        m_pInput->ReceiveEvent(m_event);
      }
    }
  }

  void Engine::AddMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
  {
    //TODO (DH) : Make msg handler to be executed in order
    // Make multiple message lists to do that

    m_messageList.push_back(std::pair<Message, pair<Entity*, Entity*>>(msg, std::pair<Entity*, Entity*>(pEntity1, pEntity2)));
  }

  void Engine::SendOutMsgs()
  {
    MessageList::iterator it;

    for (it = m_messageList.begin(); it != m_messageList.end(); ++it)
    {
      Message msg = (*it).first;
      Entity* pEntity1 = (*it).second.first;
      Entity* pEntity2 = (*it).second.second;

      m_pApp->HandleMsg(pEntity1, pEntity2, msg);
      m_pRenderer->HandleMsg(pEntity1, pEntity2, msg);
      m_pInput->HandleMsg(pEntity1, pEntity2, msg);
      m_pFrameHandler->HandleMsg(pEntity1, pEntity2, msg);
      //m_pSoundManager->HandleMsg(pEntity1, pEntity2, msg);

      this->HandleMsg(pEntity1, pEntity2, msg);
    }

    m_messageList.clear();
  }

  void Engine::HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
  {
    if (msg == Message::QUIT_PROGRAM)
      m_quit = true;
    if (msg == Message::KEY_R && m_leftBullet == 0)
    {
        m_leftBullet = 10;
    }
    if (msg == Message::CREATECURTAIN)
    {
        //std::cout << "Create" << std::endl;
        m_pRenderer->GetCamera()->SetWork(false);
    }
    if (msg == Message::DISABLECURTAIN)
    {
        //std::cout << "Disable" << std::endl;
        m_pRenderer->GetCamera()->SetWork(true);
    }

    if (pEntity1)
    {
      if (msg == Message::FIRE_BULLET && m_leftBullet > 0)
      {
          m_leftBullet--;
          Vec3 mainPos = pEntity1->GetComponentContainer().GetComponent<ComponentTransform>()->GetPositionVec();
          mainPos.y += 2.f;

        TestObject* pObj = new TestObject;
        pObj->SetName("Bullet");
		
        ComponentTransform* pTransform = ComponentTransform::CreateComponentTransform(pObj);
        pObj->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(mainPos);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetOriginPosition(mainPos);
        pObj->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(0.1f, 0.1f, 0.1f);

        ComponentModel* pModel = ComponentModel::CreateComponentModel(pObj);
        pObj->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByType(ModelType::SPHERE);

        Vec3 vel = m_pRenderer->GetCamera()->front * 5.f;
        ComponentPhysics* pPhysics = ComponentPhysics::CreateComponentPhysics(pObj);
        pObj->GetComponentContainer().AddComponent(pPhysics, ComponentPhysics::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocity(Vec3(vel));

        RigidBodyComponent* pRigidBody = RigidBodyComponent::CreateRigidBodyComponent(pObj);
        pObj->GetComponentContainer().AddComponent(pRigidBody, RigidBodyComponent::COMPONENT_ID);
        pObj->GetComponentContainer().GetComponent<RigidBodyComponent>()->SetRigidBodySize(0.2f);

        m_pSoundManager->PlayEffectSound(GUNSHOT);

        m_objectList.push_back(pObj);
      }

      if (pEntity1->GetName() == "mainCharacter")
      {
          Vec3 currRot = pEntity1->GetComponentContainer().GetComponent<ComponentTransform>()->GetRotationVec();
          Vec3 currPos = pEntity1->GetComponentContainer().GetComponent<ComponentTransform>()->GetPositionVec();
          Vec3 dir = pEntity1->GetComponentContainer().GetComponent<ComponentTransform>()->m_dir;
          Vec3 right = pEntity1->GetComponentContainer().GetComponent<ComponentTransform>()->m_right;

          // TODO (DH) : Make the control smooth
          if (msg == Message::KEY_A_PRESSED || msg == Message::KEY_A_TRIGGERED)
          {
              pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocity(right);

              //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityX(-0.5f);
          }

          else if (msg == Message::KEY_D_PRESSED || msg == Message::KEY_D_TRIGGERED)
          {
              pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocity(-right);
              //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityX(0.5f);
          }

          else if (msg == Message::KEY_S_PRESSED || msg == Message::KEY_S_TRIGGERED)
          {
              pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocity(-dir);
              //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityZ(0.5f);
          }

          else if (msg == Message::KEY_W_PRESSED || msg == Message::KEY_W_TRIGGERED)
          {
              pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocity(dir);
              //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityZ(-0.5f);
          }

          else
          {
              pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocity(Vec3(0.f, 0.f, 0.f));
          }

          //else if (msg == Message::KEY_A_RELEASED)
          //{
          //    pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->AddVelocity(right);

          //  //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityX(0.f);
          //}

          //else if (msg == Message::KEY_D_RELEASED)
          //{
          //    pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->AddVelocity(-right);

          //  //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityX(0.f);
          //}

          //else if (msg == Message::KEY_S_RELEASED)
          //{
          //    pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->AddVelocity(dir);

          //  //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityZ(0.f);
          //}

          //else if (msg == Message::KEY_W_RELEASED)
          //{
          //    pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->AddVelocity(-dir);

          //  //pEntity1->GetComponentContainer().GetComponent<ComponentPhysics>()->SetVelocityZ(0.f);
          //}
      }
    }
  }

  // Temporary function for object movement
  void Engine::HandleMovement()
  {
      Mat4 cameraViewMat = m_pRenderer->GetCamera()->GetViewMatrix();
      Vec3 cameraVec = m_pRenderer->GetCamera()->front.RadToDeg();

      // TODO (DH) : Magic number... Change it!!
      //Vec3 tmp = GetMainCharacterEntity()->GetComponentContainer().GetComponent<ComponentTransform>()->GetRotationVec();
      //GetMainCharacterEntity()->GetComponentContainer().GetComponent<ComponentTransform>()->SetRotation(0,tmp.y,tmp.z);
      GetMainCharacterEntity()->GetComponentContainer().GetComponent<ComponentTransform>()
          ->SetRotationY(-90.f + m_pRenderer->GetCamera()->yaw);
      //GetMainCharacterEntity()->GetComponentContainer().GetComponent<ComponentTransform>()->SetRotation(tmp);

    std::vector<Entity*>::iterator it1;
    for (it1 = m_objectList.begin(); it1 != m_objectList.end(); ++it1)
    {
      if ((*it1)->GetComponentContainer().HasComponent(ComponentPhysics::COMPONENT_ID))
      {
          (*it1)->GetComponentContainer().GetComponent<ComponentTransform>()->GetTransformMat();

        Vec3 pos = (*it1)->GetComponentContainer().GetComponent<ComponentTransform>()
          ->GetPositionVec();
        Vec3 vel = (*it1)->GetComponentContainer().GetComponent<ComponentPhysics>()
          ->GetVelocity();

        (*it1)->GetComponentContainer().GetComponent<ComponentTransform>()->
          Translate(vel * m_dt * 4.f);

        if ((*it1)->GetName() == "Bullet")
        {
            Vec3 originPos = (*it1)->GetComponentContainer().GetComponent<ComponentTransform>()
                ->GetOriginPosVec();

            if (pos.DistanceSq(originPos) > 500.f)
            {
                //(*it1)->GetComponentContainer().ClearComponents();
                // TODO (DH) : Erase object here
                m_markForErase.push_back(*it1);
            }
        }
      }
    }
  }

  Entity* Engine::GetMainCharacterEntity()
  {
    return m_pMainCharacterEntity;
  }

  void Engine::ClearObjectsMarkedDelete()
  {
    while (!m_markForErase.empty())
    {
      Entity* pEntity = m_markForErase.back();

      ObjectList::iterator it = std::find(m_objectList.begin(), m_objectList.end(), pEntity);

      if (it != m_objectList.end())
      {
          m_objectList.erase(it);

      }
      m_markForErase.pop_back();
    }

    m_markForErase.clear();
  }

  void Engine::SolveCollision()
  {
    // First assign collision objects to the list
    ObjectList::iterator it = m_objectList.begin();
    for (; it != m_objectList.end(); ++it)
    {
      if ((*it)->GetComponentContainer().HasComponent(RigidBodyComponent::COMPONENT_ID))
        m_collisionObjectList.push_back(*it);
    }

    // Check if there are more than one collision objects in the list
    if (m_collisionObjectList.size() > 1)
    {
      ObjectList::iterator it1 = m_collisionObjectList.begin();

      for (; it1 != m_collisionObjectList.end() - 1; ++it1)
      {
        for (ObjectList::iterator it2 = it1 + 1; it2 != m_collisionObjectList.end(); ++it2)
        {
            if (it1 != it2)
            {
                if ((*it1)->GetComponentContainer().HasComponent(RigidBodyComponent::COMPONENT_ID) &&
                    (*it2)->GetComponentContainer().HasComponent(RigidBodyComponent::COMPONENT_ID))
                {

                    Vec3 pos1 = (*it1)->GetComponentContainer().GetComponent<ComponentTransform>()->GetPositionVec();
                    Vec3 pos2 = (*it2)->GetComponentContainer().GetComponent<ComponentTransform>()->GetPositionVec();

                    float size1 = (*it1)->GetComponentContainer().GetComponent<RigidBodyComponent>()->GetRigidBodySize();
                    float size2 = (*it2)->GetComponentContainer().GetComponent<RigidBodyComponent>()->GetRigidBodySize();

                    // Do sphere collision
                    if (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2)) <= size1 + size2)
                    {
                        if ((*it1) != GetMainCharacterEntity() && (*it2) != GetMainCharacterEntity())
                        {
                            m_pSoundManager->Play(EXPLOSION);

                            AddMsg(*it1, *it2, Message::HIT_PARTICLE);
                            (*it1)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);
                            (*it2)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);

                            if ((*it1)->GetChildPtr().size() != 0)
                            {

                                (*it1)->GetChildPtr().at(2)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);
                                (*it1)->GetChildPtr().at(1)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);
                                (*it1)->GetChildPtr().at(0)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);
                            }

                            if ((*it2)->GetChildPtr().size() != 0)
                            {
                                (*it2)->GetChildPtr().at(2)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);
                                (*it2)->GetChildPtr().at(1)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);
                                (*it2)->GetChildPtr().at(0)->GetComponentContainer().GetComponent<ComponentModel>()->SetRenderCheck(false);
                            }

                            (*it1)->GetComponentContainer().RemoveComponent(RigidBodyComponent::COMPONENT_ID);
                            (*it2)->GetComponentContainer().RemoveComponent(RigidBodyComponent::COMPONENT_ID);

                            if (std::find(m_markForErase.begin(), m_markForErase.end(), *it1) == m_markForErase.end() && (*it1)->GetName() == "Bullet")
                                m_markForErase.push_back(*it1);

                            if (std::find(m_markForErase.begin(), m_markForErase.end(), *it2) == m_markForErase.end() && (*it2)->GetName() == "Bullet")
                                m_markForErase.push_back(*it2);
                        }

                        else if ((*it2) == GetMainCharacterEntity() && (*it1)->GetName() != "Bullet")
                        {
                            ComponentTransform* pTransform = (*it2)->GetComponentContainer().GetComponent<ComponentTransform>();

                            pTransform->Translate(-pTransform->m_dir * 0.08f);
                        }
                    }
                }
            }
        }
      }
    }

    m_collisionObjectList.clear();
  }

  float Engine::GetDT()
  {
    return m_dt;
  }

  ObjectList* Engine::GetObjectList()
  {
    return &m_objectList;
  }
}









#if 0
long perfCountFrequency;

LARGE_INTEGER Win32GetWallClock()
{
  LARGE_INTEGER endCounter;
  QueryPerformanceCounter(&endCounter);
  return endCounter;
}

float Win32GetSecondsElapsed(LARGE_INTEGER start, LARGE_INTEGER end)
{
  // secondsElapsedForWork
  return (end.QuadPart - start.QuadPart) / perfCountFrequency;
}


void Engine::Run()
{
  // TODO(JIN) : How do we realiably query on this on Windows?
  LARGE_INTEGER perfCountFrequencyResult;
  QueryPerformanceFrequency(&perfCountFrequencyResult);
  perfCountFrequency = perfCountFrequencyResult.QuadPart;

  int monitorRefreshHz = 60;
  int gameUpdateHz = monitorRefreshHz / 2;
  float targetSecondsPerFram = 1.0f / (float)monitorRefreshHz;;


  Initialize();
  LARGE_INTEGER lastCounter = Win32GetWallClock();
  unsigned long lastCycleCount = __rdtsc();

  while (!m_quit)
  {
    // Handle all the events from the SDL
    ProcessEvents();

    // Update

    // Draw

    LARGE_INTEGER workCounter = Win32GetWallClock();
    float worksecondsElapsedForWork = Win32GetSecondsElapsed(lastCounter, workCounter);


    float secondsElapsedForFrame = worksecondsElapsedForWork;

    while (secondsElapsedForFrame < targetSecondsPerFram)
    {

      secondsElapsedForFrame = Win32GetSecondsElapsed(lastCounter, Win32GetWallClock());
    }

#if 0
    float msPerFrame = ((1000.0f * (float)counterElapsed / (float)perfCountFrequency)) *;
    float fps = (float)perfCountFrequency / (float)counterElapsed;
    float mcPerFrame = ((float)cyclesElapsed / (1000.0f * 1000.0f));
#endif
    LARGE_INTEGER endCounter = Win32GetWallClock();
    lastCounter = endCounter;

    unsigned long endCycleCount = __rdtsc();
    unsigned long cyclesElapsed = endCycleCount - lastCycleCount;
    lastCycleCount = endCycleCount;


  }

  Shutdown();
}
#endif