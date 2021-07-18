#ifndef LIGHTMATERIAL_H
#define LIGHTMATERIAL_H

#include "materials/material.h"

#include <memory>

class Texture;

class LightMaterial : public Material {
public:
    LightMaterial(const Vec& albedo);

    LightMaterial(std::shared_ptr<Texture> albedo);

    bool calc_scattered_ray(const Ray&, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;

    Vec base_shade(const Ray& ray, const IntersectionInfo& hit_info,
        const Scene& scene) const override;

private:
    std::shared_ptr<Texture> m_albedo;
};

#endif
