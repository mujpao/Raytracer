#include "shapes/rect.h"

#include "boundingbox.h"
#include "intersectioninfo.h"

Rect::Rect(const Vec& p1, const Vec& p2, const Vec& p3, const Vec& p4,
    std::shared_ptr<Material> material, const Mat4& transform)
    : Shape(material), m_t1(Triangle(p1, p2, p3, material, transform)),
      m_t2(Triangle(p1, p3, p4, std::move(material), transform)) {
    m_box = BoundingBox::combine(m_t1.box(), m_t2.box());
}

bool Rect::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {
    bool hit_t1 = m_t1.intersect(ray, t_min, t_max, intersection_info);
    if (hit_t1) {
        t_max = std::min(t_max, intersection_info.t_hit);
    }

    bool hit_t2 = m_t2.intersect(ray, t_min, t_max, intersection_info);

    return hit_t1 || hit_t2;
}
