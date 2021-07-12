#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H

#include "materials/material.h"

#include <memory>

class Texture;

class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(const Vec& albedo);

    DiffuseMaterial(std::shared_ptr<Texture> albedo);

    bool calc_scattered_ray(const Ray&, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;

private:
    std::shared_ptr<Texture> m_albedo;
};

#endif
