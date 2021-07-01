#include "diffusematerial.h"

#include "intersectioninfo.h"
#include "ray.h"
#include "utils.h"

DiffuseMaterial::DiffuseMaterial(const Vec& albedo) : m_albedo(albedo) {}

bool DiffuseMaterial::calc_scattered_ray(const Ray&,
    const IntersectionInfo& hit_info, Vec& atten_factor, Ray& scattered) const {
    // TODO normal directions
    Vec scatter_dir = Vec::to_vec(hit_info.position + hit_info.normal
        + Vec::normalize(Utils::random_in_unit_sphere()));

    if (Utils::is_small(scatter_dir)) {
        scatter_dir = hit_info.normal;
    }

    scattered = Ray(hit_info.position, scatter_dir);
    atten_factor = m_albedo;
    return true;
}
