#ifndef UTILS_H
#define UTILS_H

#include "math/vec.h"

namespace Utils {
    const double RAY_HIT_TOLERANCE = 0.001;
    const double PI = 3.14159265358979323846;
    const double EPSILON = 0.000001;

    // Maximum ray parameter
    const double T_MAX = 10000.0;

    bool is_equal(double lhs, double rhs);
    bool is_gt_equal(double lhs, double rhs);

    double deg2rad(double degrees);
    double rad2deg(double rad);

    // In range [min, max]
    int random_int(int min = 0, int max = 1);

    // In range [min, max)
    double random_double(double min = 0.0, double max = 1.0);

    Vec random_vec(double min = 0.0, double max = 1.0);

    Vec random_in_unit_sphere();

    Vec random_in_unit_disk();

    double clamp(double value, double min, double max);
    Vec clamp(const Vec& v, double min, double max);

    bool is_small(double value);
    bool is_small(const Vec& v);

    // Compute component-wise min/max of a and b, set w coordinate to 1.0
    Vec min_vec(const Vec& a, const Vec& b);
    Vec max_vec(const Vec& a, const Vec& b);

    template<typename... Ts>
    Vec min_vec(const Vec& a, const Vec& b, const Ts&... ts) {
        const Vec m = min_vec(a, b);
        if constexpr (sizeof...(ts) > 0) {
            return min_vec(m, ts...);
        }
        return m;
    }

    template<typename... Ts>
    Vec max_vec(const Vec& a, const Vec& b, const Ts&... ts) {
        const Vec m = max_vec(a, b);
        if constexpr (sizeof...(ts) > 0) {
            return max_vec(m, ts...);
        }
        return m;
    }

    double lerp(double a, double b, double t);

} // namespace Utils

#endif
