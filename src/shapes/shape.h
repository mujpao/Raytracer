#ifndef SHAPE_H
#define SHAPE_H

#include "math/vec.h"

#include <memory>

class Material;
class IntersectionInfo;
class Ray;

class Shape {
public:
    Shape(std::shared_ptr<Material> material);
    virtual ~Shape() = default;

    virtual bool intersect(
        const Ray& ray, double& thit, IntersectionInfo& local)
        = 0;
    virtual bool intersects(const Ray& ray) = 0;

protected:
    std::shared_ptr<Material> m_material;
};

#endif
