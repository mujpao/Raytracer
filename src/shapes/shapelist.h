#ifndef SHAPELIST_H
#define SHAPELIST_H

#include "shapes/shape.h"

#include <vector>

class ShapeList : public AbstractShape {
public:
    ShapeList() = default;

    ShapeList(const std::vector<std::shared_ptr<AbstractShape>>& shapes);

    inline const std::vector<std::shared_ptr<AbstractShape>>& shapes() const {
        return m_shapes;
    }

    bool intersect(const Ray& ray, double& thit,
        IntersectionInfo& intersection_info) const override;

    void add(std::shared_ptr<AbstractShape> shape);

private:
    std::vector<std::shared_ptr<AbstractShape>> m_shapes;
};

#endif
