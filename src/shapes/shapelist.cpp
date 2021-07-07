#include "shapes/shapelist.h"

#include "intersectioninfo.h"
#include "utils.h"

ShapeList::ShapeList(const std::vector<std::shared_ptr<AbstractShape>>& shapes)
    : m_shapes(shapes) {
    m_box = m_shapes[0]->box();
    for (const auto& shape : m_shapes) {
        m_box = BoundingBox::combine(m_box, shape->box());
    }
}

bool ShapeList::intersect(
    const Ray& ray, double& thit, IntersectionInfo& intersection_info) const {
    bool has_intersect = false;

    for (const auto& shape : m_shapes) {
        double t = Utils::T_MAX;
        IntersectionInfo local;
        if (shape->intersect(ray, t, local)) {
            if (t > 0.0 && t < thit) {
                thit = t;
                intersection_info = local;
                has_intersect = true;
            }
        }
    }
    return has_intersect;
}

void ShapeList::add(std::shared_ptr<AbstractShape> shape) {
    m_box = BoundingBox::combine(m_box, shape->box());
    m_shapes.push_back(std::move(shape));
}
