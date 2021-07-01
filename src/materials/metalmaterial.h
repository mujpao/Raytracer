#ifndef METALMATERIAL_H
#define METALMATERIAL_H

#include "material.h"

class MetalMaterial : public Material {
public:
    MetalMaterial(const Vec& albedo);

    bool calc_scattered_ray(const Ray& ray, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;

private:
    Vec m_albedo;
};

#endif
