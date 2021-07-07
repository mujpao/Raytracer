#ifndef SHAPELIST_H
#define SHAPELIST_H

#include "shapes/shape.h"

#include <vector>

class ShapeList : public AbstractShape {
public:
    ShapeList() = default;

    ShapeList(std::vector<std::shared_ptr<Shape>> shapes);

    bool intersect(const Ray& ray, double& thit,
        IntersectionInfo& intersection_info) const override;

    void add(std::shared_ptr<Shape> shape);

private:
    std::vector<std::shared_ptr<Shape>> m_shapes;
};

#endif
