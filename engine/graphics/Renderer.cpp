#include "Renderer.h"
#include <cstdio>
#include "math/Vec2.h"

using namespace gi;

Renderer::Renderer(Engine* pEngine) : m_pEngine(pEngine)
{
    m_camera = new Camera();
    m_camera->pos = Vec3(0.f, 0.f, 3.f);
    //m_camera.front = Vec3(0, 0, 0.f);
    //m_camera.up = Vec3(0.f, 1.f, 0.f);

    m_pObjectList = m_pEngine->GetObjectList();
}

Renderer::~Renderer()
{
    delete m_camera;
    delete m_pShader;
}

void Renderer::Initialize(SDL_Window* _pWindow)
{
    m_pWindow = _pWindow;
    //m_pRB = new RenderBase();

    // create opengl context and attach it to window
    m_context = SDL_GL_CreateContext(m_pWindow);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // PROFILE_CORE gives the newer version, dprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Set OpenGL version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Turn on double buffering with a 24bit Z buffer
    // TODO(Dongho) : Maybe need to change this to 16 or 32 for system.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Buffer swap syncronized with the monitor's vertical refresh.
    SDL_GL_SetSwapInterval(1);

    // Request a debug context.
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    //Before using shader, initialize glew.
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

    //char working_directory[MAX_PATH + 1];
    //GetCurrentDirectoryA(sizeof(working_directory), working_directory); // **** win32 specific ****
    //std::cout << working_directory << std::endl;

    std::vector<std::string> faces
    {
        ("../../resources/textures/skybox/right.jpg"),
        ("../../resources/textures/skybox/left.jpg"),
        ("../../resources/textures/skybox/top.jpg"),
        ("../../resources/textures/skybox/bottom.jpg"),
        ("../../resources/textures/skybox/back.jpg"),
        ("../../resources/textures/skybox/front.jpg")
    };

    m_skybox = new Skybox(faces, sizeSkybox);

    Vec3 dir(0.577f, 0.577f, 0.577f);
    Vec3 pos(1.5f, 1.5f, 1.5f);

    Light* light0 = new Light(Vec3(-dir.x, dir.y, -dir.z), Vec3(pos.x, -pos.y, pos.z));
    Light* light1 = new Light(Vec3(dir.x, dir.y, -dir.z), Vec3(-pos.x, -pos.y, pos.z));
    Light* light2 = new Light(Vec3(dir.x, dir.y, dir.z), Vec3(-pos.x, -pos.y, -pos.z));
    Light* light3 = new Light(Vec3(-dir.x, dir.y, dir.z), Vec3(pos.x, -pos.y, -pos.z));
    Light* light4 = new Light(Vec3(0.555f, -0.832f, 0.f), Vec3(-1.f, 1.5f, 0.f));
    Light* light5 = new Light(Vec3(-0.535f, -0.802f, 0.267f), Vec3(1.f, 1.5f, -0.5f));
    Light* light6 = new Light(Vec3(0.f, 0.f, -1.f), Vec3(0.f, 0.f, 2.f));
    Light* light7 = new Light(Vec3(0.f, 0.f, 1.f), Vec3(0.f, 0.f, -2.f));
    AddLight(light0);
    AddLight(light1);
    AddLight(light2);
    AddLight(light3);
    AddLight(light4);
    AddLight(light5);
    AddLight(light6);
    AddLight(light7);

    m_lightList.at(0)->position = Vec3(pos.x, -pos.y, pos.z);
    m_lightList.at(1)->position = Vec3(-pos.x, -pos.y, pos.z);
    m_lightList.at(2)->position = Vec3(-pos.x, -pos.y, -pos.z);
    m_lightList.at(3)->position = Vec3(pos.x, -pos.y, -pos.z);
    m_lightList.at(4)->position = Vec3(-1.f, 1.5f, 0.f);
    m_lightList.at(5)->position = Vec3(1.f, 1.5f, -0.5f);
    m_lightList.at(6)->position = Vec3(0.f, 0.f, 2.f);
    m_lightList.at(7)->position = Vec3(0.f, 0.f, -2.f);

    m_lightList.at(0)->direction = Vec3(-dir.x, dir.y, -dir.z);
    m_lightList.at(1)->direction = Vec3(dir.x, dir.y, -dir.z);
    m_lightList.at(2)->direction = Vec3(dir.x, dir.y, dir.z);
    m_lightList.at(3)->direction = Vec3(-dir.x, dir.y, dir.z);
    m_lightList.at(4)->direction = Vec3(0.555f, -0.832f, 0.f);
    m_lightList.at(5)->direction = Vec3(-0.535f, -0.802f, 0.267f);
    m_lightList.at(6)->direction = Vec3(0.f, 0.f, -1.f);
    m_lightList.at(7)->direction = Vec3(0.f, 0.f, 1.f);

    m_lightList.at(0)->lightType = LightType::DIRECTION;
    m_lightList.at(1)->lightType = LightType::POINT;
    m_lightList.at(2)->lightType = LightType::POINT;
    m_lightList.at(3)->lightType = LightType::POINT;
    m_lightList.at(4)->lightType = LightType::POINT;
    m_lightList.at(5)->lightType = LightType::POINT;
    m_lightList.at(6)->lightType = LightType::POINT;
    m_lightList.at(7)->lightType = LightType::POINT;

    m_lightList.at(0)->diffuse = Vec4(1.f, 1.f, 1.f, 1.f); //Color::Blue;
    m_lightList.at(1)->diffuse = Vec4(0.f, 1.f, 1.f, 1.f); //Color::Cyan;
    m_lightList.at(2)->diffuse = Vec4(0.8f, 0.8f, 0.8f, 1.f); //Color::LGray;
    m_lightList.at(3)->diffuse = Vec4(0.f, 1.f, 0.f, 1.f); //Color::Green;
    m_lightList.at(4)->diffuse = Vec4(1.f, 0.f, 1.f, 1.f); //Color::Magenta;
    m_lightList.at(5)->diffuse = Vec4(1.f, 0.f, 0.f, 1.f); //Color::Red;
    m_lightList.at(6)->diffuse = Vec4(1.f, 1.f, 0.f, 1.f); //Color::Yellow;
    //m_lightList.at(7)->diffuse = Vec4(); //Color::White;

    m_pShader = new ShaderManager();
    m_pShader->RegisterShader("EXAMPLE", "../../resources/shader/model_loading_v.glsl", "../../resources/shader/model_loading_f.glsl");
    m_pShader->RegisterShader("SKYBOX", "../../resources/shader/skybox_v.glsl", "../../resources/shader/skybox_f.glsl");
    m_pShader->RegisterShader("PARTICLE", "../../resources/shader/particle_v.glsl", "../../resources/shader/particle_f.glsl");
    m_pShader->RegisterShader("TEXT", "../../resources/shader/text_v.glsl", "../../resources/shader/text_f.glsl");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //if (glDebugMessageCallback) {
    //    std::cout << "Register OpenGL debug callback " << std::endl;
    //    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //    glDebugMessageCallback((m_pShader->GetShader("EXAMPLE")->debugCallback), nullptr);
    //    GLuint unusedIds = 0;
    //    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
    //}
    //else
    //    std::cout << "glDebugMessageCallback not available" << std::endl;
}

