#include "raytracer.h"

#include "camera.h"
#include "image.h"
#include "intersectioninfo.h"
#include "materials/material.h"
#include "ray.h"
#include "scene.h"
#include "threadpool.h"
#include "utils.h"

#include <chrono>
#include <iostream>

Raytracer::Raytracer(int max_depth, int num_samples, bool normals_only)
    : m_max_depth(max_depth), m_num_samples(num_samples),
      m_normals_only(normals_only) {}

Image Raytracer::raytrace(const Scene& scene, const Camera& camera,
    const std::size_t width, bool gamma_corrected, unsigned int num_threads) {

    const std::size_t height = width / camera.aspect();

    std::cout << "Tracing scene (" << width << "x" << height
              << " px, depth=" << m_max_depth << ", samples=" << m_num_samples
              << ", threads=" << num_threads << ")" << '\n';

    m_progress_indicator.start();

    auto start_time = std::chrono::steady_clock::now();

    std::vector<std::vector<Vec>> colors(
        height, std::vector<Vec>(width, Vec()));

    ThreadPool pool(num_threads);
    for (std::size_t i = 0; i < height; ++i) {
        pool.execute(
            [&, i]() { trace_row(i, scene, camera, width, height, colors); });
    }

    pool.join();

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Finished in " << duration.count() << "s\n";

    Image image(width, height);
    for (std::size_t i = 0; i < height; ++i) {
        for (std::size_t j = 0; j < width; ++j) {
            image.set_pixel_color(
                i, j, Utils::clamp(colors[i][j], 0.0, 1.0), gamma_corrected);
        }
    }

    return image;
}

void Raytracer::trace_row(std::size_t row, const Scene& scene,
    const Camera& camera, std::size_t width, std::size_t height,
    std::vector<std::vector<Vec>>& colors) {
    for (std::size_t j = 0; j < width; ++j) {
        if (m_num_samples == 1) {
            double u = static_cast<double>(j) / (width - 1);
            double v = static_cast<double>(row) / (height - 1);

            Ray ray = camera.get_ray(u, v);
            colors[row][j] = trace(ray, scene, m_max_depth);
        } else {
            for (int k = 0; k < m_num_samples; ++k) {
                double u = (j + Utils::random_double(0.0, 1.0)) / (width - 1);
                double v
                    = (row + Utils::random_double(0.0, 1.0)) / (height - 1);

                Ray ray = camera.get_ray(u, v);
                colors[row][j] += trace(ray, scene, m_max_depth);
            }
            colors[row][j] /= m_num_samples;
        }
    }

    m_progress_indicator.increment(1.0 / height);
}

Vec Raytracer::trace(const Ray& r, const Scene& scene, int depth) const {
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
