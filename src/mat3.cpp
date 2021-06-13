#include "mat3.h"

#include "utils.h"

#include <iostream>

Mat3::Mat3(double m[3][3]) {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			m_data[i][j] = m[i][j];
	}
}

Mat3::Mat3(double val) {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			m_data[i][j] = 0.0f;
	}
	m_data[0][0] = val;
	m_data[1][1] = val;
	m_data[2][2] = val;
}

Mat3::Mat3() {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			m_data[i][j] = 0.0f;
	}
}

double& Mat3::operator()(unsigned int i, unsigned int j) {
    return m_data[i][j];
}

double Mat3::operator()(unsigned int i, unsigned int j) const {
    return m_data[i][j];
}

Mat3& Mat3::operator+=(const Mat3& rhs) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m_data[i][j] += rhs.m_data[i][j];
		}
	}

	return *this;
}

Mat3& Mat3::operator-=(const Mat3& rhs) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m_data[i][j] -= rhs.m_data[i][j];
		}
	}

	return *this;
}

Mat3& Mat3::operator*=(double scalar) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m_data[i][j] *= scalar;
		}
	}

	return *this;
}

Mat3 operator+(Mat3 lhs, const Mat3 & rhs) {
	lhs += rhs;
	return lhs;
}

Mat3 operator-(Mat3 lhs, const Mat3 & rhs) {
	lhs -= rhs;
	return lhs;
}

Mat3 operator*(Mat3 m, double scalar) {
	m *= scalar;
	return m;
}

Mat3 operator*(double scalar, Mat3 m) {
	m *= scalar;
	return m;
}

bool operator==(const Mat3& lhs, const Mat3& rhs) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (!Utils::is_equal(lhs(i, j), rhs(i, j)))
				return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Mat3& m) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			os << m(i, j) << " ";
		}
		os << "\n";
	}
	os << "\n";

	return os;
}
