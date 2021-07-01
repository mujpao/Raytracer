#include "raytracer.h"

#include "camera.h"
#include "image.h"
#include "intersectioninfo.h"
#include "materials/material.h"
#include "math/transform.h"
#include "ray.h"
#include "scene.h"
#include "utils.h"

Raytracer::Raytracer(int max_depth, int num_samples, bool normals_only)
    : m_max_depth(max_depth), m_num_samples(num_samples),
      m_normals_only(normals_only) {}

Image Raytracer::raytrace(
    const Camera& camera, const Scene& scene, bool gamma_corrected) {
    Image image(camera.width(), camera.height());

    for (std::size_t i = 0; i < image.height(); ++i) {
        for (std::size_t j = 0; j < image.width(); ++j) {
            Vec color;
            if (m_num_samples == 1) {
                double u = static_cast<double>(j) / (image.width() - 1);
                double v = static_cast<double>(i) / (image.height() - 1);
                Ray ray = camera.get_ray(u, v);

                color = trace(ray, scene, m_max_depth);

            } else {
                for (int k = 0; k < m_num_samples; ++k) {
                    double u = (j + Utils::random_double(0.0, 1.0))
                        / (image.width() - 1);
                    double v = (i + Utils::random_double(0.0, 1.0))
                        / (image.height() - 1);
                    Ray ray = camera.get_ray(u, v);

                    color += trace(ray, scene, m_max_depth);
                }
                color /= m_num_samples;
            }

            image.set_pixel_color(
                i, j, Utils::clamp(color, 0.0, 1.0), gamma_corrected);
        }
    }

    return image;
}

void Raytracer::set_background_color(const Vec& color) {
    m_background_color = color;
}

Vec Raytracer::trace(const Ray& r, const Scene& scene, int depth) {
    if (depth < 1)
        return m_background_color;

    IntersectionInfo hit_info;
    if (scene.intersect(r, Utils::RAY_HIT_TOLERANCE, hit_info)) {
        if (m_normals_only) {
            return 0.5 * (hit_info.normal + Vec(1.0, 1.0, 1.0));
        } else {
            Vec color = hit_info.material->base_shade(r, hit_info, scene);
            Vec atten_factor;
            Ray scattered;
            if (hit_info.material->calc_scattered_ray(
                    r, hit_info, atten_factor, scattered)) {
                color += atten_factor * trace(scattered, scene, depth - 1);
            }
            return color;
        }
    } else {
        return m_background_color;
    }
}