void Renderer::Update(float dt)
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    MVP(m_skybox);
    m_skybox->Draw();

  Vec3 mcPos = m_pEngine->GetMainCharacterEntity()->
      GetComponentContainer().GetComponent<ComponentTransform>()->GetPositionVec();

  //m_camera->pos.y = mcPos.y + 5.f;
  m_camera->pos = mcPos - 5.f * m_camera->front;
  m_camera->pos.y = mcPos.y + 4.f;
  //m_camera->front = (mcPos - m_camera->pos).Normalize();

	Shader* ourShader = m_pShader->GetShader("EXAMPLE");
    ourShader->Use();
    ourShader->SetVec3("viewPos", m_camera->pos);

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    glViewport(0, 0, w, h);

    int i = 0;
    for (auto it = m_lightList.begin(); it != m_lightList.end(); ++it)
    {
        MVP((*it)->cube);
        DrawLight(*it, i++);
    }
    ourShader->SetInt("lightNumber", i);


    ObjectList::iterator it;
    i = 0;
    for (it = m_pObjectList->begin(); it != m_pObjectList->end(); ++it)
    {
        //int tmp = m_pObjectList->at(i)->GetChildPtr().size();
        //if(tmp != 0)
        //{
        //    for (int j = 0; j < tmp; ++j)
        //    {
        //        if (deg > 20 && j == 0)
        //            addition = false;
        //        if (deg < -20 && j == 0)
        //            addition = true;
        //        if (addition == true && j == 0)
        //            deg += (dt * 20);
        //        if (addition == false && j == 0)
        //            deg -= (dt * 20);
        //        if(j == 0)
        //            MVPChild(m_pObjectList->at(i)->GetChildPtr().at(j), deg, true);
        //        if (j == 1)
        //            MVPChild(m_pObjectList->at(i)->GetChildPtr().at(j), -deg, true);
        //        if (j == 2)
        //        {
        //            float amount = 1.f;
        //            if (addition == true) amount = 0.005f;
        //            else amount = -0.005f;        
        //            MVPChild(m_pObjectList->at(i)->GetChildPtr().at(j), amount, false);
        //        }
        //        DrawModel(m_pObjectList->at(i)->GetChildPtr().at(j));
        //        c = true;
        //    }
        //}
        if (m_pObjectList->at(i)->GetComponentContainer().HasComponent(ComponentModel::COMPONENT_ID))
        {
            if (c == true)
            {
                Vec3 tmp = m_pObjectList->at(i)->GetComponentContainer().GetComponent<ComponentTransform>()->GetRotationVec();
                m_pObjectList->at(i)->GetComponentContainer().GetComponent<ComponentTransform>()->SetRotation(180,tmp.y,tmp.z);
                MVP(m_pObjectList->at(i));
                DrawModel(m_pObjectList->at(i));
                c = false;
                m_pObjectList->at(i)->GetComponentContainer().GetComponent<ComponentTransform>()->SetRotation(tmp.x, tmp.y, tmp.z);
            }
            else
            {
                MVP(m_pObjectList->at(i));
                DrawModel(m_pObjectList->at(i));
            }
        }
        i++;
    }
    for (unsigned i = 0; i < m_pObjectList->size(); ++i)
    {
        if (m_pObjectList->at(i)->GetComponentContainer().HasComponent(ParticleComponent::COMPONENT_ID))
        {
            DrawParticle(m_pObjectList->at(i), dt);
        }
    }
    for (unsigned i = 0; i < m_pObjectList->size(); ++i)
    {
        if (m_pObjectList->at(i)->GetComponentContainer().HasComponent(ComponentText::COMPONENT_ID))
        {
            MVPText(m_pObjectList->at(i));
            DrawTexts(m_pObjectList->at(i));
        }
    }


}

