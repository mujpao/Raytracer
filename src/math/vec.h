#ifndef VEC_H
#define VEC_H

#include <array>
#include <iosfwd>

class Vec {
public:
    Vec();
    Vec(double x, double y, double z);
    Vec(double x, double y, double z, double w);

    double& operator[](std::size_t idx);
    double operator[](std::size_t idx) const;

    inline double x() const { return m_data[0]; }
    inline double y() const { return m_data[1]; }
    inline double z() const { return m_data[2]; }
    inline double w() const { return m_data[3]; }

    static Vec normalize(const Vec& v);

    Vec& operator+=(const Vec& rhs);
    Vec& operator-=(const Vec& rhs);
    Vec& operator*=(const Vec& rhs);

    Vec& operator*=(double scalar);
    Vec& operator/=(double scalar);

    friend Vec operator+(Vec lhs, const Vec& rhs);
    friend Vec operator-(Vec lhs, const Vec& rhs);

    friend Vec operator-(const Vec& v);

    // Component-wise multiplication
    friend Vec operator*(Vec lhs, const Vec& rhs);

    friend Vec operator*(Vec v, double scalar);
    friend Vec operator*(double scalar, Vec v);
    friend Vec operator/(Vec v, double scalar);

    friend bool operator==(const Vec& lhs, const Vec& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Vec& v);

    static Vec to_point(const Vec& v);
    static Vec to_vec(const Vec& v);
    static double dist(const Vec& a, const Vec& b);

    static double length_squared(const Vec& v);
    static double length(const Vec& v);

private:
    std::array<double, 4> m_data;
};

inline double& Vec::operator[](std::size_t idx) {
    // TODO exceptions, change to std::size_t?
    return m_data[idx];
}

inline double Vec::operator[](std::size_t idx) const { return m_data[idx]; }

#endif
