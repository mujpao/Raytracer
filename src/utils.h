#ifndef UTILS_H
#define UTILS_H

class Vec;

namespace Utils {
    bool is_equal(double lhs, double rhs);
    bool is_gt_equal(double lhs, double rhs);

    double deg2rad(double degrees);

    // In range [min, max)
    double random_double(double min = 0.0, double max = 1.0);

    Vec random_vec(double min = 0.0, double max = 1.0);

    Vec random_in_unit_sphere();

    Vec random_in_unit_disk();

    double clamp(double value, double min, double max);
    Vec clamp(const Vec& v, double min, double max);

    bool is_small(double value);
    bool is_small(const Vec& v);

    const double RAY_HIT_TOLERANCE = 0.001;
    const double PI = 3.14159265358979323846;
    const double EPSILON = 0.000001;

    // Maximum ray parameter
    const double T_MAX = 10000.0;
} // namespace Utils

#endif