void Renderer::MVPChild(Entity* _pEntity, float deg, bool check)
{
    Shader* ourShader = m_pShader->GetShader("EXAMPLE");
    // don't forget to enable shader before setting uniforms
    ourShader->Use();

    // render the loaded model
    Mat4 model;
    Mat4 t;
    Mat4 s;
    Mat4 r;
    ComponentTransform* pTransform = _pEntity->GetComponentContainer().GetComponent<ComponentTransform>();

    Vec3 tra = pTransform->GetPositionVec();
    if (check == false)
    {
        tra.y += (deg);
        pTransform->SetPosition(tra);
    }
    t.Translate(tra);
    s.Scale(pTransform->GetScaleVec());
    //r.Rotate(pTransform->GetRotationVec() * 0.0174532925f);
    Vec3 rot(pTransform->GetRotationVec());

    if (check == true)
        rot.x += deg;
    r.Rotate(rot * 0.0174532925f);

    model.Transform(t, r, s);
    model = model * _pEntity->GetParentPtr()->GetComponentContainer().GetComponent<ComponentModel>()->GetWorldMat();

    ourShader->SetMat4("model", model);

    // view/projection transformations
    Mat4 view = m_camera->GetViewMatrix();
    ourShader->SetMat4("view", view);

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    Mat4 projection = Perspective(DegreeToRadian(m_camera->zoom), (float)w / (float)h, 0.1f, 100.0f);
    ourShader->SetMat4("projection", projection);
}

void Renderer::Shutdown()
{
    m_lightList.clear();
    m_modelList.clear();

    //m_modelList.clear();
    // Delete OpenGL context
    SDL_GL_DeleteContext(m_context);

    // Release the handle
    CloseHandle(m_hConsole);
}

