#include "materials/dielectricmaterial.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"

#include <cmath>

DielectricMaterial::DielectricMaterial(double refraction_idx)
    : m_refraction_idx(refraction_idx) {}

bool DielectricMaterial::calc_scattered_ray(const Ray& ray,
    const IntersectionInfo& hit_info, Vec& atten_factor, Ray& scattered) const {

    Vec incident_dir = Vec::normalize(ray.direction());

    Vec normal = hit_info.normal;

    double eta1, eta2;
    if (Transform::dot(ray.direction(), hit_info.normal) < 0) {
        // Ray entering surface
        eta1 = 1.0;
        eta2 = m_refraction_idx;
    } else {
        // Ray exiting surface
        eta1 = m_refraction_idx;
        eta2 = 1.0;

        normal = -normal;
    }

    double cos_theta = Transform::dot(incident_dir, -normal);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    Vec scatter_dir;

    if (eta1 / eta2 * sin_theta > 1.0) {

        scatter_dir = Transform::reflect(ray.direction(), normal);
    } else {
        scatter_dir = Transform::refract(incident_dir, normal, eta1, eta2);
    }

    scattered = Ray(hit_info.position, scatter_dir);

    atten_factor = Vec(1.0, 1.0, 1.0);

    return true;
}