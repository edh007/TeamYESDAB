#pragma once

class Vec3
{
public:

	union
	{
		struct
		{
			float x, y, z;
		};

		float v[3];
	};
	

	Vec3();
	Vec3(float tx, float ty, float tz);
	Vec3(float* array);
	Vec3(const Vec3& rhs);
	//Vec3(const Vec3& p1, const Vec3& p2); // Direction between the given points

	void Set(float tx, float ty, float tz);
	void Set(const Vec3& v);
	void SetZero();

	void Add(float dx, float dy, float dz);
	void Add(const Vec3& v);
	void Subtract(float dx, float dy, float dz);
	void Subtract(const Vec3& v);


	void Negate();

	//bool IsZero() const;
	//bool IsOne() const;

	float DotProduct(const Vec3& rhs) const;
	Vec3 CrossProduct(const Vec3& rhs) const;

	float Length() const;
	float LengthSq() const;

	float Distance(const Vec3& rhs) const;
	float DistanceSq(const Vec3& rhs)  const;

	Vec3& Normalize();
	Vec3 GetNormalizedVec() const;

    Vec3 RadToDeg() const;

	// Operators
	Vec3 operator+(const Vec3& rhs) const;
  Vec3 operator+(const float rhs) const;
	Vec3& operator+=(const Vec3& rhs);
    Vec3& operator+=(const float rhs);
	Vec3 operator-(const Vec3& rhs) const;
  Vec3 operator-(const float rhs) const;
	Vec3& operator-=(const Vec3& rhs);

	Vec3 operator*(float s) const;
	Vec3& operator*=(float s);
	Vec3 operator/(float s) const;
	Vec3& operator/=(float s);

	Vec3 operator-() const;

	bool operator==(const Vec3& rhs) const;
	bool operator!=(const Vec3& rhs) const;
};

Vec3 operator*(float s, const Vec3& rhs);

Vec3 CrossProduct(const Vec3& lhs, const Vec3& rhs);