void Renderer::HandleMsg(Entity* pEntity1, Entity* pEntity2, Message msg)
{
    float dt = m_pEngine->GetDT();

    if (msg == Message::HIT_PARTICLE)
    {
        if(pEntity1->GetComponentContainer().HasComponent(ParticleComponent::COMPONENT_ID))
        {
            ParticleComponent* pParticle = pEntity1->GetComponentContainer().GetComponent<ParticleComponent>();
            pParticle->active = true;
            pParticle->Restore();
            std::cout << "Call" << std::endl;
        }
        //else if (pEntity2->GetComponentContainer().HasComponent(ParticleComponent::COMPONENT_ID))
        //{
        //    ParticleComponent* pParticle = pEntity2->GetComponentContainer().GetComponent<ParticleComponent>();
        //    pParticle->active = true;
        //    pParticle->Restore();
        //}
    }
    else if (msg == Message::FULL_SCREEN)
    {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        auto w = DM.w;
        auto h = DM.h;
        glViewport(0, 0, w, h);
    }
    //else if (msg == Message::KEY_A)
    //{
    //    
    //}
    //else if (msg == Message::KEY_D)
    //{
    //    
    //}

    /*if (msg == Message::KEY_W)
      m_camera->pos.y += dt;
    else if (msg == Message::KEY_S)
      m_camera->pos.y -= dt;
    else if (msg == Message::KEY_A)
      m_camera->pos.x -= dt;
    else if (msg == Message::KEY_D)
      m_camera->pos.x += dt;

    // Clear out console each loop
    SetConsoleCursorPosition(m_hConsole, m_coordCur);
    std::cout << "Delta Time : " << dt << std::endl;
    std::cout << "Camera Position : (" << m_camera->pos.x << ", " << m_camera->pos.y << ")\n\n";*/
}

void Renderer::SetCamera(Camera* _cam)
{
    m_camera = _cam;
}

Camera* Renderer::GetCamera()
{
    return m_camera;
}

void Renderer::MVP(Skybox* _pSkybox)
{
    // TODO(Dongho): Skybox Param
    UNREFERENCED_PARAMETER(_pSkybox);
    Shader* ourShader = m_pShader->GetShader("SKYBOX");
    // don't forget to enable shader before setting uniforms
    ourShader->Use();
    // view/projection transformations
    Mat4 view = m_camera->GetViewMatrix();
    ourShader->SetMat4("view", view);

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    Mat4 projection = Perspective(DegreeToRadian(m_camera->zoom), (float)w / (float)h, 0.1f, 100.0f);
    ourShader->SetMat4("projection", projection);
}

void Renderer::MVP(Model* _pModel)
{
    Shader* ourShader = m_pShader->GetShader("EXAMPLE");
    // don't forget to enable shader before setting uniforms
    ourShader->Use();

    // render the loaded model
    Mat4 model;
    Mat4 t;
    Mat4 s;
    Mat4 r;
    t.Translate(_pModel->pos);
    //t.Translate(_pModel->pos); // translate it down so it's at the center of the scene

    //s.Scale(_pModel->scl);	// it's a bit too big for our scene, so scale it down
    s.Scale(_pModel->scl);
    r.Rotate(Vec3(), 0.f);

    model.Transform(t, r, s);

    ourShader->SetMat4("model", model);

    // view/projection transformations
    Mat4 view = m_camera->GetViewMatrix();
    ourShader->SetMat4("view", view);

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    Mat4 projection = Perspective(DegreeToRadian(m_camera->zoom), (float)w / (float)h, 0.1f, 100.0f);
    ourShader->SetMat4("projection", projection);
}

