#include <cassert>
#include "tests.h"

void test_point() {
	Point p1(1.0f, 2.0f, 3.0f);
	assert(p1.x == 1.0f);
	assert(p1.y == 2.0f);
	assert(p1.z == 3.0f);
}

void test_vec() {
	Vec v1(1.0f, 2.0f, 3.0f);
	assert(v1.x == 1.0f);
	assert(v1.y == 2.0f);
	assert(v1.z == 3.0f);
	assert(v1[0] == 1.0f);
	assert(v1[1] == 2.0f);
	assert(v1[2] == 3.0f);

	// check indexing
	v1[0] = 5.0f;
	v1[1] = 10.0f;
	v1[2] = 20.0f;
	assert(v1[0] == 5.0f);
	assert(v1[1] == 10.0f);
	assert(v1[2] == 20.0f);
	assert(v1.x == 5.0f);
	assert(v1.y == 10.0f);
	assert(v1.z == 20.0f);

	Vec v2(3.0f, 4.0f, 5.0f);
	Vec v3(6.0f, 7.0f, 8.0f);

	Vec v4 = v2 + v3;
	assert(v4.x == 9.0f);
	assert(v4.y == 11.0f);
	assert(v4.z == 13.0f);
	// make sure v2 and v3 haven't been changed
	assert(v2.x == 3.0f);
	assert(v2.y == 4.0f);
	assert(v2.z == 5.0f);
	assert(v3.x == 6.0f);
	assert(v3.y == 7.0f);
	assert(v3.z == 8.0f);

	v4 = v2 - v3;
	assert(v4.x == -3.0f);
	assert(v4.y == -3.0f);
	assert(v4.z == -3.0f);

	// test multiplying by scalar
	Vec v5(1.0f, 2.0f, 3.0f);
	v5 = v5 * 3.0f;
	assert(v5.x == 3.0f);
	assert(v5.y == 6.0f);
	assert(v5.z == 9.0f);

	Vec v6(1.0f, 2.0f, 3.0f);
	v6 = 3.0f * v6;
	assert(v6.x == 3.0f);
	assert(v6.y == 6.0f);
	assert(v6.z == 9.0f);

	// divide by scalar

	Vec v7(10.0f, 20.0f, 30.0f);
	v7 = v7 / 2;
	assert(v7.x == 5.0f);
	assert(v7.y == 10.0f);
	assert(v7.z == 15.0f);

	// normalize
	Vec v8(1.0f, 0.0f, 0.0f);
	v8 = Vec::normalize(v8);
	assert(v8.x == 1.0f);
	assert(v8.y == 0.0f);
	assert(v8.z == 0.0f);

	Vec v9(1.0f, -1.0f, 1.0f);
	v9 = Vec::normalize(v9);
	assert(v9.x == 1.0f / sqrt(3.0f));
	assert(v9.y == -1.0f / sqrt(3.0f));
	assert(v9.z == 1.0f / sqrt(3.0f));
}

