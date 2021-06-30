#include "ray.h"

#include "camera.h"
#include "utils.h"

#include <iostream>

Ray::Ray(const Vec& origin, const Vec& direction)
    : m_origin(Vec::to_point(origin)), m_direction(direction) {}

Vec Ray::evaluate(double t) const {
    Vec result = Vec::to_point(m_origin + m_direction * t);
    return result;
}

std::ostream& operator<<(std::ostream& os, const Ray& r) {
    os << r.m_origin << " + " << r.m_direction << " * t";
    return os;
}