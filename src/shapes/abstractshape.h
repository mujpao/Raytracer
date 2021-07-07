#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H

#include "boundingbox.h"

class IntersectionInfo;
class Ray;

class AbstractShape {
public:
    AbstractShape() : m_box(BoundingBox()) {}
    AbstractShape(const BoundingBox& box) : m_box(box) {}

    virtual ~AbstractShape() = default;

    virtual bool intersect(
        const Ray& ray, double& thit, IntersectionInfo& local) const = 0;

    const BoundingBox& box() const { return m_box; };

protected:
    BoundingBox m_box;
};

#endif
