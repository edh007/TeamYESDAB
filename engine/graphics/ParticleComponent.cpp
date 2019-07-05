/******************************************************************************/
/*!
\file   ParticleComponent.cpp
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)
\description
Contains Particle class
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "ParticleComponent.h"
#include "math/MathUtil.h"
#include <imgui.h>
#include <stb_image.h>

using namespace gi;

int	GetRandomInt(int left = INT_MIN, int right = INT_MAX)
{
    int result = left + rand() % (right - left + 1);
    return result;
};

float GetRandomFloat(float left = FLT_MIN, float right = FLT_MAX)
{
    float result = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
    return result;
};

const std::string ParticleComponent::COMPONENT_ID = "gi_cmp_particle";

/******************************************************************************/
/*!
\brief - Particle constructor
\param Owner - Owner of this Component
\param key - ComponentType
*/
/******************************************************************************/
ParticleComponent::ParticleComponent(Entity* pObject)
    : Component(pObject)
{
    //if (!m_Owner->HasComponent(CT_TRANSFORM))
    //    m_Owner->AddComponent(ComponentFactory::CreateComponent(m_Owner, CT_TRANSFORM));

    this->init();
}


/******************************************************************************/
/*!
\brief - Particle Destructor
*/
/******************************************************************************/
ParticleComponent::~ParticleComponent(void)
{
    particles.clear();
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteBuffers(1, &VertexArrayID);
}

ParticleComponent* ParticleComponent::CreateParticleComponent(Entity* pOwner)
{
    ParticleComponent* pModel = new ParticleComponent(pOwner);
    pModel->init();
    return pModel;
}

/******************************************************************************/
/*!
\brief - Initialize Particle info
*/
/******************************************************************************/
void ParticleComponent::init()
{
    EmissionRate = (10), p_speed = Vec3(1.f, 1.f, 1.f), active = (true), count = (0), countCheck = (0), Time = (0), EndScale = (0);
    scaleMinusValue = (0), particleRenderType = (ADDITIVE), SpinCheck = (true), ForcedQuit = (false), laser_length = (200), Player_Angle = (0);
    id = LoadTexture("../../resources/textures/particle/particle.png");
}

/******************************************************************************/
/*!
\brief - Update Particle info
\param dt - delta time
*/
/******************************************************************************/
void ParticleComponent::Update(GLfloat dt)
{
    float new_dt = dt * 0.5f;
    // Set new dt here
    //float new_dt = m_Owner->GetdtOffset() * dt;

    if (active == true)
    {
            Normal(new_dt);
    }
    else
    {
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles[i].Life = 0;
        SetUnitsPosition(Vec3(1000.f, 1000.f, 1000.f));
    }

}

/******************************************************************************/
/*!
\brief - setting whole particle units with input
\param position - setting whole particle units in this position
*/
/******************************************************************************/
void ParticleComponent::SetUnitsPosition(Vec3 position)
{
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        particles[i].Position.x = position.x;
        particles[i].Position.y = position.y;
        particles[i].Position.z = position.z;
    }
}

/******************************************************************************/
/*!
\brief - force quitting the particle update
*/
/******************************************************************************/
void ParticleComponent::ForceQuitting(void)
{
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        particles[i].Life = 0.f;
        particles[i].Position.x = 2000.f;
        particles[i].Color.w = 0;
    }
    ForcedQuit = true;
}

