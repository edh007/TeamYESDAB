#pragma once

#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include "Engine.h"
#include "../components/ComponentModel.h"
#include "ParticleComponent.h"
#include "components\ComponentTransform.h"
#include "components\ComponentText.h"
#include "../framework/SoundManager.h"

//typedef std::unordered_map<std::string, bool*> WindowList;

namespace gi
{

    class GuiManager
    {
    public:
        GuiManager(Engine* pEngine);
        ~GuiManager();

        void Initialize(SDL_Window* _pWindow);
        void Update();
        void Shutdown();
        void StartNewFrame(); //!< Function that will be called at the start of each frame
        void HandleEvent(SDL_Event* _ev);
        void EndOfFrame(); //!< Function that will be called at the end of each frame
        void CheckKbOverride(); //!< Checks to see if kb override event has been received by ImGui

        //WindowList m_windowList;
        bool show_test_window = false;
        bool objectList = false;
        bool selectChild = false;
        bool soundCheck = false;
        bool exit = false;
        bool debug_window = false;
        bool fullScreen = false;
        bool startGame = false;
        bool gameTitle = true;
        void DrawObjectlist(const char* _pTitle, bool* _pOpen);
        void DrawManagerlist(const char * _pTitle, bool * _pOpen);
        Entity*  currentSelectedEntity = nullptr;
        int    compoSelected = 0;
        void DrawComponentData();
        void ResetSelected(ObjectList* _pEntityVec);

    private:
        float f;
        SDL_Window* m_pWindow;
        Engine* m_pEngine;
        friend class Engine;
    };
}
