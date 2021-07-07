#include "boundingbox.h"

#include "ray.h"
#include "utils.h"

#include <algorithm>

BoundingBox::BoundingBox(const Vec& p1, const Vec& p2)
    : m_min(std::min(p1[0], p2[0]), std::min(p1[1], p2[1]),
        std::min(p1[2], p2[2]), 1.0),
      m_max(std::max(p1[0], p2[0]), std::max(p1[1], p2[1]),
          std::max(p1[2], p2[2]), 1.0) {}

bool BoundingBox::intersect(const Ray& ray, double t_min, double t_max) {
    for (int i = 0; i < 3; ++i) {
        double n0 = m_min[i] - ray.origin()[i];
        double n1 = m_max[i] - ray.origin()[i];

        if (Utils::is_equal(n0, 0.0) || Utils::is_equal(n1, 0.0)) {
            continue;
        }

        double inv_d = 1.0 / ray.direction()[i];
        double t0 = n0 * inv_d;
        double t1 = n1 * inv_d;
        if (inv_d < 0.0) {
            std::swap(t0, t1);
        }

        t_min = std::max(t_min, t0);
        t_max = std::min(t_max, t1);

        if (t_max <= t_min) {
            return false;
        }
    }

    return true;
}
