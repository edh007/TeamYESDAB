#pragma once

class Vec2
{
public:
	float x, y;

	Vec2();
	Vec2(float _x, float _y);
	//Vec2(float* array);
	Vec2(const Vec2& v);


	void Set(float _x, float _y);
	void Set(const Vec2& v);
	void SetZero();

	void Add(float _x, float _y);
	void Add(const Vec2& v);
	void Subtract(float _x, float _y);
	void Subtract(const Vec2& v);


	void Negate();

	//bool IsZero() const;
	//bool IsOne() const;

	/*float DotProduct(const Vec2& v) const;
	Vec2 CrossProduct(const Vec2& v) const;

	float Length() const;
	float LengthSq() const;

	float Distance(const Vec2& v) const;
	float DistanceSq(const Vec2& v)  const;

	Vec2& Normalize();
	Vec2 GetNormalizedVec() const;*/

	// Operators
	Vec2 operator+(const Vec2& v) const;
	Vec2& operator+=(const Vec2& v);
	Vec2 operator-(const Vec2& v) const;
	Vec2& operator-=(const Vec2& v);

	Vec2 operator*(float s) const;
	Vec2& operator*=(float s);
	Vec2 operator/(float s) const;
	Vec2& operator/=(float s);

	Vec2 operator-() const;

	bool operator==(const Vec2& v) const;
	bool operator!=(const Vec2& v) const;
};
