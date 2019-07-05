#include "Matrix4.h"

// TODO(JIN) : 
#include <cstring>
#include <iostream>
#include "MathUtil.h"

const Mat4 Mat4::ZERO(
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f);

const Mat4 Mat4::IDENTITY(
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f);

Mat4::Mat4()
{
	*this = IDENTITY;
}

Mat4::Mat4(float p00, float p01, float p02, float p03, float p10, float p11, float p12, float p13, float p20, float p21,
	float p22, float p23, float p30, float p31, float p32, float p33)
{
	Set(p00, p01, p02, p03,
		p10, p11, p12, p13,
		p20, p21, p22, p23,
		p30, p31, p32, p33);
}

Mat4::Mat4(const float* array)
{
	Set(array);
}

Mat4::Mat4(const Mat4& copy)
{
	Set(copy);
}

void Mat4::Set(float p00, float p01, float p02, float p03, 
	float p10, float p11, float p12, float p13, 
	float p20, float p21, float p22, float p23, 
	float p30, float p31, float p32, float p33)
{
	// TODO(JIN) : Test
	element[0] = p00; element[1] = p01; element[2] = p02; element[3] = p03;
	element[4] = p10; element[5] = p11; element[6] = p12; element[7] = p13;
	element[8] = p20; element[9] = p21; element[10] = p22; element[11] = p23;
	element[12] = p30; element[13] = p31; element[14] = p32; element[15] = p33;
}

// TODO(JIN) : 
void Mat4::Set(const float* array)
{
	std::memcpy(element, array, MATRIX4_SIZE);
}

void Mat4::Set(const Mat4& copy)
{
	std::memcpy(element, copy.element, MATRIX4_SIZE);
}

void Mat4::SetZero()
{
	std::memset(element, 0, MATRIX4_SIZE);
}

void Mat4::SetIdentity()
{
	*this = IDENTITY;
}

void Mat4::Transpose()
{
	std::swap(m01, m10);
	std::swap(m02, m20);
	std::swap(m03, m30);

	std::swap(m12, m21);
	std::swap(m13, m31);
	std::swap(m23, m32);
}

Mat4 Mat4::GetTransposed() const
{
	Mat4 rst(*this);
	rst.Transpose();

	return rst;
}

void Mat4::Inverse()
{
	// https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
	// https://youtu.be/nNOz6Ez8Fn4

	/*  0   1   2   3
		4   5   6   7
		8   9   10  11
		12  13  14  15 */

	float cf[16];

	// Calculate the Matrix of Minors and change to the cofactors
	cf[0] = GetMinorMat(5, 6, 7, 9, 10, 11, 13, 14, 15);
	cf[1] = -GetMinorMat(4, 6, 7, 8, 10, 11, 12, 14, 15);
	cf[2] = GetMinorMat(4, 5, 7, 8, 9, 11, 12, 13, 15);
	cf[3] = -GetMinorMat(4, 5, 6, 8, 9, 10, 12, 13, 14);

	// Get Determinant
	float det = element[0] * cf[0] + element[4] * cf[4] + element[8] * cf[8] + element[12] * cf[12];

	//DEBUG_ASSERT(std::fabs(det) == 0.f, "determinant of inverse is zero.\n");

	// Calculate the rest of the Matrix of Minors and change to the cofactors
	cf[4] = -GetMinorMat(1, 2, 3, 9, 10, 11, 13, 14, 15);
	cf[5] = GetMinorMat(0, 2, 3, 8, 10, 11, 12, 14, 15);
	cf[6] = -GetMinorMat(0, 1, 3, 8, 9, 11, 12, 13, 15);
	cf[7] = GetMinorMat(0, 1, 2, 8, 9, 10, 12, 13, 14);

	cf[8] = GetMinorMat(1, 2, 3, 5, 6, 7, 13, 14, 15);
	cf[9] = -GetMinorMat(0, 2, 3, 4, 6, 7, 12, 14, 15);
	cf[10] = GetMinorMat(0, 1, 3, 4, 5, 7, 12, 13, 15);
	cf[11] = -GetMinorMat(0, 1, 2, 4, 5, 6, 12, 13, 14);

	cf[12] = -GetMinorMat(1, 2, 3, 5, 6, 7, 9, 10, 11);
	cf[13] = GetMinorMat(0, 2, 3, 4, 6, 7, 8, 10, 11);
	cf[14] = -GetMinorMat(0, 1, 3, 4, 5, 7, 8, 9, 11);
	cf[15] = GetMinorMat(0, 1, 2, 4, 5, 6, 8, 9, 10);

	Set(cf);

	// Transpose (Adjugate ,which is also called Adjoint)
	//this->Transpose();


	// Multiply by 1 / determinant
	*this /= det;
}

