#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "materials/material.h"

#include "textures/flatcolortexture.h"

#include <memory>

class PointLight;
class DirectionalLight;
class Texture;

class PhongMaterial : public Material {
public:
    PhongMaterial(const Vec& ambient, const Vec& diffuse, const Vec& specular,
        double shininess, const Vec& emission = Vec(0.0, 0.0, 0.0));

    PhongMaterial(std::shared_ptr<Texture> ambient,
        std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> specular,
        double shininess,
        std::shared_ptr<Texture> emission
        = std::make_shared<FlatColorTexture>(Vec(0.0, 0.0, 0.0)));

    bool calc_scattered_ray(const Ray& ray, const IntersectionInfo& hit_info,
        Vec& atten_factor, Ray& scattered) const override;

    Vec base_shade(const Ray& ray, const IntersectionInfo& hit_info,
        const Scene& scene) const override;

private:
    Vec compute_light(double visibility, const Vec& light_color,
        const Vec& direction, const Vec& half,
        const IntersectionInfo& hit_info) const;

    Vec calc_lighting(const PointLight& point_light, const Vec& eye,
        const Scene& scene, const IntersectionInfo& intersection_info) const;

    Vec calc_lighting(const DirectionalLight& dir_light, const Vec& eye,
        const Scene& scene, const IntersectionInfo& intersection_info) const;

    std::shared_ptr<Texture> m_ambient, m_diffuse, m_specular, m_emission;
    double m_shininess;
};

#endif
