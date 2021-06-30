#include "math/mat4.h"

#include "math/mat3.h"
#include "math/vec.h"
#include "ray.h"
#include "utils.h"

#include <iostream>

Mat4::Mat4(double m[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            m_data[i][j] = m[i][j];
    }
}

Mat4::Mat4(double val) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            m_data[i][j] = 0.0;
    }
    m_data[0][0] = val;
    m_data[1][1] = val;
    m_data[2][2] = val;
    m_data[3][3] = 1.0;
}

Mat4::Mat4() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            m_data[i][j] = 0.0;
    }
}

Mat4::Mat4(const Mat3& other) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            m_data[i][j] = other(i, j);
    }

    for (int i = 0; i < 3; ++i) {
        m_data[i][3] = 0.0;
        m_data[3][i] = 0.0;
    }

    m_data[3][3] = 1.0;
}

double& Mat4::operator()(unsigned int i, unsigned int j) {
    return m_data[i][j];
}

double Mat4::operator()(unsigned int i, unsigned int j) const {
    return m_data[i][j];
}

Mat4& Mat4::operator+=(const Mat4& rhs) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_data[i][j] += rhs.m_data[i][j];
        }
    }

    return *this;
}

Mat4& Mat4::operator-=(const Mat4& rhs) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_data[i][j] -= rhs.m_data[i][j];
        }
    }

    return *this;
}

Mat4& Mat4::operator*=(const Mat4& rhs) {
    Mat4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m_data[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m_data[i][j] += m_data[i][k] * rhs.m_data[k][j];
            }
        }
    }

    // TODO copy constructor?
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_data[i][j] = result.m_data[i][j];
        }
    }
    return *this;
}

Mat4& Mat4::operator*=(double scalar) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_data[i][j] *= scalar;
        }
    }

    return *this;
}

Mat4 operator+(Mat4 lhs, const Mat4& rhs) {
    lhs += rhs;
    return lhs;
}

Mat4 operator-(Mat4 lhs, const Mat4& rhs) {
    lhs -= rhs;
    return lhs;
}

Mat4 operator*(Mat4 lhs, const Mat4& rhs) {
    lhs *= rhs;
    return lhs;
}

Mat4 operator*(Mat4 m, double scalar) {
    m *= scalar;
    return m;
}

Mat4 operator*(double scalar, Mat4 m) {
    m *= scalar;
    return m;
}

Vec operator*(const Mat4& m, const Vec& v) {
    Vec v2;

    v2[0] = m.m_data[0][0] * v[0] + m.m_data[0][1] * v[1]
        + m.m_data[0][2] * v[2] + m.m_data[0][3] * v[3];
    v2[1] = m.m_data[1][0] * v[0] + m.m_data[1][1] * v[1]
        + m.m_data[1][2] * v[2] + m.m_data[1][3] * v[3];
    v2[2] = m.m_data[2][0] * v[0] + m.m_data[2][1] * v[1]
        + m.m_data[2][2] * v[2] + m.m_data[2][3] * v[3];
    v2[3] = m.m_data[3][0] * v[0] + m.m_data[3][1] * v[1]
        + m.m_data[3][2] * v[2] + m.m_data[3][3] * v[3];

    return v2;
}

bool operator==(const Mat4& lhs, const Mat4& rhs) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!Utils::is_equal(lhs(i, j), rhs(i, j)))
                return false;
        }
    }
    return true;
}

Ray operator*(const Mat4& m, const Ray& r) {
    return Ray(m * r.origin(), m * r.direction());
}

std::ostream& operator<<(std::ostream& os, const Mat4& m) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            os << m(i, j) << " ";
        }
        os << "\n";
    }
    os << "\n";

    return os;
}
