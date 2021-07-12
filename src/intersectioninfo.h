#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

#include "math/vec.h"

#include <memory>

class Material;

struct IntersectionInfo {
    double t_hit;
    double u, v;
    Vec position;
    Vec normal;
    std::shared_ptr<Material> material;
};

#endif