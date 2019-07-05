#include  "Matrix3.h"

// TODO(JIN) : 
#include <cstring>
#include <iostream>

const Mat3 Mat3::ZERO(
	0.f, 0.f, 0.f,
	0.f, 0.f, 0.f,
	0.f, 0.f, 0.f);

const Mat3 Mat3::IDENTITY(
	1.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f);

Mat3::Mat3()
{
	*this = IDENTITY;
}

Mat3::Mat3(float p00, float p01, float p02, float p10, float p11, float p12, float p20, float p21, float p22)
{
	Set(p00, p01, p02,
		p10, p11, p12,
		p20, p21, p22);
}

Mat3::Mat3(const float* array)
{
	Set(array);
}

Mat3::Mat3(const Mat3& copy)
{
	Set(copy);
}

void Mat3::Set(float p00, float p01, float p02, float p10, float p11, float p12, float p20, float p21, float p22)
{
	p00; p01; p02;
	p10; p11; p12;
	p20; p21; p22;
}

void Mat3::Set(const float* array)
{
	std::memcpy(element, array, MATRIX3_SIZE);
}

void Mat3::Set(const Mat3& copy)
{
	std::memcpy(element, copy.element, MATRIX3_SIZE);
}

void Mat3::SetZero()
{
	std::memset(element, 0, MATRIX3_SIZE);
}

void Mat3::SetIdentity()
{
	*this = IDENTITY;
}

void Mat3::Transpose()
{
	std::swap(m01, m10);
	std::swap(m02, m20);
	std::swap(m12, m21);
}

Mat3 Mat3::GetTransposed() const
{
	Mat3 rst(*this);
	rst.Transpose();

	return rst;
}

// TODO(JIN) : 
void Mat3::Inverse()
{
}

Mat3 Mat3::GetInverseMatrix() const
{
	Mat3 rst(*this);
	rst.Inverse();
	return rst;
}

void Mat3::Scale(float x, float y, float z)
{
	SetIdentity();

	m00 = x;
	m11 = y;
	m22 = z;
}

void Mat3::Scale(const Vec3& rhs)
{
	rhs;
}

void Mat3::Rotate(float x, float y, float z, float radian)
{
	x; y; z; radian;
}

void Mat3::Rotate(const Vec3& axis, float radian)
{
	axis; radian;
}

void Mat3::RotateX(float radian)
{
	radian;
}

void Mat3::RotateY(float radian)
{
	radian;
}

void Mat3::RotateZ(float radian)
{
	radian;
}

void Mat3::Translate(float x, float y, float z)
{
	x; y; z;
}

void Mat3::Translate(const Vec3& rhs)
{
	rhs;
}

Mat3 Mat3::operator+(const Mat3& rhs) const
{
	return Mat3(*this) += rhs;
}

Mat3& Mat3::operator+=(const Mat3& rhs)
{
	for (unsigned i = 0; i < MATRIX3_INDEX_MAX; ++i)
		element[i] += rhs.element[i];

	return *this;
}

Mat3 Mat3::operator-(const Mat3& rhs) const
{
	return Mat3(*this) -= rhs;
}

Mat3& Mat3::operator-=(const Mat3& rhs)
{
	for (unsigned i = 0; i < MATRIX3_INDEX_MAX; ++i)
		element[i] -= rhs.element[i];

	return *this;
}

Mat3 Mat3::operator*(const Mat3& rhs) const
{
	return Mat3(*this) *= rhs;
}

Mat3& Mat3::operator*=(const Mat3& rhs)
{
	float array[MATRIX3_INDEX_MAX];

	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			for (int i = 0; i < 3; ++i)
			{
				array[r * 3 + c] += m[r][i] * rhs.m[i][c];
			}
		}
	}

	memcpy(element, array, MATRIX3_SIZE);

	return *this;
}

Mat3 Mat3::operator*(float s) const
{
	return Mat3(*this) *= s;
}

Mat3& Mat3::operator*=(float s)
{
	for (unsigned i = 0; i < MATRIX3_INDEX_MAX; ++i)
		element[i] *= s;

	return *this;
}

Vec3 Mat3::operator*(const Vec3& rhs) const
{
    Vec3 vec3;

    vec3.x = m00 * rhs.x + m01 * rhs.y + m02 * rhs.z;
    vec3.y = m10 * rhs.x + m11 * rhs.y + m12 * rhs.z;
    vec3.z = m20 * rhs.x + m21 * rhs.y + m22 * rhs.z;

    return vec3;
}

Mat3 Mat3::operator/(float s) const
{
	return Mat3(*this) /= s;
}

Mat3& Mat3::operator/=(float s)
{
	// TODO(JIN) : DEBUG_ASSERT(std::fabs(s) == 0.f, "cannot be divided by zero\n");
	s = 1.f / s;

	for (unsigned i = 0; i < MATRIX3_INDEX_MAX; ++i)
		element[i] *= s;

	return *this;
}

Vec3& Mat3::operator[](unsigned index)
{
	return ((Vec3*)this)[index];
}

const Vec3& Mat3::operator[](unsigned index) const
{
	return ((Vec3*)this)[index];
}

bool Mat3::operator==(const Mat3& mat) const
{
	return (std::memcmp(m, &mat, MATRIX3_SIZE) == 0);
}

bool Mat3::operator!=(const Mat3& mat) const
{
	return (std::memcmp(m, &mat, MATRIX3_SIZE) != 0);
}
