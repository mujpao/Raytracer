#include "materials/diffusematerial.h"

#include "intersectioninfo.h"
#include "ray.h"
#include "textures/flatcolortexture.h"
#include "utils.h"

DiffuseMaterial::DiffuseMaterial(const Vec& albedo)
    : m_albedo(std::make_shared<FlatColorTexture>(albedo)) {}

DiffuseMaterial::DiffuseMaterial(std::shared_ptr<Texture> albedo)
    : m_albedo(albedo) {}

bool DiffuseMaterial::calc_scattered_ray(const Ray&,
    const IntersectionInfo& hit_info, Vec& atten_factor, Ray& scattered) const {
    Vec scatter_dir = Vec::to_vec(
        hit_info.normal + Vec::normalize(Utils::random_in_unit_sphere()));

    if (Utils::is_small(scatter_dir)) {
        scatter_dir = hit_info.normal;
    }

    scattered = Ray(hit_info.position, scatter_dir);
    atten_factor = m_albedo->sample(hit_info.uv.first, hit_info.uv.second,
        hit_info.position); // TODO Position or normal?
    return true;
}
