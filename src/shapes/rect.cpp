#include "shapes/rect.h"

Rect::Rect(const Vec& p1, const Vec& p2, const Vec& p3, const Vec& p4,
    std::shared_ptr<Material> material, const Mat4& transform)
    : Shape(material), m_t1(Triangle(p1, p2, p3, material, transform)),
      m_t2(Triangle(p1, p3, p4, std::move(material), transform)) {}

bool Rect::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {
    bool hit1 = m_t1.intersect(ray, t_min, t_max, intersection_info);
    bool hit2 = m_t2.intersect(ray, t_min, t_max, intersection_info);

    return hit1 || hit2;
}
