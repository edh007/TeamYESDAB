#pragma once

#include "glew.h"
#include "../math/Math.h"
#include "ShaderManager.h"
#include "Camera.h"
#include <SDL.h>
#include <vector>
#include "Model.h"
#include "Light.h"
#include <Windows.h>
#include "Skybox.h"
#include "Engine.h"

#include "base/Entity.h"
#include "components\ComponentTransform.h"
#include "components/ComponentModel.h"
#include "components/ComponentText.h"
#include "ParticleComponent.h"

typedef std::vector<Model*> ModelList;
typedef std::vector<Light*> LightList;

namespace gi {

    class Renderer {

    public:
        Renderer(Engine* pGameEngine);
        ~Renderer(void);

        void Initialize(SDL_Window* _pWindow);
        void Update(float dt);
        void Shutdown();
        void HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg);

        void SetCamera(Camera* _cam);
        Camera* GetCamera();

        void AddModel(Model* _pModel);
        void AddLight(Light* _pLight);
        Mat4 Perspective(float const & fovy, float const & aspect, float const & zNear, float const & zFar);
        Mat4 Ortho(float const & left, float const & right, float const& bottom, float const& top, float const & zNear, float const & zFar);

        Camera* m_camera;
        SDL_Window* m_pWindow;
        SDL_GLContext m_context;

        
    private:
        void MVP(Entity* _pEntity); //Calculate MVP and sent to shader
        void MVPChild(Entity* _pEntity, float deg, bool check); //Calculate MVP and sent to shader
        void MVP(Entity* _pEntity, Unit unit); //Calculate MVP and sent to shader
        void MVP(Model* _pModel);
        void MVP(Skybox* _pSkybox);
        void MVPText(Entity* _pEntity);
        void DrawModel(Entity* _pEntity); //Draw Model
        void DrawParticle(Entity* _pEntity, float dt); //Draw Model
        void DrawModel(Model* _pModel);
        void DrawLight(Light* _pLight, int i);

        void DrawTexts(Entity* _pEntity); //Draw Model
        Engine* m_pEngine;

        ModelList m_modelList; // For lights, temporarily...
        ObjectList* m_pObjectList;
        LightList m_lightList;
        Skybox* m_skybox;
        ShaderManager* m_pShader;
        HANDLE m_hConsole;
        COORD m_coordCur;

        Vec4 fogColor = Vec4(0.5f, 0.5f, 0.5f, 1.f);
        Vec4 g_ambient = Vec4(0.2f, 0.2f, 0.2f, 1.0f);
        int fogFar = 100;
        int fogNear = 50;
        float sizeSkybox = 100.f;
        friend class Engine;
        float deg = 0;
        bool addition = true;
        bool head = true;
        bool c = false;
    };

};
