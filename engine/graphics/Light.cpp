#include "Light.h"


// Initialize the light structure.
Light::Light(Vec3 _direction, Vec3 const &_position,
    Vec4 const &_ambient/* = Vec4::White*/,
    Vec4 const &_diffuse/* = Vec4::White*/,
    Vec4 const &_specular/* = Vec4::White */,
    LightType const &_lt/* = Vec4::White */)
    : direction(_direction.Normalize()), ambient(_ambient), diffuse(_diffuse), specular(_specular), lightType(_lt), position(_position)
{
    fallOff = 1;
    cutOff = 15.f;
    outerCutOff = 30.f;
    specular = Vec4();
	cube = new Model(ModelType::LIGHT);
	cube->pos = position;
	cube->scl = Vec3(0.1f,0.1f,0.1f);
}

Light::~Light()
{
	delete cube;
}