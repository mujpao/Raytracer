#include "diffusematerial.h"

#include "intersectioninfo.h"
#include "ray.h"
#include "utils.h"

bool DiffuseMaterial::calc_scattered_ray(const Ray&,
    const IntersectionInfo& hit_info, Vec& atten_factor, Ray& scattered) const {
    // TODO normal directions
    Vec scatter_dir = Vec::to_vec(hit_info.position + hit_info.normal
        + Vec::normalize(Utils::random_in_unit_sphere()));
    scattered = Ray(hit_info.position, scatter_dir);
    atten_factor = Vec(0.5, 0.5, 0.5);
    return true;
}