/******************************************************************************/
/*!
\brief - update usual normal particles with this function
\param dt - delta time
*/
/******************************************************************************/
void ParticleComponent::Normal(float dt)
{
    // Loop Through All The Particles
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        Unit &p = particles[i];

        if (p.Life > 0.f) {
            ColorChange = (ColorInit - ColorEnd) * dt;

            // Reduce Particles Life By 'Dt'
            p.Life -= dt;
            p.Color -= ColorChange;

            p.Position.x += p.Velocity.x * (dt);
            p.Position.y += p.Velocity.y * (dt);
            p.Position.z += p.Velocity.z * (dt);
            p.Position.x += (Gravity.x / 5.f) * dt;
            p.Position.y += (Gravity.y / 5.f) * dt;
            p.Position.z += (Gravity.z / 5.f) * dt;

            if (ScaleValue.x < EndScale.x)
            {
                scaleMinusValue = (EndScale - ScaleValue) * dt;
                if (p.Scale.x < EndScale.x)
                    p.Scale = Vec3(p.Scale.x + scaleMinusValue.x, p.Scale.y + scaleMinusValue.y, p.Scale.z + scaleMinusValue.z);
                else
                    p.Scale = Vec3(EndScale.x, EndScale.y, EndScale.z);
            }
            else
            {
                scaleMinusValue = (ScaleValue - EndScale) * dt;
                if (p.Scale.x > EndScale.x)
                    p.Scale = Vec3(p.Scale.x - scaleMinusValue.x, p.Scale.y - scaleMinusValue.y, p.Scale.z - scaleMinusValue.z);
                else
                    p.Scale = Vec3(EndScale.x, EndScale.y, EndScale.z);
            }


            if (SpinCheck == true)
                p.Angle += 5;
        }

        // If Particle Is Burned Out
        else if (p.Life <= 0.0f && p.Active == true)
        {
            if (ForcedQuit == true)
                p.Active = false;
            else if (count != 0)
            {
                p.countCheck++;
                if (count < p.countCheck)
                    p.Active = false;
            }

            p.Scale = Vec3(ScaleValue.x, ScaleValue.y, ScaleValue.z);

            p.Position.x = GetRandomFloat(p_position.x - EmitArea.x, p_position.x + EmitArea.x);
            p.Position.y = GetRandomFloat(p_position.y - EmitArea.y, p_position.y + EmitArea.y);
            p.Position.z = GetRandomFloat(p_position.z - EmitArea.z, p_position.z + EmitArea.z);

            // Give It New Life
            p.Life = GetRandomFloat(LifeInit - LifeVariable, LifeInit + LifeVariable);
            p.Angle = GetRandomInt(AngleInit - AngleVariable, AngleInit + AngleVariable);

            float x = cos(MATH_DEG_TO_RAD(float(p.Angle)));
            float y = sin(MATH_DEG_TO_RAD(float(p.Angle)));
            float z = sin(MATH_DEG_TO_RAD(float(p.Angle)));

            int speed = GetRandomInt(SpeedInitValue - SpeedVariable, SpeedInitValue + SpeedVariable);
            p.Velocity.x = (speed * x) / 5.f;
            p.Velocity.y = (speed * y) / 5.f;
            p.Velocity.z = (speed * z) / 5.f;

            p.Color = ColorInit;

            Time = 1.f;

            if (SpinCheck == true)
                p.Angle = GetRandomInt(0, 180);

        }

        if (p.Active == false)
        {
            p.Life = 0;
            p.Position = 0;
            p.Velocity = 0;
            p.countCheck = 0;
        }
    }

    if (count == 0)
        countCheck = 0;
}

/******************************************************************************/
/*!
\brief - make particle work again
*/
/******************************************************************************/
void ParticleComponent::Restore()
{
    for (GLuint i = 0; i < EmissionRate; ++i)
    {
        Unit &p = particles[i];
        p.Active = true;
        p.countCheck = 0;
    }
    ForcedQuit = false;
}

/******************************************************************************/
/*!
\brief - setting texture
\param texture - setting the particles texture
*/
/******************************************************************************/
void ParticleComponent::SetTexture(Texture* texture)
{
    m_texture = texture;
}

/******************************************************************************/
/*!
\brief - getting texture
\return m_texture - getting the particles texture
*/
/******************************************************************************/
Texture* ParticleComponent::GetTexture(void) const
{
    return m_texture;
}

/******************************************************************************/
/*!
\brief - setting color
\param color - setting the color
*/
/******************************************************************************/
void ParticleComponent::SetColor(const Vec4& color)
{
    m_color = color;
}

