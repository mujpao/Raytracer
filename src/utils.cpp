#include "utils.h"

#include <cmath>

namespace Utils {
    bool is_equal(double lhs, double rhs) {
        return std::abs(lhs - rhs) < EPSILON;
    }

    double deg2rad(double degrees) {
       return degrees * (PI / 180.0);
    }
}