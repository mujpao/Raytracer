#include "raytracer.h"

#include "camera.h"
#include "image.h"
#include "intersectioninfo.h"
#include "materials/material.h"
#include "math/transform.h"
#include "ray.h"
#include "scene.h"
#include "utils.h"

#include <chrono>
#include <iostream>

Raytracer::Raytracer(int max_depth, int num_samples, bool normals_only)
    : m_max_depth(max_depth), m_num_samples(num_samples),
      m_normals_only(normals_only) {}

Image Raytracer::raytrace(const Scene& scene, const Camera& camera,
    const std::size_t width, bool gamma_corrected) {

    const std::size_t height = width / camera.aspect();

    Image image(width, height);

    std::cout << "Tracing scene (" << width << "x" << height
              << " px, depth=" << m_max_depth << ", samples=" << m_num_samples
              << ")" << '\n';

    m_progress_indicator.start();

    auto start_time = std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < height; ++i) {
        for (std::size_t j = 0; j < width; ++j) {
            Vec color;
            if (m_num_samples == 1) {
                double u = static_cast<double>(j) / (width - 1);
                double v = static_cast<double>(i) / (height - 1);

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

        m_progress_indicator.increment(1.0 / height);
    }

    auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Finished in " << duration.count() << "s\n";

    return image;
}

void Raytracer::set_background_color(const Vec& color) {
    m_background_color = color;
}

Vec Raytracer::trace(const Ray& r, const Scene& scene, int depth) {
    if (depth < 1)
        return m_background_color;

    IntersectionInfo hit_info;
    if (scene.intersect(r, hit_info)) {
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
