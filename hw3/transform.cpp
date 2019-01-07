#include "transform.h"

Mat4 Transform::rotate(const float degrees, Vec& axis)
{
	const float theta = (M_PI * degrees) / 180.0f;
	Mat3 I(1.0);
	Mat3 result;

	Mat3 multiply_by_transpose;
	int i, j;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			multiply_by_transpose.mat[i][j] = axis[i] * axis[j];
		}
	}

	// dual matrix of axis
	Mat3 axis_dual;
	axis_dual.mat[0][0] = 0;
	axis_dual.mat[0][1] = -axis.z;
	axis_dual.mat[0][2] = axis.y;
	axis_dual.mat[1][0] = axis.z;
	axis_dual.mat[1][1] = 0;
	axis_dual.mat[1][2] = -axis.x;
	axis_dual.mat[2][0] = -axis.y;
	axis_dual.mat[2][1] = axis.x;
	axis_dual.mat[2][2] = 0;


	result = I * cos(theta) + multiply_by_transpose *  (1 - cos(theta)) + axis_dual * sin(theta);

	Mat4 res4x4(result);

	return res4x4;
}

Mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	Mat4 result;

	result.mat[0][0] = sx;
	result.mat[1][1] = sy;
	result.mat[2][2] = sz;
	return result;
}

Mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{


	Mat4 result(1.0f);

	result.mat[0][3] = tx;
	result.mat[1][3] = ty;
	result.mat[2][3] = tz;
	return result;
}

float Transform::dot(Vec &a, Vec &b) {
	float result;
	
	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

Vec Transform::cross(Vec &a, Vec &b) {
	Vec result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

float Transform::det3x3(Mat4 & m) {
	float d = 0.0f;
	d += m.mat[0][0] * m.mat[1][1] * m.mat[2][2];
	d += m.mat[0][1] * m.mat[1][2] * m.mat[2][0];
	d += m.mat[0][2] * m.mat[1][0] * m.mat[2][1];

	d -= m.mat[0][2] * m.mat[1][1] * m.mat[2][0];
	d -= m.mat[0][1] * m.mat[1][0] * m.mat[2][2];
	d -= m.mat[0][0] * m.mat[1][2] * m.mat[2][1];

	return d;
}

float Transform::det(Mat4 & m) {
	return m.mat[0][3] * m.mat[1][2] * m.mat[2][1] * m.mat[3][0] - m.mat[0][2] * m.mat[1][3] * m.mat[2][1] * m.mat[3][0] -
		m.mat[0][3] * m.mat[1][1] * m.mat[2][2] * m.mat[3][0] + m.mat[0][1] * m.mat[1][3] * m.mat[2][2] * m.mat[3][0] +
		m.mat[0][2] * m.mat[1][1] * m.mat[2][3] * m.mat[3][0] - m.mat[0][1] * m.mat[1][2] * m.mat[2][3] * m.mat[3][0] -
		m.mat[0][3] * m.mat[1][2] * m.mat[2][0] * m.mat[3][1] + m.mat[0][2] * m.mat[1][3] * m.mat[2][0] * m.mat[3][1] +
		m.mat[0][3] * m.mat[1][0] * m.mat[2][2] * m.mat[3][1] - m.mat[0][0] * m.mat[1][3] * m.mat[2][2] * m.mat[3][1] -
		m.mat[0][2] * m.mat[1][0] * m.mat[2][3] * m.mat[3][1] + m.mat[0][0] * m.mat[1][2] * m.mat[2][3] * m.mat[3][1] +
		m.mat[0][3] * m.mat[1][1] * m.mat[2][0] * m.mat[3][2] - m.mat[0][1] * m.mat[1][3] * m.mat[2][0] * m.mat[3][2] -
		m.mat[0][3] * m.mat[1][0] * m.mat[2][1] * m.mat[3][2] + m.mat[0][0] * m.mat[1][3] * m.mat[2][1] * m.mat[3][2] +
		m.mat[0][1] * m.mat[1][0] * m.mat[2][3] * m.mat[3][2] - m.mat[0][0] * m.mat[1][1] * m.mat[2][3] * m.mat[3][2] -
		m.mat[0][2] * m.mat[1][1] * m.mat[2][0] * m.mat[3][3] + m.mat[0][1] * m.mat[1][2] * m.mat[2][0] * m.mat[3][3] +
		m.mat[0][2] * m.mat[1][0] * m.mat[2][1] * m.mat[3][3] - m.mat[0][0] * m.mat[1][2] * m.mat[2][1] * m.mat[3][3] -
		m.mat[0][1] * m.mat[1][0] * m.mat[2][2] * m.mat[3][3] + m.mat[0][0] * m.mat[1][1] * m.mat[2][2] * m.mat[3][3];
}

Mat4 Transform::inverse(Mat4 & m) {
	Mat4 result = (1.0f / 6.0f) * (pow(trace(m), 3.0f) - 3.0f * trace(m) * trace(m * m) + 2.0f * trace(m * m * m)) * Mat4(1.0f);
	result = result - 0.5f * m * (pow(trace(m), 2.0f) - trace(m * m));
	result = result + m * m * trace(m) - m * m * m;

	return (1.0f / det(m)) * result;
}

Mat4 Transform::inverse3x3(Mat4 & m) {
	float d = det3x3(m);
	
	Mat4 result;

	result.mat[0][0] = m.mat[1][1] * m.mat[2][2] - m.mat[2][1] * m.mat[1][2];
	result.mat[0][1] = m.mat[0][2] * m.mat[2][1] - m.mat[0][1] * m.mat[2][2];
	result.mat[0][2] = m.mat[0][1] * m.mat[1][2] - m.mat[0][2] * m.mat[1][1];
	result.mat[1][0] = m.mat[1][2] * m.mat[2][0] - m.mat[1][0] * m.mat[2][2];
	result.mat[1][1] = m.mat[0][0] * m.mat[2][2] - m.mat[0][2] * m.mat[2][0];
	result.mat[1][2] = m.mat[1][0] * m.mat[0][2] - m.mat[0][0] * m.mat[1][2];
	result.mat[2][0] = m.mat[1][0] * m.mat[2][1] - m.mat[2][0] * m.mat[1][1];
	result.mat[2][1] = m.mat[2][0] * m.mat[0][1] - m.mat[0][0] * m.mat[2][1];
	result.mat[2][2] = m.mat[0][0] * m.mat[1][1] - m.mat[1][0] * m.mat[0][1];

	return (1.0f / d) * result;
}

/*Mat4 Transform::transpose(Mat4 & m) {

}*/

Mat4 Transform::transpose3x3(Mat4 & m) {
	Mat4 m2 = m;

	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			m2.mat[i][j] = m.mat[j][i];
		}
	}

	return m2;
}

float Transform::trace(Mat4 & m) {
	int i;
	float sum = 0.0f;
	for (i = 0; i < 4; ++i) {
		sum += m.mat[i][i];
	}

	return sum;
}

float Transform::trace3x3(Mat4 & m) {
	int i;
	float sum = 0.0f;
	for (i = 0; i < 3; ++i) {
		sum += m.mat[i][i];
	}

	return sum;
}