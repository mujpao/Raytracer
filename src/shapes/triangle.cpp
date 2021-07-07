#include "shapes/triangle.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"

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
