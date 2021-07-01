#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H

#include "material.h"

class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(const Vec& albedo);

    bool calc_scattered_ray(const Ray&, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;

private:
    Vec m_albedo;
};

#endif
