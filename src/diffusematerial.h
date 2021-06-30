#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H

#include "material.h"

class DiffuseMaterial : public Material {
public:
    bool calc_scattered_ray(const Ray&, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;
};

#endif
