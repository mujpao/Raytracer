#ifndef TRANSFORM_H
#define TRANSFORM_H

class Vec;
class Mat4;

class Transform {
public:
  // TODO does this need to be a class?
  static Mat4 rotate(double degrees, const Vec &axis);
  static Mat4 scale(double sx, double sy, double sz);
  static Mat4 translate(double tx, double ty, double tz);
  static double dot(const Vec &a, const Vec &b);
  static Vec cross(const Vec &a, const Vec &b);
  static double det3x3(const Mat4 &m); // det of upper left 3x3
  static double det(const Mat4 &m);    // det of 4x4 matrix
  static Mat4 inverse(const Mat4 &m);
  static Mat4 inverse3x3(const Mat4 &m); // applied to upper left 3x3 only
  // static Mat4 transpose(Mat4 & m);
  static Mat4 transpose3x3(const Mat4 &m); // applied to upper left 3x3 only
  static double trace(const Mat4 &m);
  static double trace3x3(const Mat4 &m);
};

#endif