Mat4 Mat4::GetInverseMatrix() const
{
	Mat4 rst(*this);
	rst.Inverse();
	return rst;
}

void Mat4::Scale(float x, float y, float z)
{
	SetIdentity();

	m00 = x;
	m11 = y;
	m22 = z;
}

void Mat4::Scale(const Vec3& rhs)
{
	SetIdentity();

	m00 = rhs.x;
	m11 = rhs.y;
	m22 = rhs.z;
}

void Mat4::Rotate(float x, float y, float z, float radian)
{
	SetIdentity();

	float c = std::cos(radian);
	float s = std::sin(radian);
	float t = 1 - c;

#ifdef  COLUMN_BASIS
	(*this)[0].Set(t*x*x + c, t*x*y + s*z, t*x*z - s*y, 0.f);
	(*this)[1].Set(t*x*y - s*z, t*y*y + c, t*y*z + s*x, 0.f);
	(*this)[2].Set(t*x*z + s*y, t*y*z - s*x, t*z*z + c, 0.f);

#else
	(*this)[0].Set(t*x*x + c, t*x*y - s*z, t*x*z + s*y, 0.f);
	(*this)[1].Set(t*x*y + s*z, t*y*y + c, t*y*z - s*x, 0.f);
	(*this)[2].Set(t*x*z - s*y, t*y*z + s*x, t*z*z + c, 0.f);
#endif
}

void Mat4::Rotate(const Vec3& rhs, float radian)
{
	Rotate(rhs.x, rhs.y, rhs.z, radian);
}

void Mat4::Rotate(const Vec3& rhs)
{
    SetIdentity();
    m00 = cos(rhs.y) * cos(rhs.z);
    m01 = sin(rhs.x) * sin(rhs.y) * cos(rhs.z) - cos(rhs.x) * sin(rhs.z);
    m02 = cos(rhs.x) * sin(rhs.y) * cos(rhs.z) + sin(rhs.x) * sin(rhs.z);
    m10 = cos(rhs.y) * sin(rhs.z);
    m11 = sin(rhs.x) * sin(rhs.y) * sin(rhs.z) + cos(rhs.x) * cos(rhs.z);
    m12 = cos(rhs.x) * sin(rhs.y) * sin(rhs.z) - sin(rhs.x) * cos(rhs.z);
    m20 = -sin(rhs.y);
    m21 = sin(rhs.x) * cos(rhs.y);
    m22 = cos(rhs.x) * cos(rhs.y);
    Transpose();
}

void Mat4::RotateX(float radian)
{
	SetIdentity();

	float c = std::cos(radian);
	float s = std::sin(radian);

	m11 = c;
	m12 = -s;
	m21 = s;
	m22 = c;	
}

void Mat4::RotateY(float radian)
{
	SetIdentity();

	float c = std::cos(radian);
	float s = std::sin(radian);

	m00 = c;
	m02 = s;
	m20 = -s;
	m22 = c;
}

void Mat4::RotateZ(float radian)
{
	SetIdentity();

	float c = std::cos(radian);
	float s = std::sin(radian);

	m00 = c;
	m01 = -s;
	m10 = s;
	m11 = s;

}

void Mat4::Translate(float x, float y, float z)
{
	SetIdentity();

	m03 = x;
	m13 = y;
	m23 = z;
}

void Mat4::Transform(const Mat4& translation, const Mat4& rotation, const Mat4& scaling)
{
	SetIdentity();

#ifdef COLUMN_BASIS
	*this = translation * rotation * scaling;
#else
    *this = scaling * rotation * translation;
    //Mat4 t;
    //t.Translate(0, 0, 0);
    //*this *= t;
    //*this *= scaling;
    //*this *= rotation;
    //*this *= translation;
#endif
}

void Mat4::Translate(const Vec3& rhs)
{
	Translate(rhs.x, rhs.y, rhs.z);
}

