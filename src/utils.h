#ifndef UTILS_H
#define UTILS_H

class Vec;

namespace Utils {
    bool is_equal(double lhs, double rhs);

    double deg2rad(double degrees);

    // In range [min, max)
    double random_double(double min, double max);

    double clamp(double value, double min, double max);
    Vec clamp(const Vec &v, double min, double max);

    const double RAY_HIT_TOLERANCE = 0.001;
    const double EPSILON = 0.000001;
    const double PI = 3.14159265358979323846;
}

#endif
