#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

#include "math/vec.h"

#include <memory>

class Material;

struct IntersectionInfo {
    double t_hit;
    std::pair<double, double> uv;
    Vec position;
    Vec normal;
    std::shared_ptr<Material> material;
};

#endif