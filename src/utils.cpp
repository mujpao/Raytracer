#include "utils.h"

#include "math/vec.h"

#include <cmath>
#include <stdlib.h>

namespace Utils {
    bool is_equal(double lhs, double rhs) {
        return std::abs(lhs - rhs) < EPSILON;
    }

    double deg2rad(double degrees) {
       return degrees * (PI / 180.0);
    }

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

    double clamp(double value, double min, double max) {
        if (value > max)
            return max;
        if (value < min)
            return min;
        return value;
    }

    Vec clamp(const Vec &v, double min, double max) {
        Vec result = v;
        for (int i = 0; i < 3; ++i) {
            result[i] = clamp(v[i], min, max);
        }
        return result;
    }
}