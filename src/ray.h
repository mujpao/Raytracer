#ifndef RAY_H
#define RAY_H

#include "math/vec.h"

class Ray {
public:
    Ray() = default;
    Ray(const Vec& origin, const Vec& direction);

    inline const Vec& origin() const { return m_origin; }
    inline const Vec& direction() const { return m_direction; }

    Vec evaluate(double t) const;

    friend std::ostream& operator<<(std::ostream& os, const Ray& r);

private:
    Vec m_origin;
    Vec m_direction;
};

#endif
