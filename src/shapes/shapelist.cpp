#include "shapes/shapelist.h"

#include "intersectioninfo.h"

ShapeList::ShapeList(std::vector<std::shared_ptr<Shape>> shapes)
    : m_shapes(shapes) {}

bool ShapeList::intersect(
    const Ray& ray, double& thit, IntersectionInfo& intersection_info) const {
    bool has_intersect = false;

    for (auto& shape : m_shapes) {
        double t;
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

void ShapeList::add(std::shared_ptr<Shape> shape) {
    m_shapes.push_back(std::move(shape));
}