void Renderer::MVP(Entity* _pEntity)
{
    Shader* ourShader = m_pShader->GetShader("EXAMPLE");
    // don't forget to enable shader before setting uniforms
    ourShader->Use();

    // render the loaded model
    Mat4 model;
    Mat4 t;
    Mat4 s;
    Mat4 r;
    ComponentTransform* pTransform = _pEntity->GetComponentContainer().GetComponent<ComponentTransform>();

    t.Translate(pTransform->GetPositionVec());
    s.Scale(pTransform->GetScaleVec());
    //rx.Rotate(0.1f, 0.f, 0.f, pTransform->GetRotationVec().x* 0.0174532925f / 2);
    //ry.Rotate(0.0f, 1.f, 0.f, pTransform->GetRotationVec().y* 0.0174532925f / 2);
   // rz.Rotate(0.0f, 0.f, 1.f, pTransform->GetRotationVec().z* 0.0174532925f / 2);
    
    r.Rotate(pTransform->GetRotationVec()* 0.0174532925f);
    //r.Rotate(pTransform->GetRotationVec());
   // Mat4 rx;
   // Mat4 ry;
   // Mat4 rz;
    //rx.Rotate(0.1f, 0.f, 0.f, pTransform->GetRotationVec().x* 0.0174532925f / 2);
    //ry.Rotate(0.0f, 1.f, 0.f, pTransform->GetRotationVec().y* 0.0174532925f / 2);
   // rz.Rotate(0.0f, 0.f, 1.f, pTransform->GetRotationVec().z* 0.0174532925f / 2);
   // rx.RotateX(MATH_DEG_TO_RAD(pTransform->GetRotationVec().x)* 0.0174532925f / 2);
   // ry.RotateY(MATH_DEG_TO_RAD(pTransform->GetRotationVec().y)* 0.0174532925f / 2);
   // rz.RotateZ(MATH_DEG_TO_RAD(pTransform->GetRotationVec().z)* 0.0174532925f / 2);
    //r = rx * ry * rz;
   model.Transform(t, r, s);


    ourShader->SetMat4("model", model);
    _pEntity->GetComponentContainer().GetComponent<ComponentModel>()->SetWorldMat(model);

    // view/projection transformations
    Mat4 view = m_camera->GetViewMatrix();
    ourShader->SetMat4("view", view);

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    Mat4 projection = Perspective(DegreeToRadian(m_camera->zoom), (float)w / (float)h, 0.1f, 100.0f);
    ourShader->SetMat4("projection", projection);
}

void Renderer::MVPText(Entity* _pEntity)
{
    Shader* ourShader = m_pShader->GetShader("TEXT");
    // don't forget to enable shader before setting uniforms
    ourShader->Use();

    // render the loaded model
    Mat4 model;
    Mat4 t;
    Mat4 s;
    Mat4 r;
    ComponentTransform* pTransform = _pEntity->GetComponentContainer().GetComponent<ComponentTransform>();

    t.Translate(pTransform->GetPositionVec());
    s.Scale(pTransform->GetScaleVec());
    r.Rotate(pTransform->GetRotationVec()* 0.0174532925f);
    model.Transform(t, r, s);


    ourShader->SetMat4("model", model);

    // view/projection transformations
    Mat4 view = m_camera->GetViewMatrix();
    ourShader->SetMat4("view", view);

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    Mat4 projection = Perspective(DegreeToRadian(m_camera->zoom), (float)w / (float)h, 0.1f, 100.0f);
    ourShader->SetMat4("projection", projection);
}

void Renderer::MVP(Entity* _pEntity, Unit unit)
{
    Shader* ourShader = m_pShader->GetShader("PARTICLE");
    // don't forget to enable shader before setting uniforms
    ourShader->Use();

    // render the loaded model
    Mat4 model;
    Mat4 t;
    Mat4 s;
    Mat4 r;
    ComponentTransform* pTransform = _pEntity->GetComponentContainer().GetComponent<ComponentTransform>();
    
    t.Translate(unit.Position + pTransform->GetPositionVec());
    s.Scale(unit.Scale);
    r.Rotate(pTransform->GetRotationVec(), MATH_DEG_TO_RAD(unit.Angle));
    //r.SetIdentity();
    model.Transform(t, r, s);

    ourShader->SetMat4("model", model);

    // view/projection transformations
    Mat4 view = m_camera->GetViewMatrix();
    ourShader->SetMat4("view", view);

    int w, h;
    SDL_GetWindowSize(m_pWindow, &w, &h);
    Mat4 projection = Perspective(DegreeToRadian(m_camera->zoom), (float)w / (float)h, 0.1f, 100.0f);
    ourShader->SetMat4("projection", projection);
}

