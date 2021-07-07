#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H

class IntersectionInfo;
class Ray;

class AbstractShape {
public:
    virtual ~AbstractShape() = default;

    virtual bool intersect(
        const Ray& ray, double& thit, IntersectionInfo& local) const = 0;
};

#endif
