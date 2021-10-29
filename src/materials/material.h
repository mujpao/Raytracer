#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/vec.h"

class Ray;
struct IntersectionInfo;
class Scene;

class Material {
public:
    Material() = default;

    virtual ~Material() = default;
    Material(const Material&) = default;
    Material(Material&&) = default;
    Material& operator=(const Material&) = default;
    Material& operator=(Material&&) = default;

    virtual bool calc_scattered_ray(const Ray& ray,
        const IntersectionInfo& hit_info, Vec& atten_factor,
        Ray& scattered) const = 0;

    virtual Vec base_shade(
        const Ray&, const IntersectionInfo&, const Scene&) const {
        return Vec(0.0, 0.0, 0.0);
    }
};

#endif
