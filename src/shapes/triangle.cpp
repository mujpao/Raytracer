#include "shapes/triangle.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"
#include "utils.h"

Triangle::Triangle(const Vec& p1, const Vec& p2, const Vec& p3,
    std::shared_ptr<Material> material, const Mat4& transform)
    : Shape(std::move(material)), m_v1(transform * Vec::to_point(p1)),
      m_v2(transform * Vec::to_point(p2)), m_v3(transform * Vec::to_point(p3)) {
    m_box = BoundingBox(Utils::min_vec(Utils::min_vec(m_v1, m_v2), m_v3),
        Utils::max_vec(Utils::max_vec(m_v1, m_v2), m_v3));

    m_normal = Vec::normalize(Transform::cross(m_v2 - m_v1, m_v3 - m_v1));
    m_p_dot_n = Transform::dot(m_v1, m_normal);

    Vec a = m_v2 - m_v1;
    Vec b = m_v3 - m_v1;

    m_d00 = Transform::dot(a, a);
    m_d01 = Transform::dot(a, b);
    m_d11 = Transform::dot(b, b);

    m_denom_inv = 1.0 / (m_d00 * m_d11 - m_d01 * m_d01);
}

bool Triangle::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {

    double denom = Transform::dot(ray.direction(), m_normal);
    if (denom == 0)
        return false;

    double t = (m_p_dot_n - Transform::dot(ray.origin(), m_normal)) / denom;

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

    // TODO texture coordinates

    intersection_info.position = position;
    intersection_info.normal = m_normal;
    intersection_info.material = m_material;
    intersection_info.t_hit = t;

    return true;
}

Vec Triangle::barycentric(const Vec& p) const {
    Vec a = m_v2 - m_v1;
    Vec b = m_v3 - m_v1;
    Vec c = p - m_v1;

    double d20 = Transform::dot(c, a);
    double d21 = Transform::dot(c, b);

    double v = (m_d11 * d20 - m_d01 * d21) * m_denom_inv;
    double w = (m_d00 * d21 - m_d01 * d20) * m_denom_inv;
    double u = 1.0 - v - w;

    return Vec(u, v, w);
}
