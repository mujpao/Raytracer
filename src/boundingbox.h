#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "math/vec.h"

class Ray;

class BoundingBox {
public:
    BoundingBox() = default;
    BoundingBox(const Vec& p1, const Vec& p2);

    inline const Vec& min() const { return m_min; }
    inline const Vec& max() const { return m_max; }

    bool intersect(const Ray& ray, double t_min, double t_max) const;

    static BoundingBox combine(
        const BoundingBox& left, const BoundingBox& right);

    friend std::ostream& operator<<(std::ostream& os, const BoundingBox& b);

private:
    Vec m_min;
    Vec m_max;
};

#endif
