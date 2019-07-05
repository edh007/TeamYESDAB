#include "Vec2.h"

Vec2::Vec2()
	: x(0.f), y(0.f)
{
}

Vec2::Vec2(float _x, float _y)
	: x(_x), y(_y)
{
}


Vec2::Vec2(const Vec2& v)
	: x(v.x), y(v.y)
{

}

void Vec2::Set(float _x, float _y)
{
	x = _x; y = _y;
}

void Vec2::Set(const Vec2& v)
{
	x = v.x; y = v.y;
}

void Vec2::SetZero()
{
	x = y = 0.f;
}

void Vec2::Add(float _x, float _y)
{
	x += _x; y += _y;
}

void Vec2::Add(const Vec2& v)
{
	x += v.x; y += v.y;
}

void Vec2::Subtract(float _x, float _y)
{
	x -= _x; y -= _y;
}

void Vec2::Subtract(const Vec2& v)
{
	x -= v.x; y -= v.y;
}

void Vec2::Negate()
{
	x *= -1; y *= -1;
}

Vec2 Vec2::operator+(const Vec2& v) const
{
	return Vec2(x + v.x, y + v.y);
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	Add(v);
	return *this;
}

Vec2 Vec2::operator-(const Vec2& v) const
{
	return Vec2(x - v.x, y - v.y);
}

Vec2& Vec2::operator-=(const Vec2& v)
{
	Subtract(v);
	return *this;
}

Vec2 Vec2::operator*(float s) const
{
	return Vec2(x * s, y * s);
}

Vec2& Vec2::operator*=(float s)
{
	x *= s; y *= s;
	return *this;
}

Vec2 Vec2::operator/(float s) const
{
	// TODO(JIN) Assert when s == 0
	s = 1.f / s;
	return Vec2(x*s, y*s);
}

Vec2& Vec2::operator/=(float s)
{
	// TODO(JIN) Assert when s == 0
	s = 1.f / s;
	x *= s; y *= s;
	return *this;
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

bool Vec2::operator==(const Vec2& v) const
{
	return (x == v.x) && (y == v.y);
}

bool Vec2::operator!=(const Vec2& v) const
{
	return (x != v.x) || (y != v.y);
}
