#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"

// TODO (JIN) : Move macros into other files
#define MATRIX4_SIZE (sizeof(float)*16)
#define MATRIX4_INDEX_MAX 16

class  Mat4
{
public:
	union
	{
		struct
		{
#ifdef COLUMN_BASIS
			float m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33;
#else
			float m00, m10, m20, m30,
				m01, m11, m21, m31,
				m02, m12, m22, m32,
				m03, m13, m23, m33;
#endif // COLUMN_BASIS
		};
		float m[4][4];
		float element[16];
	};

	Mat4();
	Mat4(float p00, float p01, float p02, float p03,
		float p10, float p11, float p12, float p13,
		float p20, float p21, float p22, float p23,
		float p30, float p31, float p32, float p33);
	Mat4(const float* array);
	Mat4(const Mat4& copy);

	void Set(float p00, float p01, float p02, float p03,
		float p10, float p11, float p12, float p13,
		float p20, float p21, float p22, float p23,
		float p30, float p31, float p32, float p33);
	void Set(const float* array);
	void Set(const Mat4& copy);

	void SetZero();
	void SetIdentity();

	void Transpose();
	Mat4 GetTransposed() const;

	//float Determinant() const;

	void Inverse();
	Mat4 GetInverseMatrix() const;

	void Scale(float x, float y, float z);
	void Scale(const Vec3& rhs);

	void Rotate(float x, float y, float z, float radian);
	void Rotate(const Vec3& rhs, float radian);
    void Rotate(const Vec3& rhs);
    Mat4 Mat4::Concat(Mat4 rhs) const;

	void RotateX(float radian);
	void RotateY(float radian);
	void RotateZ(float radian);

	void Translate(float x, float y, float z);
	void Translate(const Vec3& rhs);

	void Transform(const Mat4& translation, const Mat4& rotation, const Mat4& scaling);

    Mat3 ToMatrix3();

	Mat4 operator+(const Mat4& rhs) const;
	Mat4& operator+=(const Mat4& rhs);
	Mat4 operator-(const Mat4& rhs) const;
	Mat4& operator-=(const Mat4& rhs);
	Mat4 operator*(const Mat4& rhs) const;
	Mat4& operator*=(const Mat4& rhs);

	Mat4 operator*(float s) const;
	Mat4& operator*=(float s);
	Mat4 operator/(float s) const;
	Mat4& operator/=(float s);

	Vec4& operator[](unsigned index);
	// TODO(JIN) : Need to understand when const work
	const Vec4& operator[](unsigned index) const;

	bool operator==(const Mat4& mat) const;
	bool operator!=(const Mat4& mat) const;

	static const Mat4 ZERO;
	static const Mat4 IDENTITY;

private:
	float GetMinorMat(unsigned i0, unsigned i1, unsigned i2,
		unsigned i3, unsigned i4, unsigned i5,
		unsigned i6, unsigned i7, unsigned i8);
};

