#pragma once

#include "Vector3.h"
#include "Vector4.h"

#include "Matrix3.h"
#include "Matrix4.h"

#define MATH_EPSILON				0.00000001f
#define MATH_PI						3.14159265358979323846f
#define MATH_PIOVER2				1.57079632679489661923f

// TODO(JIN) : Choose one way
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)

float DegreeToRadian(float degree);
float RadianToDegree(float radian);

Mat4 GetTranslation(float x, float y, float z);
Mat4 GetTranslation(const Vec3& v);

Mat4 GetRotation(float x, float y, float z, float radian);
Mat4 GetRotation(const Vec3& v, float radian);
Mat4 GetRotationX(float rad);
Mat4 GetRotationY(float rad);
Mat4 GetRotationZ(float rad);

Mat4 GetScaling(float x, float y, float z); 
Mat4 GetScaling(const Vec3& v);

Mat4 GetTransform(const Mat4& translation, const Mat4& rotation, const Mat4& scaling);

// TODO(JIN) : it may Need to change name
Mat4 GetLookAt(const Vec3& eye, const Vec3& target, const Vec3&  up);
