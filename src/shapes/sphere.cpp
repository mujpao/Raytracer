#include "shapes/sphere.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"

#include <cmath>

Sphere::Sphere(const Vec& center, double r, std::shared_ptr<Material> material,
    const Mat4& transform)
    : Shape(std::move(material)), m_center(Vec::to_point(center)), m_radius(r),
      m_transformation(transform) {
    m_inverse = Transform::inverse(m_transformation);
    m_inverse_transpose
        = Transform::transpose3x3(Transform::inverse3x3(m_transformation));
}

bool Sphere::intersect(const Ray& ray, double& thit, IntersectionInfo& local) {
    double a, b, c, disc;
    Ray r2 = m_inverse * ray;

    a = Transform::dot(r2.direction(), r2.direction());
    b = 2 * Transform::dot(r2.direction(), r2.origin() - m_center);
    c = Transform::dot(r2.origin() - m_center, r2.origin() - m_center)
        - std::pow(m_radius, 2.0);

    // check if discriminant < 0
    disc = std::pow(b, 2.0) - 4.0 * a * c;

    if (disc < 0)
        return false;

    double t1 = (-b + std::sqrt(disc)) / (2.0 * a);
    double t2 = (-b - std::sqrt(disc)) / (2.0 * a);

    if (t1 > 0 && t2 > 0) {
        thit = std::min(t1, t2);
    } else if (t1 > 0) {
        thit = t1;
    } else if (t2 > 0) {
        thit = t2;
    } else {
        return false;
    }

    Vec untransformed_point = r2.evaluate(thit);
    Vec untransformed_normal = Vec::normalize(untransformed_point - m_center);

    local.position = m_transformation * untransformed_point;
    local.normal = Vec::normalize(m_inverse_transpose * untransformed_normal);
    if (m_radius < 0.0) {
        local.normal *= -1.0;
    }

    local.material = m_material;

    return true;
}

bool Sphere::intersects(const Ray& ray) {
    double a, b, c, disc;

    Ray r2 = Transform::inverse(m_transformation) * ray;

    a = Transform::dot(r2.direction(), r2.direction());
    b = 2 * Transform::dot(r2.direction(), r2.origin() - m_center);
    c = Transform::dot(r2.origin() - m_center, r2.origin() - m_center)
        - std::pow(m_radius, 2.0);

    // check if discriminant >= 0
    disc = std::pow(b, 2.0) - 4.0 * a * c;
    return disc >= 0;
}
