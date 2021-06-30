#ifndef MAT3_H
#define MAT3_H

#include <iosfwd>

class Mat3 {
public:
    Mat3(double m[3][3]);
    Mat3(double val); // sets diagonal to value
    Mat3(); // initializes all elements to 0
    // todo should it initialize to identity matrix?

    // TODO type of idx?
    double& operator()(unsigned int i, unsigned int j);
    double operator()(unsigned int i, unsigned int j) const;

    Mat3& operator+=(const Mat3& rhs);
    Mat3& operator-=(const Mat3& rhs);

    Mat3& operator*=(double scalar);

    friend Mat3 operator+(Mat3 lhs, const Mat3& rhs);
    friend Mat3 operator-(Mat3 lhs, const Mat3& rhs);

    friend Mat3 operator*(Mat3 m, double scalar);
    friend Mat3 operator*(double scalar, Mat3 m);

    friend bool operator==(const Mat3& lhs, const Mat3& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Mat3& m);

private:
    double m_data[3][3];
};

#endif
