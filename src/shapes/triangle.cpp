#include "shapes/triangle.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"
#include "utils.h"

Triangle::Triangle(const Vec& p0, const Vec& p1, const Vec& p2,
    std::shared_ptr<Material> material, const Mat4& transform)
    : Triangle(Vertex{ p0 }, Vertex{ p1 }, Vertex{ p2 }, std::move(material),
        transform) {}

Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2,
    std::shared_ptr<Material> material, const Mat4& transform)
    : Shape(std::move(material)), m_vertices{ v0, v1, v2 } {

    for (auto& vertex : m_vertices) {
        vertex.set_position(transform * vertex.position());
    }

    m_box = BoundingBox(Utils::min_vec(Utils::min_vec(m_vertices[0].position(),
                                           m_vertices[1].position()),
                            m_vertices[2].position()),
        Utils::max_vec(
            Utils::max_vec(m_vertices[0].position(), m_vertices[1].position()),
            m_vertices[2].position()));

    m_normal = Vec::normalize(
        Transform::cross(m_vertices[1].position() - m_vertices[0].position(),
            m_vertices[2].position() - m_vertices[0].position()));

    m_p_dot_n = Transform::dot(m_vertices[0].position(), m_normal);

    Vec a = m_vertices[1].position() - m_vertices[0].position();
    Vec b = m_vertices[2].position() - m_vertices[0].position();

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

    std::array<double, 3> coords = barycentric(position);

    for (int i = 0; i < 3; ++i) {
        if (coords[i] < 0.0 || coords[i] > 1.0) {
            return false;
        }
    }

    intersection_info.position = position;
    intersection_info.normal = m_normal;
    intersection_info.material = m_material;
    intersection_info.t_hit = t;

    intersection_info.uv = { 0.0, 0.0 };
    for (int i = 0; i < 3; ++i) {
        intersection_info.uv.first += coords[i] * m_vertices[i].u();
        intersection_info.uv.second += coords[i] * m_vertices[i].v();
    }

    return true;
}

std::array<double, 3> Triangle::barycentric(const Vec& p) const {
    Vec a = m_vertices[1].position() - m_vertices[0].position();
    Vec b = m_vertices[2].position() - m_vertices[0].position();

    Vec c = p - m_vertices[0].position();

    double d20 = Transform::dot(c, a);
    double d21 = Transform::dot(c, b);

    double v = (m_d11 * d20 - m_d01 * d21) * m_denom_inv;
    double w = (m_d00 * d21 - m_d01 * d20) * m_denom_inv;
    double u = 1.0 - v - w;

    return { u, v, w };
}
