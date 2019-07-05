#pragma once

class Vec4
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};

		float v[4];
	};

	Vec4();
	Vec4(float tx, float ty, float tz, float wa);
	Vec4(float* array);
	Vec4(const Vec4& copy);

	void Set(float tx, float ty, float tz, float tw);
	void Set(const Vec4& copy);
	void SetZero();

	void Negate();

	//bool IsZero() const;
	//bool IsOne() const;

	float DotProduct(const Vec4& rhs) const;

	float Length() const;
	float LengthSq() const;

	float Distance(const Vec4& rhs) const;
	float DistanceSq(const Vec4& rhs) const;

	Vec4& Normalize();
	Vec4 GetNormalized() const;


	// Operators
	Vec4 operator+(const Vec4& rhs) const;
	Vec4& operator+=(const Vec4& rhs);
	Vec4 operator-(const Vec4& rhs) const;
	Vec4& operator-=(const Vec4& rhs);

	Vec4 operator*(float s) const;
	Vec4& operator*=(float s);
	Vec4 operator/(float s) const;
	Vec4& operator/=(float s);

	Vec4 operator-() const;

	bool operator==(const Vec4& rhs) const;
	bool operator!=(const Vec4& rhs) const;
};

Vec4 operator*(float s, const Vec4& rhs);