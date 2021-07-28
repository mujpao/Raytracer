#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "math/mat4.h"
#include "shapes/shape.h"
#include "vertex.h"

class Triangle : public Shape {
public:
    Triangle(const Vec& p0, const Vec& p1, const Vec& p2,
        std::shared_ptr<Material> material, const Mat4& transform = Mat4(1.0));

    Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2,
        std::shared_ptr<Material> material, const Mat4& transform = Mat4(1.0));

    bool intersect(const Ray& ray, double t_min, double t_max,
        IntersectionInfo& intersection_info) const override;

private:
    std::array<double, 3> barycentric(const Vec& p) const;

    // Vec m_v1, m_v2, m_v3;
    std::array<Vertex, 3> m_vertices;

    Vec m_normal;
    double m_p_dot_n;
    double m_d00, m_d01, m_d11;
    double m_denom_inv;
};

#endif
