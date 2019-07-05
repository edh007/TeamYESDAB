#include "GuiManager.h"

using namespace gi;

GuiManager::GuiManager(Engine* pEngine) : m_pEngine(pEngine)
{
    f = 0.0f;
}

GuiManager::~GuiManager()
{
}

void GuiManager::Initialize(SDL_Window* _pWindow)
{
    m_pWindow = _pWindow;
    ImGui_ImplSdlGL3_Init(m_pWindow);
}

void GuiManager::Update()
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoMove;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
    ImGui::Begin("", NULL, window_flags);
    {
        //ImGui::PushFont();
        ImGui::SetWindowFontScale(2);
        if (ImGui::Button("Exit", ImVec2(200, 50))) exit ^= 1;
    }
    ImGui::End();
    ImGui::Begin("", NULL, window_flags);
    {
        ImGui::SameLine();
        if (ImGui::Button("Start Game", ImVec2(200, 50))) startGame ^= 1;
    }
    ImGui::End();
    ImGui::Begin("", NULL, window_flags);
    {
        ImGui::SameLine();
        if (startGame == true)
        {
            if (ImGui::Button("Open Editor", ImVec2(200, 50))) debug_window ^= 1;
            m_pEngine->AddMsg(nullptr, nullptr, Message::DISABLECURTAIN);
            gameTitle = false;
        }
        else
        {
            m_pEngine->AddMsg(nullptr, nullptr, Message::CREATECURTAIN);
            show_test_window = false;
            objectList = false;
            soundCheck = false;
            debug_window = false;
            gameTitle = true;
        }
    }
    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();

    if (gameTitle)
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
        ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.0f, 0.0f, 0.f)); // Transparent background
        ImGui::Begin(" ", NULL, window_flags);
        {
            ImGui::SetWindowFontScale(4);
            ImGui::Button("YESDAB", ImVec2(300, 100));
        }
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }

    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug".
    if (debug_window)
    {
        ImGui::Begin("Debug Console");
        {
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            //ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Imgui Example")) show_test_window ^= 1;
            if (ImGui::Button("Object")) objectList ^= 1;
            if (ImGui::Button("SoundManager")) soundCheck ^= 1;
            if (ImGui::Button("Full Screen")) fullScreen ^= 1;
            ImGui::Text("Press Z to shoot bullet, R to reload when bullet == 0");
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.f), "Bullet : %d", m_pEngine->m_leftBullet);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();
    }
    // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
    // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow().
    if (show_test_window)
    {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
        ImGui::ShowTestWindow(&show_test_window);
    }
    if (objectList)
    {
        DrawObjectlist("Entity", &objectList);
    }
    if (soundCheck)
    {
        DrawManagerlist("SoundManager", &soundCheck);
    }
    if (exit)
    {
        m_pEngine->Quit();
    }
    if (fullScreen)
    {
        m_pEngine->AddMsg(nullptr, nullptr, Message::FULL_SCREEN);
        fullScreen = false;
    }
}

void GuiManager::Shutdown()
{
    ImGui_ImplSdlGL3_Shutdown();
}

void GuiManager::StartNewFrame()
{
    ImGui_ImplSdlGL3_NewFrame(m_pWindow);
}

void GuiManager::HandleEvent(SDL_Event* _ev)
{
    ImGui_ImplSdlGL3_ProcessEvent(_ev);
}

void GuiManager::EndOfFrame()
{
    ImGui::Render();
}

void GuiManager::CheckKbOverride()
{
    //ImGuiIO& io = ImGui::GetIO();
    //if (io.WantCaptureKeyboard == true)
    //{
    //    BE::Core::Event::instance()->flushKeyboardEvents();
    //}
    //if (io.WantCaptureMouse == true)
    //{
    //    BE::Core::Event::instance()->flushMouseEvents();
    //}
}

void GuiManager::DrawManagerlist(const char * _pTitle, bool * _pOpen)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(_pTitle, _pOpen);
    {
        m_pEngine->GetSoundManager()->DrawManager();
        //// Adding and Removing actors
        //ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 30), false);
        //{
        //    // The list of all active actors
        //    ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 50), true);
        //    {
        //        if (ImGui::CollapsingHeader("Actors", ImGuiTreeNodeFlags_DefaultOpen))
        //        {
        //        }
        //    }
        //    ImGui::EndChild();

        //    if (ImGui::Button("Add"))
        //    {
        //    }
        //    ImGui::SameLine();
        //    if (ImGui::Button("Remove"))
        //    {
        //    }
        //    if (ImGui::Button("Remove All"))
        //    {
        //    }
        //}
        //ImGui::EndChild();
    }
    ImGui::SameLine();
    
    ImGui::End();
}

