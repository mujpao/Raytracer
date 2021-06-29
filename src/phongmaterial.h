#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "material.h"

class PointLight;
class DirectionalLight;

class PhongMaterial : public Material {
public:
    PhongMaterial(const Vec &ambient, const Vec &diffuse, const Vec &specular, double shininess, const Vec &emission = Vec(0.0, 0.0, 0.0));

    bool calc_scattered_ray(const Ray &ray, const IntersectionInfo &hit_info, Vec &atten_factor, Ray &scattered) const override;

    Vec base_shade(const Ray &ray, const IntersectionInfo &hit_info, const Scene &scene) const override;

private:
	Vec compute_light(double visibility, const Vec & light_color, const Vec & direction, const Vec & normal, 
		const Vec & half) const;

    Vec calc_lighting(const PointLight& point_light, const Vec & eye, const Scene & scene, const IntersectionInfo & intersection_info) const;

    Vec calc_lighting(const DirectionalLight& dir_light, const Vec & eye, const Scene & scene, const IntersectionInfo & intersection_info) const;

    Vec m_ambient, m_diffuse, m_specular, m_emission;
	double m_shininess;
};

#endif
