#include "materials/phongmaterial.h"

#include "intersectioninfo.h"
#include "light.h"
#include "math/transform.h"
#include "ray.h"
#include "scene.h"
#include "utils.h"

#include <cmath>

PhongMaterial::PhongMaterial(const Vec& ambient, const Vec& diffuse,
    const Vec& specular, double shininess, const Vec& emission)
    : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular),
      m_emission(emission), m_shininess(shininess) {}

bool PhongMaterial::calc_scattered_ray(const Ray& ray,
    const IntersectionInfo& hit_info, Vec& atten_factor, Ray& scattered) const {
    Vec reflected_dir = Transform::reflect(ray.direction(), hit_info.normal);
    scattered = Ray(hit_info.position, reflected_dir);
    atten_factor = m_specular;
    return true;
}

Vec PhongMaterial::base_shade(const Ray& ray, const IntersectionInfo& hit_info,
    const Scene& scene) const {
    Vec color = m_ambient + m_emission;
    for (const auto& light : scene.lights) {
        if (auto dir_light = dynamic_cast<DirectionalLight*>(light.get())) {
            color += calc_lighting(*dir_light, ray.origin(), scene, hit_info);
        } else if (auto point_light = dynamic_cast<PointLight*>(light.get())) {
            color += calc_lighting(*point_light, ray.origin(), scene, hit_info);
        }
    }
    return color;
}

Vec PhongMaterial::compute_light(double visibility, const Vec& light_color,
    const Vec& direction, const Vec& normal, const Vec& half) const {
    double ndotl = Transform::dot(direction, normal);
    double hdotn = Transform::dot(half, normal);

    Vec result = visibility * light_color
        * (m_diffuse * std::max(ndotl, 0.0)
            + m_specular * std::pow(std::max(hdotn, 0.0), m_shininess));
    return result;
}

Vec PhongMaterial::calc_lighting(const PointLight& point_light, const Vec& eye,
    const Scene& scene, const IntersectionInfo& intersection_info) const {
    double dist = Vec::dist(intersection_info.position, point_light.position());

    Vec ray_dir = Vec::to_vec(
        Vec::normalize(point_light.position() - intersection_info.position));
    Ray ray(intersection_info.position, ray_dir);

    Vec atten_light_color = point_light.calc_attenuation(dist);

    double visibility;
    IntersectionInfo shadow_hit_info;
    if (scene.intersect(ray, Utils::RAY_HIT_TOLERANCE, shadow_hit_info)
        && Vec::dist(shadow_hit_info.position, point_light.position())
            < dist) // TODO what if light is between objects?
        visibility = 0.0;
    else
        visibility = 1.0;

    Vec dir = ray.direction();
    Vec eyedirn = Vec::normalize(eye - intersection_info.position);
    Vec half = Vec::normalize(dir + eyedirn);

    return compute_light(
        visibility, atten_light_color, dir, intersection_info.normal, half);
}

Vec PhongMaterial::calc_lighting(const DirectionalLight& dir_light,
    const Vec& eye, const Scene& scene,
    const IntersectionInfo& intersection_info) const {
    Ray ray(Vec::to_point(intersection_info.position),
        Vec::normalize(dir_light.direction()));

    double visibility;
    IntersectionInfo shadow_hit_info;
    if (scene.intersect(ray, Utils::RAY_HIT_TOLERANCE, shadow_hit_info))
        visibility = 0.0;
    else
        visibility = 1.0;

    Vec pos_vector(intersection_info.position.x(),
        intersection_info.position.y(), intersection_info.position.z());
    Vec eyedirn = Vec::normalize(eye - pos_vector);
    Vec normalized_dir = Vec::normalize(dir_light.direction());
    Vec half = Vec::normalize(normalized_dir + eyedirn);

    return compute_light(visibility, dir_light.light_color(), normalized_dir,
        intersection_info.normal, half);
}