void GuiManager::DrawComponentData()
{
    if (currentSelectedEntity->GetComponentContainer().GetComponent<ComponentTransform>() != nullptr)
    {
        currentSelectedEntity->GetComponentContainer().GetComponent<ComponentTransform>()->DrawComponent();
    }
    if (currentSelectedEntity->GetComponentContainer().GetComponent<ComponentModel>() != nullptr)
    {
        currentSelectedEntity->GetComponentContainer().GetComponent<ComponentModel>()->DrawComponent();
    }
    if (currentSelectedEntity->GetComponentContainer().GetComponent<ParticleComponent>() != nullptr)
    {
        currentSelectedEntity->GetComponentContainer().GetComponent<ParticleComponent>()->DrawComponent();
    }
    if (currentSelectedEntity->GetComponentContainer().GetComponent<ComponentText>() != nullptr)
    {
        currentSelectedEntity->GetComponentContainer().GetComponent<ComponentText>()->DrawComponent();
    }
}

void GuiManager::ResetSelected(ObjectList* _pEntityVec)
{
    for (uint32_t i = 0; i < _pEntityVec->size(); ++i)
    {
        _pEntityVec->at(i)->_isSelected = false;
    }
}

void GuiManager::DrawObjectlist(const char * _pTitle, bool * _pOpen)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(_pTitle, _pOpen);
    {
        ObjectList* entityVec = m_pEngine->GetObjectList();
        ObjectList::iterator activeVec = m_pEngine->GetObjectList()->begin();
        // left
        {
            static size_t selected = 0;
            //static size_t selectedChild = 0;
            if (selected >= entityVec->size())
            {
                selected = 0;
                currentSelectedEntity = nullptr;
            }
            else
            {
                currentSelectedEntity = activeVec[selected];
                //if(selectChild == true)
                //{
                //    std::vector<Entity*>::iterator* child = currentSelectedEntity->GetChildIterator();
                //    currentSelectedEntity = (*child)[selectedChild];
                //}
            }

            // Adding and Removing actors
            ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 30), false);
            {
                // The list of all active actors
                ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 50), true);
                {
                    if (ImGui::CollapsingHeader("Actors", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        for (size_t i = 0; i < entityVec->size(); ++i)
                        {
                                ImGui::PushID(static_cast<int>(i));
                                {
                                    char label[128];
                                    sprintf_s(label, "%s", (entityVec->at(i))->GetName().data());
                                    if (ImGui::Selectable(label, selected == i) || (entityVec->at(i))->_isSelected)
                                    {
                                        if (!entityVec->at(i)->_isSelected)
                                        {
                                            ResetSelected(entityVec);
                                        }
                                        selected = i;
                                        currentSelectedEntity = entityVec->at(i);
                                        if (currentSelectedEntity->GetComponentContainer().GetComponent<ComponentModel>())
                                        {
                                            currentSelectedEntity->_isSelected = true;
                                            //selectedChild = 0;
                                            //selectChild = false;
                                            //int tmp = currentSelectedEntity->GetChildPtr().size();
                                            //if(tmp != 0)
                                            //{
                                            //    for (int j = 0; j < tmp; j++)
                                            //    {
                                            //        if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", j))
                                            //        {
                                            //            if (ImGui::SmallButton("Select"))
                                            //            {
                                            //                selectedChild = j;
                                            //                selectChild = true;
                                            //                //currentSelectedEntity = currentSelectedEntity->GetChildPtr().at(j);
                                            //            }
                                            //            ImGui::TreePop();
                                            //        }
                                            //    }
                                            //}
                                        }
                                    }
                                }
                                ImGui::PopID();
                        }
                    }
                }
                ImGui::EndChild();

                if (ImGui::Button("Add"))
                {
                        TestObject* newEntity = new TestObject();
                        newEntity->SetName("New");
                        ComponentTransform* pTransform = ComponentTransform::CreateComponentTransform(newEntity);
                        newEntity->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
                        newEntity->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(-0.f, -1.75f, 0.f);
                        newEntity->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(0.2f, 0.2f, 0.2f);

                        ComponentModel* pModel = ComponentModel::CreateComponentModel(newEntity);
                        newEntity->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
                        newEntity->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByType(ModelType::CONE);

                        entityVec->push_back(newEntity);
                }
                ImGui::SameLine();
                if (ImGui::Button("Remove"))
                {
                    if (currentSelectedEntity != nullptr)
                    {
                        std::cout << "Remove !\n";
                        entityVec->erase(activeVec+selected);
                        //entityVec->clear();
                        currentSelectedEntity = nullptr;
                        selected = 0;
                    }
                }
                if (ImGui::Button("Remove All"))
                {
                    if (currentSelectedEntity != nullptr)
                    {
                        std::cout << "Remove !\n";
                        //entityVec->erase(activeVec + selected);
                        entityVec->clear();
                        currentSelectedEntity = nullptr;
                        selected = 0;
                    }
                }
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();

        // right
        {
            if (currentSelectedEntity != nullptr)
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

                ImGui::BeginGroup();
                {
                    // Actor name + active state
                    {
                        static char buf1[32] = "";
                        ImGui::Text("Actor name: %s\n", currentSelectedEntity->GetName().c_str());
                        ImGui::PushItemWidth(textWidth);
                        {
                            if (ImGui::InputText("", buf1, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                            {
                                currentSelectedEntity->SetName(buf1);
                                buf1[0] = '\0';
                            }
                            ImGui::PopItemWidth();
                        }
                        ImGui::SameLine(buttonSpacing);
                        ImGui::Checkbox("Active", &currentSelectedEntity->_isActive);

                    }
                    // Actor component's
                    {
                        DrawComponentData();
                    }
                    // Adding and removing components
                    ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing())); // Leave room for 1 line below us
                    {
                        ImGui::Separator();
                        // To add and remove components
                        ImGui::PushItemWidth(120);
                        {
                            ImGui::Combo("Component", &compoSelected, "NONE\0TRANSFORM\0MODEL\0PARTICLE\0TEXT\0CAMERA\0\0");
                        }
                        ImGui::PopItemWidth();
                        ImGui::SameLine();

                        if (ImGui::Button("Add"))
                        {
                            switch (compoSelected)
                            {
                            case 1:
                            {
                                if (currentSelectedEntity->GetComponentContainer().GetComponent<ComponentTransform>() == nullptr)
                                {
                                    ComponentTransform* pTransform = ComponentTransform::CreateComponentTransform(currentSelectedEntity);
                                    currentSelectedEntity->GetComponentContainer().AddComponent(pTransform, ComponentTransform::COMPONENT_ID);
                                    currentSelectedEntity->GetComponentContainer().GetComponent<ComponentTransform>()->SetPosition(-0.f, -1.75f, 0.f);
                                    currentSelectedEntity->GetComponentContainer().GetComponent<ComponentTransform>()->SetScale(0.2f, 0.2f, 0.2f);
                                }
                                break;
                            }
                            case 2:
                            {
                                if (currentSelectedEntity->GetComponentContainer().GetComponent<ComponentModel>() == nullptr)
                                {
                                    ComponentModel* pModel = ComponentModel::CreateComponentModel(currentSelectedEntity);
                                    currentSelectedEntity->GetComponentContainer().AddComponent(pModel, ComponentModel::COMPONENT_ID);
                                    currentSelectedEntity->GetComponentContainer().GetComponent<ComponentModel>()->InitModelByPath("../../resources/obj/nanosuit/nanosuit.obj");
                                }
                                break;
                            }
                            case 3:
                            {
                                if (currentSelectedEntity->GetComponentContainer().GetComponent<ParticleComponent>() == nullptr)
                                {
                                    ParticleComponent* pModel = ParticleComponent::CreateParticleComponent(currentSelectedEntity);
                                    pModel->SetParticleVariables(ParticleType::P_BOMB);
                                    currentSelectedEntity->GetComponentContainer().AddComponent(pModel, ParticleComponent::COMPONENT_ID);
                                    
                                    //currentSelectedEntity->GetComponentContainer().GetComponent<ParticleComponent>()->InitModelByPath("../../resources/obj/nanosuit/nanosuit.obj");
                                }
                                break;
                            }
                            case 4:
                            {
                                if (currentSelectedEntity->GetComponentContainer().GetComponent<ComponentText>() == nullptr)
                                {
                                    ComponentText* pModel = ComponentText::CreateComponentText(currentSelectedEntity, 30);
                                    pModel->SetText("SAMPLE");
                                    currentSelectedEntity->GetComponentContainer().AddComponent(pModel, ComponentText::COMPONENT_ID);

                                    //currentSelectedEntity->GetComponentContainer().GetComponent<ParticleComponent>()->InitModelByPath("../../resources/obj/nanosuit/nanosuit.obj");
                                }
                                break;
                            }
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Remove"))
                        {
                            switch (compoSelected)
                            {
                                case 1:
                                {
                                    currentSelectedEntity->GetComponentContainer().RemoveComponent(ComponentTransform::COMPONENT_ID);
                                    break;
                                }
                                case 2:
                                {
                                    currentSelectedEntity->GetComponentContainer().RemoveComponent(ComponentModel::COMPONENT_ID);
                                    break;
                                }
                                case 3:
                                {
                                    currentSelectedEntity->GetComponentContainer().RemoveComponent(ParticleComponent::COMPONENT_ID);
                                    break;
                                }
                                case 4:
                                {
                                    currentSelectedEntity->GetComponentContainer().RemoveComponent(ComponentText::COMPONENT_ID);
                                    break;
                                }
                            }
                        }
                    }
                    ImGui::EndChild();
                }
                ImGui::EndGroup();
            }
        }
    }
    ImGui::End();
}
