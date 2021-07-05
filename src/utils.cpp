#include "utils.h"

#include "math/vec.h"

#include <cmath>
#include <stdlib.h>

namespace Utils {
    bool is_equal(double lhs, double rhs) {
        return std::abs(lhs - rhs) < EPSILON;
    }

    bool is_gt_equal(double lhs, double rhs) {
        return lhs > rhs || is_equal(lhs, rhs);
    }

    double deg2rad(double degrees) { return degrees * (PI / 180.0); }

    double random_double(double min, double max) {
        return rand() * (max - min) / (RAND_MAX + 1.0) + min;
    }

    Vec random_vec(double min, double max) {
        Vec result;
        for (int i = 0; i < 3; ++i) {
            result[i] = random_double(min, max);
        }
        return result;
    }

    Vec random_in_unit_sphere() {
        while (true) {
            Vec v = Vec::to_point(random_vec(-1.0, 1.0));
            if (Vec::length_squared(v) < 1.0) {
                return v;
            }
        }
    }

    Vec random_in_unit_disk() {
        while (true) {
            Vec v = Vec::to_point(
                Vec(random_double(-1.0, 1.0), random_double(-1.0, 1.0), 0.0));
            if (Vec::length_squared(v) < 1.0) {
                return v;
            }
        }
    }

    double clamp(double value, double min, double max) {
        if (value > max)
            return max;
        if (value < min)
            return min;
        return value;
    }

    Vec clamp(const Vec& v, double min, double max) {
        Vec result = v;
        for (int i = 0; i < 3; ++i) {
            result[i] = clamp(v[i], min, max);
        }
        return result;
    }

    bool is_small(double value) { return std::abs(value) < EPSILON; }

    bool is_small(const Vec& v) {
        return is_small(v[0]) && is_small(v[1]) && is_small(v[2]);
    }

} // namespace Utils