void Renderer::DrawLight(Light* _pLight, int i)
{
    Shader* ourShader = m_pShader->GetShader("EXAMPLE");
    ourShader->Use();
    ourShader->SetVec3("Lights[" + std::to_string(i) + "].position", _pLight->position);
    ourShader->SetVec3("Lights[" + std::to_string(i) + "].direction", _pLight->direction);
    ourShader->SetVec4("Lights[" + std::to_string(i) + "].ambient", _pLight->ambient);
    ourShader->SetVec4("Lights[" + std::to_string(i) + "].diffuse", _pLight->diffuse);
    ourShader->SetVec4("Lights[" + std::to_string(i) + "].specular", _pLight->specular);
    ourShader->SetFloat("Lights[" + std::to_string(i) + "].cutOff", _pLight->cutOff);
    ourShader->SetFloat("Lights[" + std::to_string(i) + "].outerCutOff", _pLight->outerCutOff);
    ourShader->SetInt("Lights[" + std::to_string(i) + "].lightType", static_cast<int>(_pLight->lightType));
    ourShader->SetInt("Lights[" + std::to_string(i) + "].fallOff", _pLight->fallOff);

    ourShader->SetVec4("mat.diffuse", _pLight->diffuse);
    ourShader->SetInt("mat.modelType", _pLight->cube->m_modelType);
    _pLight->cube->Draw(*ourShader);
}

void Renderer::DrawModel(Entity* _pEntity)
{
    ComponentModel* pModel = _pEntity->GetComponentContainer().GetComponent<ComponentModel>();
    //pModel->SetRenderCheck(false);
    Shader* ourShader = m_pShader->GetShader("EXAMPLE");
    ourShader->Use();
    ourShader->SetInt("mat.modelType", pModel->GetModelType());

    ourShader->SetVec4("mat.ambient", pModel->GetAmbient());
    ourShader->SetVec4("mat.diffuse", pModel->GetDiffuse());
    ourShader->SetVec4("mat.specular", pModel->GetSpecular());
    ourShader->SetVec4("mat.emmisive", pModel->GetEmissive());

    ourShader->SetFloat("mat.shininess", pModel->GetShininess());
    ourShader->SetFloat("mat.constant", pModel->GetConstant());
    ourShader->SetFloat("mat.linear", pModel->GetLinear());
    ourShader->SetFloat("mat.quadratic", pModel->GetQuatratic());

    /*
  Shader* ourShader = m_pShader->GetShader("EXAMPLE");
  ourShader->SetInt("mat.modelType", _pModel->m_modelType);

  ourShader->SetVec4("mat.ambient", _pModel->ambient);
    ourShader->SetVec4("mat.diffuse", _pModel->diffuse);
    ourShader->SetVec4("mat.specular", _pModel->specular);
    ourShader->SetVec4("mat.emmisive", _pModel->emmisive);

    ourShader->SetFloat("mat.shininess", _pModel->shininess);
    ourShader->SetFloat("mat.constant", _pModel->constant);
    ourShader->SetFloat("mat.linear", _pModel->linear);
    ourShader->SetFloat("mat.quadratic", _pModel->quadratic);*/

    pModel->Draw(*ourShader);
}

