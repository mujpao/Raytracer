#include "materials/lightmaterial.h"

#include "intersectioninfo.h"
#include "textures/flatcolortexture.h"

LightMaterial::LightMaterial(const Vec& albedo)
    : m_albedo(std::make_shared<FlatColorTexture>(albedo)) {}

LightMaterial::LightMaterial(std::shared_ptr<Texture> albedo)
    : m_albedo(std::move(albedo)) {}

bool LightMaterial::calc_scattered_ray(
    const Ray&, const IntersectionInfo&, Vec&, Ray&) const {
    return false;
}

Vec LightMaterial::base_shade(
    const Ray&, const IntersectionInfo& hit_info, const Scene&) const {
    return m_albedo->sample(
        hit_info.uv.first, hit_info.uv.second, hit_info.position);
}