/******************************************************************************/
/*!
\brief - getting color
\return m_color - getting the color
*/
/******************************************************************************/
Vec4 ParticleComponent::GetColor(void) const
{
    return m_color;
}

/******************************************************************************/
/*!
\brief - Change the value of the particle
*/
/******************************************************************************/
void ParticleComponent::ChangeResolution(int cr)
{
    SpeedInitValue *= cr;
    SpeedVariable *= cr;
    Gravity.x *= cr;
    Gravity.y *= cr;
    Gravity.z *= cr;
    ScaleValue.x *= cr;
    ScaleValue.y *= cr;
    ScaleValue.z *= cr;
    EndScale.x *= cr;
    EndScale.y *= cr;
    EndScale.z *= cr;
    EmitArea.x *= cr;
    EmitArea.y *= cr;
    EmitArea.z *= cr;
}

void ParticleComponent::Draw()
{
    
    glActiveTexture(GL_TEXTURE0);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glBindTexture(GL_TEXTURE_2D, id);

    glBindVertexArray(VertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    //glActiveTexture(GL_TEXTURE0);
}

unsigned ParticleComponent::GetID()
{
    return id;
}

unsigned int ParticleComponent::LoadTexture(std::string faces)
{
    glGenVertexArrays(1, &VertexArrayID);
    glGenBuffers(1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glBindVertexArray(VertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //talk about 'vertexbuffer' buffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); //give vertices to openGL.
                                                                                                       // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size : X + Y + Z => 3
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        5 * sizeof(GLfloat),	// stride
        (GLvoid*)0				// array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        1,                              // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                              // size : U+V => 2
        GL_FLOAT,                       // type
        GL_FALSE,                        // normalized?
        5 * sizeof(GLfloat),			// stride
        (GLvoid*)(3 * sizeof(GLfloat))	// array buffer offset
    );

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    
    unsigned char *data = stbi_load(faces.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Particle texture failed to load at path: ";
        std::cout << faces.c_str() << std::endl;
        stbi_image_free(data);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureID;
}

/******************************************************************************/
/*!
\brief - setting variables value for particle
\param p_type - Get the type of particle to set
*/
/******************************************************************************/
void ParticleComponent::SetParticleVariables(ParticleType p_type)
{
    switch (p_type)
    {
    case P_RADAR:
        AngleInit = 90,
        AngleVariable = 0,
        SpeedInitValue = 0,
        SpeedVariable = 0,
        LifeInit = 1.f,
        LifeVariable = 0.9f,
        ColorInit.x = 1.f,
        ColorInit.y = 0.2f,
        ColorInit.z = 0.2f,
        ColorInit.w = 1,
        ColorEnd.x = 0,
        ColorEnd.y = 0,
        ColorEnd.z = 0,
        ColorEnd.w = 1,
        Gravity.x = 0,
        Gravity.y = 0,
            Gravity.z = 0,
        ScaleValue.x = 10,
        ScaleValue.y = 10,
            ScaleValue.z = 10,
        EndScale.x = 300,
        EndScale.y = 300,
            EndScale.z = 300,
        EmitArea.x = 0,
        EmitArea.y = 0,
            EmitArea.z = 0,
        count = 2;
        ForcedQuit = true;
        EmissionRate = 25;
        // Create this->EmissionRate default particle instances
        particles.reserve(EmissionRate);
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;
    case P_BOMB:
        AngleInit = 90,
        AngleVariable = 360,
        SpeedInitValue = 100.f,
        SpeedVariable = 10.f,
        LifeInit = 1.f,
        LifeVariable = 0,
        ColorInit.x = 0.75f,
        ColorInit.y = 0.25f,
        ColorInit.z = 0.11f,
        ColorInit.w = 1,
        ColorEnd.x = 0,
        ColorEnd.y = 0,
        ColorEnd.z = 0,
        ColorEnd.w = 1,
        Gravity.x = 0,
        Gravity.y = 0,
            Gravity.z = 0,
        ScaleValue.x = 5,
        ScaleValue.y = 5,
            ScaleValue.z = 35,
        EndScale.x = 0.f,
        EndScale.y = 0.f,
            EndScale.z = 0.f,
        EmitArea.x = 1,
        EmitArea.y = 1,
            EmitArea.z = 1,
        count = 1;
        ForcedQuit = true;
        active = false;
        EmissionRate = 100;
        // Create this->EmissionRate default particle instances
        particles.reserve(EmissionRate);
        for (GLuint i = 0; i < EmissionRate; ++i)
            particles.push_back(Unit());
        break;

    default:
        std::cout << "ERROR! NOT REGISTERED PARTICLE TYPE" << std::endl;
        break;
    }
}

void ParticleComponent::DrawComponent()
{
    if (ImGui::CollapsingHeader("Particle Component"))
    {
        ImGui::PushItemWidth(160);
        {
            ImGui::InputFloat("LifeInit", &LifeInit, 1.f, 256.f, 2);
            ImGui::InputFloat("LifeVariable", &LifeVariable, 1.f, 256.f, 2);
            if(ImGui::Button("Activate"))
            {
                active = true;
                Restore();
            }
            //ImGui::InputInt("Count", &count, 1, 256, 2);
            ImGui::InputInt("Count", &count);
            //ImGui::InputInt("Particle Render Type", &(particleRenderType), 1.f, 2.f, 2);

            ImGui::InputInt("EmissionRate", &EmissionRate);
            ImGui::InputInt("AngleInit", &AngleInit);
            ImGui::InputInt("AngleVariable", &AngleVariable);
            ImGui::InputInt("SpeedInitValue", &SpeedInitValue);
            ImGui::InputInt("SpeedVariable", &SpeedVariable);
            
            ImGui::InputFloat("EmitArea X", &EmitArea.x, 1.f, 256.f, 2);
            ImGui::InputFloat("EmitArea Y", &EmitArea.y, 1.f, 256.f, 2);
            ImGui::InputFloat("EmitArea Z", &EmitArea.z, 1.f, 256.f, 2);

            ImGui::InputFloat("Gravity X", &Gravity.x, 1.f, 256.f, 2);
            ImGui::InputFloat("Gravity Y", &Gravity.y, 1.f, 256.f, 2);
            ImGui::InputFloat("Gravity Z", &Gravity.z, 1.f, 256.f, 2);

            ImGui::InputFloat("Scale X", &ScaleValue.x, 1.f, 256.f, 2);
            ImGui::InputFloat("Scale Y", &ScaleValue.y, 1.f, 256.f, 2);
            ImGui::InputFloat("Scale Z", &ScaleValue.z, 1.f, 256.f, 2);

            ImGui::InputFloat("EndScale X", &EndScale.x, 1.f, 256.f, 2);
            ImGui::InputFloat("EndScale Y", &EndScale.y, 1.f, 256.f, 2);
            ImGui::InputFloat("EndScale Z", &EndScale.z, 1.f, 256.f, 2);

            ImGui::InputFloat("ColorInitRed", &ColorInit.x, 1.f, 256.f, 2);
            ImGui::InputFloat("ColorInitGreen", &ColorInit.y, 1.f, 256.f, 2);
            ImGui::InputFloat("ColorInitBlue", &ColorInit.z, 1.f, 256.f, 2);
            ImGui::InputFloat("ColorInitAlpha", &ColorInit.w, 1.f, 256.f, 2);

            ImGui::InputFloat("ColorEndRed", &ColorEnd.x, 1.f, 256.f, 2);
            ImGui::InputFloat("ColorEndGreen", &ColorEnd.y, 1.f, 256.f, 2);
            ImGui::InputFloat("ColorEndBlue", &ColorEnd.z, 1.f, 256.f, 2);
            ImGui::InputFloat("ColorEndAlpha", &ColorEnd.w, 1.f, 256.f, 2);
        }
        ImGui::PopItemWidth();
    }

}