void Renderer::DrawParticle(Entity* _pEntity, float dt)
{
    ParticleComponent* pModel = _pEntity->GetComponentContainer().GetComponent<ParticleComponent>();

    Shader* ourShader = m_pShader->GetShader("PARTICLE");
    ourShader->Use();
    //ourShader->SetVec3("", pModel->ScaleValue);
    //ourShader->SetVec4("color", pModel->GetColor());
    glUniform1i(glGetUniformLocation(ourShader->ID, "texture_particle"), 0);
    pModel->Update(dt);

    if (pModel->particleRenderType == ParticleRenderType::ADDITIVE)
        glDepthMask(GL_FALSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    for (Unit unit : pModel->particles)
    {
        if (unit.Life > 0.0f)
        {
            MVP(_pEntity, unit);
            ourShader->SetVec4("color", unit.Color);
            pModel->Draw();

        }
    }
    if (pModel->particleRenderType == ParticleRenderType::ADDITIVE)
        glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    
}

void Renderer::DrawModel(Model* _pModel)
{
    Shader* ourShader = m_pShader->GetShader("EXAMPLE");
    ourShader->Use();
    ourShader->SetInt("mat.modelType", _pModel->m_modelType);

    ourShader->SetVec4("mat.ambient", _pModel->ambient);
    ourShader->SetVec4("mat.diffuse", _pModel->diffuse);
    ourShader->SetVec4("mat.specular", _pModel->specular);
    ourShader->SetVec4("mat.emmisive", _pModel->emmisive);

    ourShader->SetFloat("mat.shininess", _pModel->shininess);
    ourShader->SetFloat("mat.constant", _pModel->constant);
    ourShader->SetFloat("mat.linear", _pModel->linear);
    ourShader->SetFloat("mat.quadratic", _pModel->quadratic);

    _pModel->Draw(*ourShader);
}

//void Renderer::AddModel(Model* _pModel)
//{
//  m_modelList.emplace_back(_pModel);
//}

void Renderer::AddLight(Light* _pLight)
{
    m_lightList.emplace_back(_pLight);
}

Mat4 Renderer::Perspective(float const & fovy, float const & aspect, float const & zNear, float const & zFar)
{
    float tanHalfFovy = tan(fovy / static_cast<float>(2));

    Mat4 Result;
    Result.SetZero();

    Result.m[0][0] = (1.f) / (aspect * tanHalfFovy);
    Result.m[1][1] = (1.f) / (tanHalfFovy);
    Result.m[2][2] = -(zFar + zNear) / (zFar - zNear);
    Result.m[2][3] = -(1.f);
    Result.m[3][2] = -((2.f) * zFar * zNear) / (zFar - zNear);
    return Result;
}

Mat4 Renderer::Ortho(float const & left, float const & right, float const & bottom, float const & top, float const & zNear, float const & zFar)
{
    Mat4 Result;
    Result.m[0][0] = (2.f) / (right - left);
    Result.m[1][1] = (2.f) / (top - bottom);
    Result.m[2][2] = (2.f) / (zFar - zNear);
    Result.m[3][0] = (-(right + left)) / (right - left);
    Result.m[3][1] = (-(top + bottom)) / (top - bottom);
    Result.m[3][2] = (-(zFar + zNear)) / (zFar - zNear);
    Result.m[3][3] = (1.f);
    return Result;
}

/******************************************************************************/
/*!
\brief - draw the texts
\param obj - object that has text component
*/
/******************************************************************************/
void Renderer::DrawTexts(Entity* _pEntity)
{
    ComponentText* text = _pEntity->GetComponentContainer().GetComponent<ComponentText>();
    ComponentTransform* trs = _pEntity->GetComponentContainer().GetComponent<ComponentTransform>();

    Vec4 color = text->GetColor();

    Shader* ourShader = m_pShader->GetShader("TEXT");
    ourShader->Use();

    ourShader->SetVec4("color", color);
    glEnable(GL_BLEND);

    // Set init values
    GLfloat new_x = 0;
    GLfloat new_y = 0;
    GLfloat init_x = new_x, lower_y = 0;
    int num_newline = 1;

    // Iterate all character
    std::string::const_iterator c;
    for (c = text->GetText().begin(); c != text->GetText().end(); ++c)
    {
        const char newline = *c;
        if (newline == '\n')
        {
            new_x = init_x;
            lower_y = GLfloat(text->GetFontData().m_fontSize * num_newline);
            ++num_newline;
        }

        else
        {
            Character ch = text->GetFontData().m_chars[*c];
            GLfloat xpos = new_x + ch.Bearing.x * trs->GetScaleVec().x;
            GLfloat ypos = new_y - (ch.Size.y - ch.Bearing.y) * trs->GetScaleVec().y - lower_y;
            GLfloat zpos = trs->GetPositionVec().z;

            GLfloat w = ch.Size.x * trs->GetScaleVec().x;
            GLfloat h = ch.Size.y * trs->GetScaleVec().y;

            GLfloat vertices[6][5] = {
                { xpos, ypos + h, zpos, 0.0, 0.0 },
                { xpos + w, ypos + h, zpos, 1.0, 0.0 },
                { xpos + w, ypos, zpos, 1.0, 1.0 },
                { xpos + w, ypos, zpos, 1.0, 1.0 },
                { xpos, ypos, zpos, 0.0, 1.0 },
                { xpos, ypos + h, zpos, 0.0, 0.0 }
            };

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //int t = static_cast<int>(ch.Advance);
            new_x += ((ch.Advance) >> 6) * trs->GetScaleVec().x;
        }

    }
    glDisable(GL_BLEND);
    //glDisable(GL_CULL_FACE);
}