//////////////////////////////////////////////////////////////////////////
// Operator
//////////////////////////////////////////////////////////////////////////
Mat4 Mat4::operator+(const Mat4& rhs) const
{
	return Mat4(*this) += rhs;
}

Mat4& Mat4::operator+=(const Mat4& rhs)
{
	for(unsigned i = 0; i < MATRIX4_INDEX_MAX; ++i)
		element[i] += rhs.element[i];

	return *this;
}

Mat4 Mat4::operator-(const Mat4& rhs) const
{
	return Mat4(*this) -= rhs;
}

Mat4& Mat4::operator-=(const Mat4& rhs)
{
	for (unsigned i = 0; i < MATRIX4_INDEX_MAX; ++i)
		element[i] -= rhs.element[i];

	return *this;
}

Mat4 Mat4::operator*(const Mat4& rhs) const
{
	//return Mat4(*this) *= rhs;
    return Concat(rhs);
}

Mat4 Mat4::Concat(Mat4 rhs) const
{
    Mat4 ret;

    ret.SetZero();

    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            for (int i = 0; i < 4; ++i)
            {
                ret.m[r][c] += m[r][i] * rhs.m[i][c];
            }
        }
    }

    return ret;
}

Mat4& Mat4::operator*=(const Mat4& rhs)
{
	float array[16] = {0.f};

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			for (int i = 0; i < 4; ++i)
			{
				array[r*4 + c] += m[r][i] * rhs.m[i][c];
			}
		}
	}

	memcpy(element, array, MATRIX4_SIZE);

	return *this;
}

Mat4 Mat4::operator*(float s) const
{
	return Mat4(*this) *= s;
}

Mat4& Mat4::operator*=(float s)
{
	for (unsigned i = 0; i < MATRIX4_INDEX_MAX; ++i)
		element[i] *= s;

	return *this;
}

Mat4 Mat4::operator/(float s) const
{
	return Mat4(*this) /= s;
}

Mat4& Mat4::operator/=(float s)
{
	// TODO(JIN) : DEBUG_ASSERT(std::fabs(s) == 0.f, "cannot be divided by zero\n");
	s = 1.f / s;

	for (unsigned i = 0; i < MATRIX4_INDEX_MAX; ++i)
		element[i] *= s;

	return *this;
}

Vec4& Mat4::operator[](unsigned index)
{
	return ((Vec4*)this)[index];
}

const Vec4& Mat4::operator[](unsigned index) const
{
	return ((Vec4*)this)[index];
}

bool Mat4::operator==(const Mat4& mat) const
{
	return (std::memcmp(m, &mat, MATRIX4_SIZE) == 0);
}

bool Mat4::operator!=(const Mat4& mat) const
{
	return (std::memcmp(m, &mat, MATRIX4_SIZE) != 0);
}


float Mat4::GetMinorMat(unsigned i0, unsigned i1, unsigned i2, 
	unsigned i3, unsigned i4, unsigned i5, 
	unsigned i6, unsigned i7, unsigned i8)
{

	/*
	0   1   2
	3   4   5
	6   7   8

	GetMinorMat(5, 6, 7, 9, 10, 11, 13, 14, 15);

	5   6   7
	9   10  11
	13  14  15

	5 * (10 * 15 - 11* 14) - 6 * (9 * 15 - 11 * 13) + 7 * ( 9 * 14 - 10 * 13)

	GetMinorMat(1, 2, 3, 9, 10, 11, 13, 14, 15);

	1   2   3
	9   10  11
	13  14  15

	1 * (10 * 15 - 11 * 14) - 2 * ( 9 * 15 - 11 * 13) + 3 * (9 * 14 - 10 * 13)
	*/

	return element[i0] * (element[i4] * element[i8] - element[i5] * element[i7])
		- element[i1] * (element[i3] * element[i8] - element[i5] * element[i6])
		+ element[i2] * (element[i3] * element[i7] - element[i4] * element[i6]);
}

Mat3 Mat4::ToMatrix3()
{
    Mat3 mat3;

    mat3.m00 = this->m00;
    mat3.m01 = this->m01;
    mat3.m02 = this->m02;

    mat3.m10 = this->m10;
    mat3.m11 = this->m11;
    mat3.m12 = this->m12;

    mat3.m20 = this->m20;
    mat3.m21 = this->m21;
    mat3.m22 = this->m22;

    return mat3;
}