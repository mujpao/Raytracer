#ifndef METALMATERIAL_H
#define METALMATERIAL_H

#include "materials/material.h"

class MetalMaterial : public Material {
public:
    MetalMaterial(const Vec& albedo, double fuzz = 0.0);

    bool calc_scattered_ray(const Ray& ray, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;

private:
    Vec m_albedo;
    const double m_fuzz;
};

#endif