void test_mat3() {
	float m[3][3] = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	Mat3 m1(m);
	assert(m1.mat[0][0] == 1.0f);
	assert(m1.mat[0][1] == 2.0f);
	assert(m1.mat[0][2] == 3.0f);
	assert(m1.mat[1][0] == 4.0f);
	assert(m1.mat[1][1] == 5.0f);
	assert(m1.mat[1][2] == 6.0f);
	assert(m1.mat[2][0] == 7.0f);
	assert(m1.mat[2][1] == 8.0f);
	assert(m1.mat[2][2] == 9.0f);

	Mat3 m2;
	assert(m2.mat[0][0] == 0.0f);
	assert(m2.mat[0][1] == 0.0f);
	assert(m2.mat[0][2] == 0.0f);
	assert(m2.mat[1][0] == 0.0f);
	assert(m2.mat[1][1] == 0.0f);
	assert(m2.mat[1][2] == 0.0f);
	assert(m2.mat[2][0] == 0.0f);
	assert(m2.mat[2][1] == 0.0f);
	assert(m2.mat[2][2] == 0.0f);

	Mat3 m3(1.0f);
	assert(m3.mat[0][0] == 1.0f);
	assert(m3.mat[0][1] == 0.0f);
	assert(m3.mat[0][2] == 0.0f);
	assert(m3.mat[1][0] == 0.0f);
	assert(m3.mat[1][1] == 1.0f);
	assert(m3.mat[1][2] == 0.0f);
	assert(m3.mat[2][0] == 0.0f);
	assert(m3.mat[2][1] == 0.0f);
	assert(m3.mat[2][2] == 1.0f);

	Mat3 m4 = m1 + m3;
	assert(m4.mat[0][0] == 2.0f);
	assert(m4.mat[0][1] == 2.0f);
	assert(m4.mat[0][2] == 3.0f);
	assert(m4.mat[1][0] == 4.0f);
	assert(m4.mat[1][1] == 6.0f);
	assert(m4.mat[1][2] == 6.0f);
	assert(m4.mat[2][0] == 7.0f);
	assert(m4.mat[2][1] == 8.0f);
	assert(m4.mat[2][2] == 10.0f);

	Mat3 m5 = m1 - m3;
	assert(m5.mat[0][0] == 0.0f);
	assert(m5.mat[0][1] == 2.0f);
	assert(m5.mat[0][2] == 3.0f);
	assert(m5.mat[1][0] == 4.0f);
	assert(m5.mat[1][1] == 4.0f);
	assert(m5.mat[1][2] == 6.0f);
	assert(m5.mat[2][0] == 7.0f);
	assert(m5.mat[2][1] == 8.0f);
	assert(m5.mat[2][2] == 8.0f);

	Mat3 m6 = m1 * 3.0f;
	assert(m6.mat[0][0] == 3.0f);
	assert(m6.mat[0][1] == 6.0f);
	assert(m6.mat[0][2] == 9.0f);
	assert(m6.mat[1][0] == 12.0f);
	assert(m6.mat[1][1] == 15.0f);
	assert(m6.mat[1][2] == 18.0f);
	assert(m6.mat[2][0] == 21.0f);
	assert(m6.mat[2][1] == 24.0f);
	assert(m6.mat[2][2] == 27.0f);

	Mat3 m7 = 3.0f * m1;
	assert(m7.mat[0][0] == 3.0f);
	assert(m7.mat[0][1] == 6.0f);
	assert(m7.mat[0][2] == 9.0f);
	assert(m7.mat[1][0] == 12.0f);
	assert(m7.mat[1][1] == 15.0f);
	assert(m7.mat[1][2] == 18.0f);
	assert(m7.mat[2][0] == 21.0f);
	assert(m7.mat[2][1] == 24.0f);
	assert(m7.mat[2][2] == 27.0f);
}

void test_mat4() {
	float m[4][4] = {
		1.0f, 2.0f, 3.0f, 0.0f,
		4.0f, 5.0f, 6.0f, 0.0f,
		7.0f, 8.0f, 9.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	Mat4 m1(m);
	assert(m1.mat[0][0] == 1.0f);
	assert(m1.mat[0][1] == 2.0f);
	assert(m1.mat[0][2] == 3.0f);
	assert(m1.mat[1][0] == 4.0f);
	assert(m1.mat[1][1] == 5.0f);
	assert(m1.mat[1][2] == 6.0f);
	assert(m1.mat[2][0] == 7.0f);
	assert(m1.mat[2][1] == 8.0f);
	assert(m1.mat[2][2] == 9.0f);
	assert(m1.mat[3][3] == 1.0f);


	Mat4 m2;
	assert(m2.mat[0][0] == 0.0f);
	assert(m2.mat[0][1] == 0.0f);
	assert(m2.mat[0][2] == 0.0f);
	assert(m2.mat[1][0] == 0.0f);
	assert(m2.mat[1][1] == 0.0f);
	assert(m2.mat[1][2] == 0.0f);
	assert(m2.mat[2][0] == 0.0f);
	assert(m2.mat[2][1] == 0.0f);
	assert(m2.mat[2][2] == 0.0f);
	assert(m1.mat[3][3] == 1.0f);


	Mat4 m3(1.0f);
	assert(m3.mat[0][0] == 1.0f);
	assert(m3.mat[0][1] == 0.0f);
	assert(m3.mat[0][2] == 0.0f);
	assert(m3.mat[1][0] == 0.0f);
	assert(m3.mat[1][1] == 1.0f);
	assert(m3.mat[1][2] == 0.0f);
	assert(m3.mat[2][0] == 0.0f);
	assert(m3.mat[2][1] == 0.0f);
	assert(m3.mat[2][2] == 1.0f);
	assert(m1.mat[3][3] == 1.0f);



	float m3x3[3][3] = {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};
	Mat3 m4(m3x3);
	Mat4 m5(m4);

	assert(m5.mat[0][0] == 1.0f);
	assert(m5.mat[0][1] == 2.0f);
	assert(m5.mat[0][2] == 3.0f);
	assert(m5.mat[1][0] == 4.0f);
	assert(m5.mat[1][1] == 5.0f);
	assert(m5.mat[1][2] == 6.0f);
	assert(m5.mat[2][0] == 7.0f);
	assert(m5.mat[2][1] == 8.0f);
	assert(m5.mat[2][2] == 9.0f);
	assert(m5.mat[3][3] == 1.0f);
}


void run_tests() {
	test_point();
	test_vec();
	test_mat3();
	test_mat4();
}