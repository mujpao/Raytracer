#include "materials/metalmaterial.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"

MetalMaterial::MetalMaterial(const Vec& albedo) : m_albedo(albedo) {}

bool MetalMaterial::calc_scattered_ray(const Ray& ray,
    const IntersectionInfo& hit_info, Vec& atten_factor, Ray& scattered) const {
    Vec reflected_dir = Transform::reflect(ray.direction(), hit_info.normal);

    scattered = Ray(hit_info.position, reflected_dir);
    atten_factor = m_albedo;

    return Transform::dot(reflected_dir, hit_info.normal) > 0;
}
