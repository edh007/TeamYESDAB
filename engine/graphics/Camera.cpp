#include "Camera.h"

namespace gi
{
  Mat4 Camera::LookAt(Vec3 _eye, Vec3 _center, Vec3 _up)
  {
    Vec3 temp = (_center - _eye);

	Vec3 f = temp.Normalize();
	Vec3 cal = f.CrossProduct(_up);
	Vec3 s = cal * 1 / (sqrt(cal.DotProduct(cal)));

    Vec3 u = s.CrossProduct(f);

    Mat4 Result;
    Result.SetIdentity();

    Result.m[0][0] = s.x;
    Result.m[1][0] = s.y;
    Result.m[2][0] = s.z;

    Result.m[0][1] = u.x;
    Result.m[1][1] = u.y;
    Result.m[2][1] = u.z;

    Result.m[0][2] = -f.x;
    Result.m[1][2] = -f.y;
    Result.m[2][2] = -f.z;

    Result.m[3][0] = -(s.DotProduct(_eye));
    Result.m[3][1] = -(u.DotProduct(_eye));
    Result.m[3][2] = f.DotProduct(_eye);

    return Result;
  }
}