#include "shape.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"

#include <cmath>

Shape::Shape(std::shared_ptr<Material> material)
    : m_material(std::move(material)) {}

Triangle::Triangle(const Vec& p1, const Vec& p2, const Vec& p3,
    std::shared_ptr<Material> material, const Mat4& transform)
    : Shape(std::move(material)), m_v1(transform * p1), m_v2(transform * p2),
      m_v3(transform * p3) {}

bool Triangle::intersect(
    const Ray& ray, double& thit, IntersectionInfo& local) {
    Vec a = m_v1;
    Vec b = m_v2;
    Vec c = m_v3;

    Vec n = Vec::normalize(Transform::cross(b - a, c - a));

    double denom = Transform::dot(ray.direction(), n);
    if (denom == 0)
        return false;

    thit = (Transform::dot(a, n) - Transform::dot(ray.origin(), n)) / denom;

    local.position = ray.evaluate(thit);
    local.normal = n;
    local.material = m_material;

    double alpha, beta, gamma;
    barycentric(local.position, alpha, beta, gamma);

    if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0
        && gamma <= 1)
        return true;

    return false;
}

bool Triangle::intersects(const Ray& ray) {
    Vec a = m_v1;
    Vec b = m_v2;
    Vec c = m_v3;

    Vec n = Vec::normalize(Transform::cross(b - a, c - a));

    double denom = Transform::dot(ray.direction(), n);
    if (denom == 0)
        return false;

    double thit;
    thit = (Transform::dot(a, n) - Transform::dot(ray.origin(), n)) / denom;

    Vec pos = ray.evaluate(thit);

    double alpha, beta, gamma;
    barycentric(pos, alpha, beta, gamma);

    if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0
        && gamma <= 1)
        return true;

    return false;
}

void Triangle::barycentric(const Vec& p, double& u, double& v, double& w) {
    Vec a = m_v2 - m_v1;
    Vec b = m_v3 - m_v1;
    Vec c = p - m_v1;
    double d00 = Transform::dot(a, a);
    double d01 = Transform::dot(a, b);
    double d11 = Transform::dot(b, b);
    double d20 = Transform::dot(c, a);
    double d21 = Transform::dot(c, b);
    double denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0 - v - w;
}

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
