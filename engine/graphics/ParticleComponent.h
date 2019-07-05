/******************************************************************************/
/*!
\file   ParticleComponent.h
\author Dongho Lee
\par    email: edongho007\@gmail.com
\date   2016/07/24(yy/mm/dd)

\description
Contains Sprite class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once

#include <vector>
#include <algorithm>

#include "base/Component.h"
#include "Mesh.h"

using namespace gi;

static const GLfloat g_vertex_buffer_data[] =
{
    //		X		Y		Z		U		V
    .5f, .5f, 0.f, 1.f, 0.f , /*1*/
    -.5f, .5f, 0.f, 0.f, 0.f , /*2*/
    -.5f, -.5f, 0.f, 0.f, 1.f , /*3*/

    -.5f, -.5f, 0.f, 0.f, 1.f , /*4*/
    .5f, -.5f, 0.f, 1.f, 1.f , /*5*/
    .5f, .5f, 0.f, 1.f, 0.f
};

// Represents a single particle and its state
struct Unit {
    Vec3 Position, Velocity;
    Vec4 Color;
    GLfloat Life;
    GLfloat countCheck;
    int Angle;
    Vec3 Scale;
    bool Active;
    Unit() : Position(), Velocity(0), Color(1.f, 1.f, 1.f, 1.f), Life(0.0f), countCheck(0.0f), Angle(0), Scale(0), Active(true) { }
};

enum ParticleRenderType { ADDITIVE, NORMALPARTICLE };
enum ParticleType { P_BOMB, P_RADAR };

// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class ParticleComponent : public Component
{
public:
    static const std::string COMPONENT_ID;
    static ParticleComponent* CreateParticleComponent(Entity* pOwner);
    explicit ParticleComponent(Entity* pObject);
    virtual ~ParticleComponent();
    // Constructor
    //Particle(Shader shader, GLuint amount);
    //ParticleComponent(Object* Owner = 0, ComponentType key = CT_PARTICLE);
    //virtual ~ParticleComponent(void);
    // Update all particles
    void Update(GLfloat dt);
    void SetUnitsPosition(Vec3 position);

    // Render all particles
    std::vector<Unit> particles;

    void SetColor(const Vec4& color);
    Vec4 GetColor(void) const;

    void SetTexture(Texture* texture);
    Texture* GetTexture(void) const;

    void ChangeResolution(int cr);
    Texture* m_texture;

    //Particle Variable
    Vec3 EmitArea;
    int EmissionRate;
    GLfloat LifeInit;
    GLfloat LifeVariable;
    int AngleInit;
    int AngleVariable;
    Vec3 Gravity;
    int SpeedInitValue;
    int SpeedVariable;
    Vec4 ColorInit;
    Vec4 ColorEnd;
    Vec3 ScaleValue;
    int countCheck;
    Vec4 ColorChange;
    Vec3 EndScale;
    Vec3 scaleMinusValue;
    Vec4 m_color;
    Vec3 p_speed;
    Vec3 p_position;
    bool active;
    int count;
    float Time;

    bool SpinCheck;
    ParticleRenderType particleRenderType;
    ParticleType particleType;
    bool ForcedQuit;
    void Restore();
    void SetParticleVariables(ParticleType p_type);
    void ForceQuitting(void);

    int laser_length;
    int Player_Angle;
    void DrawComponent();
    unsigned int LoadTexture(std::string faces);
    void Draw();
    unsigned GetID();
private:
    // Initializes buffer and vertex attributes
    void init();
    void Normal(float dt);
    unsigned int id;
    GLuint VertexArrayID;
    GLuint vertexbuffer;
    bool shaderCheck = false;
    //vec3 beforePosition;
};
