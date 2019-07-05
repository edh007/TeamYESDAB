#include "MathUtil.h"

float DegreeToRadian(float degree)
{
	return degree * 0.01745329251f/*pi / 180.f*/;
}

float RadianToDegree(float radian)
{
	return radian * 57.2957795131f/*180.f / pi*/;
}

Mat4 GetTranslation(float x, float y, float z)
{
	Mat4 rst;
	rst.Translate(x, y, z);
	return rst;
}
Mat4 GetTranslation(const Vec3& v)
{
	Mat4 rst;
	rst.Translate(v.x, v.y, v.z);
	return rst;
}

Mat4 GetRotation(float x, float y, float z, float radian)
{
	Mat4 rst;
	rst.Rotate(x, y, z, radian);
	return rst;
}

Mat4 GetRotation(const Vec3& v, float radian)
{
	Mat4 rst;
	rst.Rotate(v, radian);
	return rst;
}

Mat4 GetRotationX(float rad)
{
	Mat4 rst;
	rst.RotateX(rad);
	return rst;
}

Mat4 GetRotationY(float rad)
{
	Mat4 rst;
	rst.RotateY(rad);
	return rst;
}

Mat4 GetRotationZ(float rad)
{
	Mat4 rst;
	rst.RotateZ(rad);
	return rst;
}

Mat4 GetScaling(float x, float y, float z)
{
	Mat4 rst;
	rst.Scale(x, y, z);
	return rst;
}

Mat4 GetScaling(const Vec3& v)
{
	Mat4 rst;
	rst.Scale(v);
	return rst;
}

Mat4 GetTransform(const Mat4& translation, const Mat4& rotation, const Mat4& scaling)
{
	Mat4 rst;
	rst.Transform(translation, rotation, scaling);
	return rst;
}

Mat4 GetLookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	Vec3 frontDir(target - eye);
	frontDir.Normalize();

	Vec3 rightDir(frontDir.CrossProduct(up));
	rightDir.Normalize();

	Vec3 upDir(rightDir.CrossProduct(frontDir));
	upDir.Normalize();

	Mat4 result;

	// TODO(JIN) : Need to be tested both case
#ifdef COLUMN_BASIS
	result[0].Set(xAxis.x, xAxis.y, xAxis.z, 0.f);
	result[1].Set(yAxis.c, yAxis.y, yAxis.z, 0.f);
	result[2].Set(zAxis.x, zAxis.y, zAxis.z, 0.f);


	result[0].Set(rightDir.x, rightDir.y, rightDir.z, -rightDir.DotProduct(eye));
	result[1].Set(upDir.x, upDir.y, upDir.z, -upDir.DotProduct(eye);
	result[2].Set(-frontDir.x, -frontDir.y, -frontDir.z, frontDir.DotProduct(eye));

#else
	
	result.m[0][0] = rightDir.x;
	result.m[1][0] = rightDir.y;
	result.m[2][0] = rightDir.z;
	result.m[3][0] = -rightDir.DotProduct(eye);

	result.m[0][1] = upDir.x;
	result.m[1][1] = upDir.y;
	result.m[2][1] = upDir.z;
	result.m[3][1] = -upDir.DotProduct(eye);

	result.m[0][2] = -frontDir.x;
	result.m[1][2] = -frontDir.y;
	result.m[2][2] = -frontDir.z;
	result.m[3][2] = frontDir.DotProduct(eye);

#endif
	return result;
}