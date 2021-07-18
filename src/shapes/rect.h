#ifndef RECT_H
#define RECT_H

#include "shapes/triangle.h"

class Rect : public Shape {
public:
    // t1: p1, p2, p3
    // t2: p1, p3, p4
    Rect(const Vec& p1, const Vec& p2, const Vec& p3, const Vec& p4,
        std::shared_ptr<Material> material, const Mat4& transform = Mat4(1.0));

    bool intersect(const Ray& ray, double t_min, double t_max,
        IntersectionInfo& intersection_info) const override;

private:
    Triangle m_t1, m_t2;
};

#endif
