#ifndef TRANSFORM_H
#define TRANSFORM_H

class Vec;
class Mat4;

namespace Transform {
    double dot(const Vec& a, const Vec& b);
    Vec cross(const Vec& a, const Vec& b);

    Vec reflect(const Vec& v, const Vec& n);
    Vec refract(const Vec& incident, const Vec& n1, double eta1, double eta2);

    Mat4 rotate(double degrees, const Vec& axis);
    Mat4 scale(double sx, double sy, double sz);
    Mat4 translate(double tx, double ty, double tz);

    double det3x3(const Mat4& m); // det of upper left 3x3
    double det(const Mat4& m); // det of 4x4 matrix
    Mat4 inverse(const Mat4& m);
    Mat4 inverse3x3(const Mat4& m); // applied to upper left 3x3 only
    Mat4 transpose3x3(const Mat4& m); // applied to upper left 3x3 only
    double trace(const Mat4& m);
    double trace3x3(const Mat4& m);
} // namespace Transform

#endif