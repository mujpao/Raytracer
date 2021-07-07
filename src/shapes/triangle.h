#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shapes/shape.h"

#include "math/mat4.h"

class Triangle : public Shape {
public:
    Triangle(const Vec& p1, const Vec& p2, const Vec& p3,
        std::shared_ptr<Material> material, const Mat4& transform = Mat4(1.0));

    bool intersect(
        const Ray& ray, double& thit, IntersectionInfo& local) const override;
    // bool intersects(const Ray& ray) override;

private:
    void barycentric(const Vec& p, double& u, double& v, double& w) const;
    Vec m_v1, m_v2, m_v3;
};

#endif
