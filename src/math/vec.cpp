#include "math/vec.h"

#include "utils.h"

#include <cmath>
#include <iostream>

Vec::Vec() {
    m_data[0] = m_data[1] = m_data[2] = m_data[3] = 0.0;
}

Vec::Vec(double x, double y, double z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_data[3] = 0.0;
}

Vec::Vec(double x, double y, double z, double w)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_data[3] = w;
}

double& Vec::operator[](int idx) {
    return m_data[idx];
}


double Vec::operator[](int idx) const {
	return m_data[idx];
}

Vec Vec::normalize(const Vec & v) {
	double mag = std::sqrt(std::pow(v.m_data[0], 2) + std::pow(v.m_data[1], 2) + std::pow(v.m_data[2], 2));
	Vec result = v / mag;
	return result;
}

Vec& Vec::operator+=(const Vec& rhs) {
    m_data[0] += rhs.m_data[0];
    m_data[1] += rhs.m_data[1];
    m_data[2] += rhs.m_data[2];
	return *this;
}

Vec& Vec::operator-=(const Vec& rhs) {
	m_data[0] -= rhs.m_data[0];
    m_data[1] -= rhs.m_data[1];
    m_data[2] -= rhs.m_data[2];
	return *this;
}

Vec& Vec::operator*=(const Vec& rhs) {
	m_data[0] *= rhs.m_data[0];
    m_data[1] *= rhs.m_data[1];
    m_data[2] *= rhs.m_data[2];
	return *this;
}

Vec& Vec::operator*=(double scalar) {
	m_data[0] *= scalar;
	m_data[1] *= scalar;
	m_data[2] *= scalar;
	return *this;
}

Vec& Vec::operator/=(double scalar) {
	m_data[0] /= scalar;
	m_data[1] /= scalar;
	m_data[2] /= scalar;
	return *this;
}

Vec operator+(Vec lhs, const Vec & rhs) {
	lhs += rhs;
	return lhs;
}

Vec operator-(Vec lhs, const Vec & rhs) {
	lhs -= rhs;
	return lhs;
}

Vec operator*(Vec lhs, const Vec & rhs) {
	lhs *= rhs;
	return lhs;
}

Vec operator*(Vec v, double scalar) {
	v *= scalar;
	return v;
}

Vec operator*(double scalar, Vec v) {
	v *= scalar;
	return v;
}

Vec operator/(Vec v, double scalar) {
	v /= scalar;
	return v;
}

bool operator==(const Vec& lhs, const Vec& rhs) {
	return Utils::is_equal(lhs[0], rhs[0]) && 
    Utils::is_equal(lhs[1], rhs[1]) &&
    Utils::is_equal(lhs[2], rhs[2]) && 
    Utils::is_equal(lhs[3], rhs[3]);
}

std::ostream& operator<<(std::ostream& os, const Vec& v) {
	os << "<" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ">";
	return os;
}

Vec Vec::to_point(const Vec& v) {
	return Vec(v.x(), v.y(), v.z(), 1.0);
}

Vec Vec::to_vec(const Vec& v) {
	return Vec(v.x(), v.y(), v.z(), 0.0);
}

double Vec::dist(const Vec& a, const Vec& b) {
	return length(a - b);
	// return std::sqrt(std::pow(a.x() - b.x(), 2) + std::pow(a.y() - b.y(), 2) + std::pow(a.z() - b.z(), 2));
}

double Vec::length_squared(const Vec& v) {
	return std::pow(v.x(), 2) + std::pow(v.y(), 2) + std::pow(v.z(), 2);
}

double Vec::length(const Vec& v) {
	return std::sqrt(length_squared(v));
}
