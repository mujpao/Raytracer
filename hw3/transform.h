#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "geometry.h"

class Transform
{
public:
	Transform();
	virtual ~Transform();
	static Mat4 rotate(const float degrees, Vec& axis);
	static Mat4 scale(const float &sx, const float &sy, const float &sz);
	static Mat4 translate(const float &tx, const float &ty, const float &tz);
	static float dot(Vec &a, Vec &b);
	static Vec cross(Vec &a, Vec &b);
	static float det(Mat4 & m); // det of upper left 3x3
	static Mat4 inverse(Mat4 & m); // applied to upper left 3x3 only
	static Mat4 transpose(Mat4 & m); // applied to upper left 3x3 only
};


#endif