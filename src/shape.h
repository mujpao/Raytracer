#ifndef SHAPE_H
#define SHAPE_H

#include "math/mat4.h"
#include "math/vec.h"

#include <memory>

class Material;
class IntersectionInfo;

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

class Triangle : public Shape {
public:
    Triangle(const Vec& p1, const Vec& p2, const Vec& p3, const Mat4& transform,
        std::shared_ptr<Material> material);

    bool intersect(
        const Ray& ray, double& thit, IntersectionInfo& local) override;
    bool intersects(const Ray& ray) override;

private:
    void barycentric(const Vec& p, double& u, double& v, double& w);
    Vec m_v1, m_v2, m_v3;
};

class Sphere : public Shape {
public:
    Sphere(const Vec& center, double r, const Mat4& transform,
        std::shared_ptr<Material> material);

    bool intersect(
        const Ray& ray, double& thit, IntersectionInfo& local) override;
    bool intersects(const Ray& ray) override;

private:
    Vec m_center;
    double m_radius;
    Mat4 m_transformation, m_inverse, m_inverse_transpose;
};

#endif
