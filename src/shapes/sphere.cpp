#include "shapes/sphere.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"
#include "utils.h"

#include <cmath>

Sphere::Sphere(const Vec& center, double r, std::shared_ptr<Material> material,
    const Mat4& transform)
    : Shape(std::move(material)), m_center(Vec::to_point(center)), m_radius(r),
      m_transformation(transform) {
    m_inverse = Transform::inverse(m_transformation);
    m_inverse_transpose
        = Transform::transpose3x3(Transform::inverse3x3(m_transformation));

    Vec v(1.0, 1.0, 1.0, 1.0);
    // TODO ellipsoid box
    m_box = BoundingBox(center - r * v, center + r * v);
}

bool Sphere::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {
    Ray r2 = m_inverse * ray;

    double a = Transform::dot(r2.direction(), r2.direction());
    double b = 2 * Transform::dot(r2.direction(), r2.origin() - m_center);
    double c = Transform::dot(r2.origin() - m_center, r2.origin() - m_center)
        - m_radius * m_radius;

    // check if discriminant < 0
    double disc = b * b - 4.0 * a * c;

    if (disc < 0)
        return false;

    double t1 = (-b + std::sqrt(disc)) / (2.0 * a);
    double t2 = (-b - std::sqrt(disc)) / (2.0 * a);

    double t;
    if (t1 > 0 && t2 > 0) {
        t = std::min(t1, t2);
    } else if (t1 > 0) {
        t = t1;
    } else if (t2 > 0) {
        t = t2;
    } else {
        return false;
    }

    if (t < t_min || t > t_max) {
        return false;
    }

    intersection_info.t_hit = t;

    Vec untransformed_point = r2.evaluate(t);
    Vec untransformed_normal = Vec::normalize(untransformed_point - m_center);

    intersection_info.position = m_transformation * untransformed_point;
    intersection_info.normal
        = Vec::normalize(m_inverse_transpose * untransformed_normal);
    if (m_radius < 0.0) {
        intersection_info.normal *= -1.0;
    }

    intersection_info.material = m_material;

    return true;
}
