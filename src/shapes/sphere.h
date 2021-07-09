#ifndef SPHERE_H
#define SPHERE_H

#include "shapes/shape.h"

#include "math/mat4.h"

class Sphere : public Shape {
public:
    Sphere(const Vec& center, double r, std::shared_ptr<Material> material,
        const Mat4& transform = Mat4(1.0));

    bool intersect(const Ray& ray, double t_min, double t_max,
        IntersectionInfo& intersection_info) const override;

private:
    Vec m_center;
    double m_radius;
    Mat4 m_transformation, m_inverse, m_inverse_transpose;
};

#endif
