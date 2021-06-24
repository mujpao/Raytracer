#include "utils.h"

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
}