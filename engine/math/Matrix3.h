#pragma once

#include "math\Vector3.h"

// TODO (JIN) : Move macros into other files
#define MATRIX3_SIZE (sizeof(float)*9)
#define MATRIX3_INDEX_MAX 9

class Mat3
{
public:
	union {
		struct{
#ifdef COLUMN_BASIS
			float m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22;
#else // ROW_BASIS
			float m00, m10, m20,
				m01, m11, m21,
				m02, m12, m22;
#endif // COLUMN_BASIS
		};
		float element[9];
		float m[3][3];
	};

	Mat3();
	Mat3(float p00, float p01, float p02,
		float p10, float p11, float p12,
		float p20, float p21, float p22);
	Mat3(const float* array);
	Mat3(const Mat3& copy);

	void Set(float p00, float p01, float p02,
		float p10, float p11, float p12,
		float p20, float p21, float p22);
	void Set(const float* array);
	void Set(const Mat3& copy);

	void SetZero();
	void SetIdentity();

	void Transpose();
	Mat3 GetTransposed() const;

	// float Determinant() const;

	void Inverse();
	Mat3 GetInverseMatrix() const;

	void Scale(float x, float y, float z);
	void Scale(const Vec3& rhs);

	void Rotate(float x, float y, float z, float radian);
	void Rotate(const Vec3& axis, float radian);
	void RotateX(float radian);
	void RotateY(float radian);
	void RotateZ(float radian);
	//void Rotate(const Quaternion& q);

	void Translate(float x, float y, float z);
	void Translate(const Vec3& rhs);

	Mat3 operator+(const Mat3& rhs) const;
	Mat3& operator+=(const Mat3& rhs);
	Mat3 operator-(const Mat3& rhs) const;
	Mat3& operator-=(const Mat3& rhs);
	Mat3 operator*(const Mat3& rhs) const;
	Mat3& operator*=(const Mat3& rhs);
    Vec3 operator*(const Vec3& rhs) const;

	Mat3 operator*(float s) const;
	Mat3& operator*=(float s);
	Mat3 operator/(float s) const;
	Mat3& operator/=(float s);

	Vec3& operator[](unsigned index);
	// TODO(JIN) : Need to understand when const work
	const Vec3& operator[](unsigned index) const;

	bool operator==(const Mat3& mat) const;
	bool operator!=(const Mat3& mat) const;

	static const Mat3 ZERO;
	static const Mat3 IDENTITY;
};
