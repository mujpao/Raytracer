#include "math/transform.h"

#include "math/mat3.h"
#include "math/mat4.h"
#include "math/vec.h"
#include "utils.h"

#include <cmath>

namespace Transform {
    double dot(const Vec& a, const Vec& b) {
        double result;
        result = a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
        return result;
    }

    Vec cross(const Vec& a, const Vec& b) {
        return Vec(a.y() * b.z() - a.z() * b.y(), a.z() * b.x() - a.x() * b.z(),
            a.x() * b.y() - a.y() * b.x());
    }

    Vec reflect(const Vec& v, const Vec& n) { return v - 2 * dot(v, n) * n; }

    Mat4 rotate(double degrees, const Vec& axis) {
        Vec axis_normalized = Vec::normalize(axis);
        const double theta = Utils::deg2rad(degrees);
        Mat3 I(1.0);
        Mat3 result;

        Mat3 multiply_by_transpose;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                multiply_by_transpose(i, j)
                    = axis_normalized[i] * axis_normalized[j];
            }
        }

        // dual matrix of normalized axis
        Mat3 axis_dual;
        axis_dual(0, 0) = 0;
        axis_dual(0, 1) = -axis_normalized.z();
        axis_dual(0, 2) = axis_normalized.y();
        axis_dual(1, 0) = axis_normalized.z();
        axis_dual(1, 1) = 0;
        axis_dual(1, 2) = -axis_normalized.x();
        axis_dual(2, 0) = -axis_normalized.y();
        axis_dual(2, 1) = axis_normalized.x();
        axis_dual(2, 2) = 0;

        result = I * std::cos(theta)
            + multiply_by_transpose * (1 - std::cos(theta))
            + axis_dual * std::sin(theta);

        Mat4 res4x4(result);

        return res4x4;
    }

    Mat4 scale(double sx, double sy, double sz) {
        Mat4 result;
        result(0, 0) = sx;
        result(1, 1) = sy;
        result(2, 2) = sz;
        result(3, 3) = 1.0;
        return result;
    }

    Mat4 translate(double tx, double ty, double tz) {
        Mat4 result(1.0);
        result(0, 3) = tx;
        result(1, 3) = ty;
        result(2, 3) = tz;
        result(3, 3) = 1.0;
        return result;
    }

    double det3x3(const Mat4& m) {
        double d = 0.0;
        d += m(0, 0) * m(1, 1) * m(2, 2);
        d += m(0, 1) * m(1, 2) * m(2, 0);
        d += m(0, 2) * m(1, 0) * m(2, 1);

        d -= m(0, 2) * m(1, 1) * m(2, 0);
        d -= m(0, 1) * m(1, 0) * m(2, 2);
        d -= m(0, 0) * m(1, 2) * m(2, 1);

        return d;
    }

    double det(const Mat4& m) {
        return m(0, 3) * m(1, 2) * m(2, 1) * m(3, 0)
            - m(0, 2) * m(1, 3) * m(2, 1) * m(3, 0)
            - m(0, 3) * m(1, 1) * m(2, 2) * m(3, 0)
            + m(0, 1) * m(1, 3) * m(2, 2) * m(3, 0)
            + m(0, 2) * m(1, 1) * m(2, 3) * m(3, 0)
            - m(0, 1) * m(1, 2) * m(2, 3) * m(3, 0)
            - m(0, 3) * m(1, 2) * m(2, 0) * m(3, 1)
            + m(0, 2) * m(1, 3) * m(2, 0) * m(3, 1)
            + m(0, 3) * m(1, 0) * m(2, 2) * m(3, 1)
            - m(0, 0) * m(1, 3) * m(2, 2) * m(3, 1)
            - m(0, 2) * m(1, 0) * m(2, 3) * m(3, 1)
            + m(0, 0) * m(1, 2) * m(2, 3) * m(3, 1)
            + m(0, 3) * m(1, 1) * m(2, 0) * m(3, 2)
            - m(0, 1) * m(1, 3) * m(2, 0) * m(3, 2)
            - m(0, 3) * m(1, 0) * m(2, 1) * m(3, 2)
            + m(0, 0) * m(1, 3) * m(2, 1) * m(3, 2)
            + m(0, 1) * m(1, 0) * m(2, 3) * m(3, 2)
            - m(0, 0) * m(1, 1) * m(2, 3) * m(3, 2)
            - m(0, 2) * m(1, 1) * m(2, 0) * m(3, 3)
            + m(0, 1) * m(1, 2) * m(2, 0) * m(3, 3)
            + m(0, 2) * m(1, 0) * m(2, 1) * m(3, 3)
            - m(0, 0) * m(1, 2) * m(2, 1) * m(3, 3)
            - m(0, 1) * m(1, 0) * m(2, 2) * m(3, 3)
            + m(0, 0) * m(1, 1) * m(2, 2) * m(3, 3);
    }

    Mat4 inverse(const Mat4& m) {
        Mat4 result = (1.0 / 6.0)
            * (std::pow(trace(m), 3.0) - 3.0 * trace(m) * trace(m * m)
                + 2.0 * trace(m * m * m))
            * Mat4(1.0);
        result = result - 0.5 * m * (std::pow(trace(m), 2.0) - trace(m * m));
        result = result + m * m * trace(m) - m * m * m;

        return (1.0 / det(m)) * result;
    }

    Mat4 inverse3x3(const Mat4& m) {
        double d = det3x3(m);
        Mat4 result;

        result(0, 0) = m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2);
        result(0, 1) = m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2);
        result(0, 2) = m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1);
        result(1, 0) = m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2);
        result(1, 1) = m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0);
        result(1, 2) = m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2);
        result(2, 0) = m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1);
        result(2, 1) = m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1);
        result(2, 2) = m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1);

        return (1.0 / d) * result;
    }

    Mat4 transpose3x3(const Mat4& m) {
        Mat4 m2 = m;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                m2(i, j) = m(j, i);
            }
        }

        return m2;
    }

    double trace(const Mat4& m) {
        double sum = 0.0;
        for (int i = 0; i < 4; ++i) {
            sum += m(i, i);
        }

        return sum;
    }

    double trace3x3(const Mat4& m) {
        double sum = 0.0;
        for (int i = 0; i < 3; ++i) {
            sum += m(i, i);
        }

        return sum;
    }

} // namespace Transform
