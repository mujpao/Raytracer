#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shapes/shape.h"

#include "math/mat4.h"

class Triangle : public Shape {
public:
    Triangle(const Vec& p1, const Vec& p2, const Vec& p3,
        std::shared_ptr<Material> material, const Mat4& transform = Mat4(1.0));

    bool intersect(const Ray& ray, double t_min, double t_max,
        IntersectionInfo& intersection_info) const override;

private:
    Vec barycentric(const Vec& p) const;

    Vec m_v1, m_v2, m_v3;

    Vec m_normal;
    double m_p_dot_n;
    double m_d00, m_d01, m_d11;
    double m_denom_inv;
};

#endif
