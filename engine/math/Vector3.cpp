#include "Vector3.h"

// TODO(JIN) : check that precompiled is needed or not.
#include <cmath>

Vec3::Vec3()
	: x(0.f), y(0.f), z(0.f)
{
}

Vec3::Vec3(float tx, float ty, float tz)
	: x(tx), y(ty), z(tz)
{
}

// TODO(JIN) 
Vec3::Vec3(float* array)
{
	array;
}

Vec3::Vec3(const Vec3& rhs)
	: x(rhs.x), y(rhs.y), z(rhs.z)
{
}

void Vec3::Set(float tx, float ty, float tz)
{
	x = tx; y = ty; z = tz;
}

void Vec3::Set(const Vec3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vec3::SetZero()
{
	x = y = z = 0.f;
}

void Vec3::Add(float dx, float dy, float dz)
{
	x += dx;
	y += dy;
	z += dz;
}

void Vec3::Add(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vec3::Subtract(float dx, float dy, float dz)
{
	x -= dx;
	y -= dy;
	z -= dz;
}

void Vec3::Subtract(const Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}


void Vec3::Negate()
{
	x *= -1.f; y *= -1; z *= -1;
}

float Vec3::DotProduct(const Vec3& rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vec3 Vec3::CrossProduct(const Vec3& rhs) const
{
	return Vec3(
		(y * rhs.z) - (z * rhs.y),
		(z * rhs.x) - (x * rhs.z),
		(x * rhs.y) - (y * rhs.x)
	);
}

float Vec3::Length() const
{
	return sqrtf(x*x + y*y + z*z);
}

float Vec3::LengthSq() const
{
	return x*x + y*y + z*z;
}

float Vec3::Distance(const Vec3& rhs) const
{
	return (rhs - *this).Length();
}

float Vec3::DistanceSq(const Vec3& rhs) const
{
	return (rhs - *this).LengthSq();
}

Vec3& Vec3::Normalize()
{
	float l = Length();
	l = 1.f / l;
	*this *= l;
	return *this;
}

Vec3 Vec3::GetNormalizedVec() const
{
	Vec3 rst(*this);
	rst.Normalize();
	return rst;
}

Vec3 Vec3::RadToDeg() const
{
    Vec3 degVec = *this;
    degVec += 1.f;
    degVec *= 180.f;

    return degVec;
}

Vec3 Vec3::operator+(const Vec3& rhs) const
{
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3 Vec3::operator+(const float rhs) const
{
  return Vec3(x + rhs, y + rhs, z + rhs);
}

Vec3& Vec3::operator+=(const Vec3& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
	return *this;
}

Vec3& Vec3::operator+=(const float rhs)
{
    x += rhs; y += rhs; z += rhs;
    return *this;
}

Vec3 Vec3::operator-(const Vec3& rhs) const
{
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3 Vec3::operator-(const float rhs) const
{
  return Vec3(x - rhs, y - rhs, z - rhs);
}

Vec3& Vec3::operator-=(const Vec3& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
	return *this;
}

Vec3 Vec3::operator*(float s) const
{
	return Vec3(x*s, y*s, z*s);
}

Vec3& Vec3::operator*=(float s)
{
	x *= s; y *= s; z *= s;
	return *this;
}

Vec3 Vec3::operator/(float s) const
{
	// TODO(JIN) Assert when s == 0
	s = 1.f / s;
	return Vec3(x*s, y*s, z*s);
}

Vec3& Vec3::operator/=(float s)
{
	// TODO(JIN) Assert when s == 0
	s = 1.f / s;
	x *= s; y *= s; z *= s;
	return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

bool Vec3::operator==(const Vec3& rhs) const
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

bool Vec3::operator!=(const Vec3& rhs) const
{
	return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

Vec3 operator*(float s, const Vec3& rhs)
{
	return Vec3(rhs) * s;
}

Vec3 CrossProduct(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(
		(lhs.y * rhs.z) - (lhs.z * rhs.y),
		(lhs.z * rhs.x) - (lhs.x * rhs.z),
		(lhs.x * rhs.y) - (lhs.y * rhs.x)
	);
}