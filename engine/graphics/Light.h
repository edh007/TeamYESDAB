#pragma once

#include "math/Math.h"
#include "Model.h"

enum class LightType
{
    DIRECTION = 0,
    POINT = 1,
    SPOT = 2,
    NOT_EXISTING = 3,
    COUNT
};

class Light
{
public:
    // positional light
    Light(Vec3 _direction, Vec3 const &_position, Vec4 const &_ambient = Vec4(0.f, 0.f, 0.f, 1.f),
        Vec4 const &_diffuse = Vec4(1.f, 1.f, 1.f, 1.f), Vec4 const &_specular = Vec4(1.f, 1.f, 1.f, 1.f),
        LightType const &_lt = LightType::POINT);

	~Light();

    // setup so it can be copied right over to the GPU
    Vec3 direction;
    Vec4 ambient;
    Vec4 diffuse;

    Vec4 specular;
    LightType lightType;
    Vec3 position;
    int fallOff;
    float cutOff, outerCutOff;

	Model* cube;
};