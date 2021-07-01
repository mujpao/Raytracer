#include "materials/metalmaterial.h"

#include "intersectioninfo.h"
#include "math/transform.h"
#include "ray.h"
#include "utils.h"

MetalMaterial::MetalMaterial(const Vec& albedo, double fuzz)
    : m_albedo(albedo), m_fuzz(std::min(fuzz, 1.0)) {}

bool MetalMaterial::calc_scattered_ray(const Ray& ray,
    const IntersectionInfo& hit_info, Vec& atten_factor, Ray& scattered) const {
    Vec reflected_dir = Transform::reflect(ray.direction(), hit_info.normal);
    reflected_dir += m_fuzz * Utils::random_in_unit_sphere();

    scattered = Ray(hit_info.position, reflected_dir);
    atten_factor = m_albedo;

    return Transform::dot(reflected_dir, hit_info.normal) > 0;
}
