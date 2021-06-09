#ifndef TRANSFORM_H
#define TRANSFORM_H

class Vec;
class Mat4;

class Transform
{
public:
// TODO does this need to be a class?
	Transform();
	virtual ~Transform();
	static Mat4 rotate(float degrees, const Vec& axis);
	static Mat4 scale(float sx, float sy, float sz);
	static Mat4 translate(float tx, float ty, float tz);
	static float dot(const Vec &a, const Vec &b);
	static Vec cross(const Vec &a, const Vec &b);
	static float det3x3(const Mat4 & m); // det of upper left 3x3
	static float det(const Mat4 & m); // det of 4x4 matrix
	static Mat4 inverse(const Mat4 & m);
	static Mat4 inverse3x3(const Mat4 & m); // applied to upper left 3x3 only
	//static Mat4 transpose(Mat4 & m);
	static Mat4 transpose3x3(const Mat4 & m); // applied to upper left 3x3 only
	static float trace(const Mat4 & m);
	static float trace3x3(const Mat4 & m);
};


#endif