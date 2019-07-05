#include "Vector4.h"

// TODO(JIN) : check that precompiled is needed or not.
#include <cmath>

Vec4::Vec4()
	: x(0.f), y(0.f), z(0.f), w(0.f)
{
}

Vec4::Vec4(float tx, float ty, float tz, float tw): x(tx), y(ty), z(tz), w(tw)
{
}

// TODO(JIN)
Vec4::Vec4(float* array)
{
	array;
}

Vec4::Vec4(const Vec4& copy)
	: x(copy.x), y(copy.y), z(copy.z), w(copy.w)
{
}

void Vec4::Set(float tx, float ty, float tz, float tw)
{
	x = tx; y = ty; z = tz; w = tw;
}

void Vec4::Set(const Vec4& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
	w = copy.w;
}

void Vec4::SetZero()
{
	x = y = z = w = 0.f;
}

void Vec4::Negate()
{
	*this *= -1.f;
}

float Vec4::DotProduct(const Vec4& rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
}


float Vec4::Length() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

float Vec4::LengthSq() const
{
	return x*x + y*y + z*z + w*w;
}

float Vec4::Distance(const Vec4& rhs) const
{
	return (rhs - *this).Length();
}

float Vec4::DistanceSq(const Vec4& rhs) const
{
	return (rhs - *this).LengthSq();
}

Vec4& Vec4::Normalize()
{
	float l = Length();
	l = 1.f / l;
	*this *= l;

	return *this;
}

Vec4 Vec4::GetNormalized() const
{
	Vec4 rst(*this);
	rst.Normalize();
	return rst;
}

Vec4 Vec4::operator+(const Vec4& rhs) const
{
	return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vec4& Vec4::operator+=(const Vec4& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
	return *this;
}

Vec4 Vec4::operator-(const Vec4& rhs) const
{
	return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vec4& Vec4::operator-=(const Vec4& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
	return *this;
}

Vec4 Vec4::operator*(float s) const
{
	return Vec4(x*s, y*s, z*s, w*s);
}

Vec4& Vec4::operator*=(float s)
{
	x *= s; y *= s; z *= s; w *= w;
	return *this;
}

Vec4 Vec4::operator/(float s) const
{
	// TODO(JIN) Assert when s == 0
	s = 1.f / s;
	return Vec4(x*s, y*s, z*s, w*s);
}

Vec4& Vec4::operator/=(float s)
{
	// TODO(JIN) Assert when s == 0
	s = 1.f / s;
	x *= s; y *= s; z *= s; w *= w;
	return *this;
}

Vec4 Vec4::operator-() const
{
	return Vec4(-x, -y, -z, -w);
}

bool Vec4::operator==(const Vec4& rhs) const
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

bool Vec4::operator!=(const Vec4& rhs) const
{
	return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

Vec4 operator*(float s, const Vec4& rhs)
{
	return Vec4(rhs) * s;
}
