#ifndef MAT4_H
#define MAT4_H

#include <iosfwd>

class Vec;
class Mat3;
class Ray;

class Mat4 {
public:
	Mat4(double m[4][4]);
	Mat4(double val); // sets diagonal to value, sets m[3][3] to 1.0
	Mat4(); // initializes all elements to 0
	Mat4(const Mat3 &other); // initializes with 3x3 matrix, sets fourth row and column to 0 0 0 1

	double& operator()(unsigned int i, unsigned int j);
	double operator()(unsigned int i, unsigned int j) const;

	Mat4& operator+=(const Mat4& rhs);
	Mat4& operator-=(const Mat4& rhs);
	Mat4& operator*=(const Mat4& rhs);

	Mat4& operator*=(double scalar);

	friend Mat4 operator+(Mat4 lhs, const Mat4 & rhs);
	friend Mat4 operator-(Mat4 lhs, const Mat4 & rhs);
	friend Mat4 operator*(Mat4 lhs, const Mat4 & rhs);

	friend Mat4 operator*(Mat4 m, double scalar);
	friend Mat4 operator*(double scalar, Mat4 m);

	friend bool operator==(const Mat4& lhs, const Mat4& rhs);

	friend Vec operator*(const Mat4 & m, const Vec & v);
	friend Ray operator*(const Mat4 & m, const Ray & r);

	friend std::ostream& operator<<(std::ostream& os, const Mat4& m);

private:
	double m_data[4][4];
};

#endif
