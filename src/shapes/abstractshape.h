#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H

#include "boundingbox.h"

struct IntersectionInfo;
class Ray;

class AbstractShape {
public:
    AbstractShape() : m_box(BoundingBox()) {}
    AbstractShape(const BoundingBox& box) : m_box(box) {}

    virtual ~AbstractShape() = default;

    virtual bool intersect(const Ray& ray, double t_min, double t_max,
        IntersectionInfo& intersection_info) const = 0;

    const BoundingBox& box() const { return m_box; };

protected:
    BoundingBox m_box;
};

#endif
