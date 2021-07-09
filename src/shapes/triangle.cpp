#include "shapes/triangle.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"
#include "utils.h"

Triangle::Triangle(const Vec& p1, const Vec& p2, const Vec& p3,
    std::shared_ptr<Material> material, const Mat4& transform)
    : Shape(std::move(material)), m_v1(transform * p1), m_v2(transform * p2),
      m_v3(transform * p3) {
    m_box = BoundingBox(Utils::min_vec(Utils::min_vec(p1, p2), p3),
        Utils::max_vec(Utils::max_vec(p1, p2), p3));
}

bool Triangle::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {
    Vec a = m_v1;
    Vec b = m_v2;
    Vec c = m_v3;

    Vec n = Vec::normalize(Transform::cross(b - a, c - a));

    double denom = Transform::dot(ray.direction(), n);
    if (denom == 0)
        return false;

    double t = (Transform::dot(a, n) - Transform::dot(ray.origin(), n)) / denom;

    if (t < t_min || t > t_max) {
        return false;
    }

    Vec position = ray.evaluate(t);

    Vec coords = barycentric(position);

    for (int i = 0; i < 3; ++i) {
        if (coords[i] < 0.0 || coords[i] > 1.0) {
            return false;
        }
    }

    intersection_info.position = position;
    intersection_info.normal = n;
    intersection_info.material = m_material;
    intersection_info.t_hit = t;
    return true;
}

Vec Triangle::barycentric(const Vec& p) const {
    Vec a = m_v2 - m_v1;
    Vec b = m_v3 - m_v1;
    Vec c = p - m_v1;
    double d00 = Transform::dot(a, a);
    double d01 = Transform::dot(a, b);
    double d11 = Transform::dot(b, b);
    double d20 = Transform::dot(c, a);
    double d21 = Transform::dot(c, b);
    double denom = d00 * d11 - d01 * d01;

    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;

    return Vec(u, v, w);
}
