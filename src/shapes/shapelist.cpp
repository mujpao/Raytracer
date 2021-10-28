#include "shapes/shapelist.h"

#include "intersectioninfo.h"

ShapeList::ShapeList(const std::vector<std::shared_ptr<AbstractShape>>& shapes)
    : m_shapes(shapes) {
    m_box = m_shapes[0]->box();
    for (const auto& shape : m_shapes) {
        m_box = BoundingBox::combine(m_box, shape->box());
    }
}

bool ShapeList::intersect(const Ray& ray, double t_min, double t_max,
    IntersectionInfo& intersection_info) const {
    bool has_intersect = false;

    for (const auto& shape : m_shapes) {
        if (shape->intersect(ray, t_min, t_max, intersection_info)) {
            has_intersect = true;
            t_max = std::min(t_max, intersection_info.t_hit);
        }
    }
    return has_intersect;
}

void ShapeList::add(std::shared_ptr<AbstractShape> shape) {
    m_box = BoundingBox::combine(m_box, shape->box());
    m_shapes.push_back(std::move(shape));
}
