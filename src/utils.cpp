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

    int random_int(int min, int max) { return rand() % (max - min + 1) + min; }

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

    Vec min_vec(const Vec& a, const Vec& b) {
        return Vec(std::min(a[0], b[0]), std::min(a[1], b[1]),
            std::min(a[2], b[2]), 1.0);
    }

    Vec max_vec(const Vec& a, const Vec& b) {
        return Vec(std::max(a[0], b[0]), std::max(a[1], b[1]),
            std::max(a[2], b[2]), 1.0);
    }

    double lerp(double a, double b, double t) { return (b - a) * t + a; }

} // namespace Utils