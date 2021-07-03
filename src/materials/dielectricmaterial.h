#ifndef DIELECTRICMATERIAL_H
#define DIELECTRICMATERIAL_H

#include "materials/material.h"

class DielectricMaterial : public Material {
public:
    DielectricMaterial(double refraction_idx);

    bool calc_scattered_ray(const Ray& ray, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;

private:
    // Schlick's Approximation
    static double reflectance(double cosine, double ref_idx);

    const double m_refraction_idx;
};

#endif
