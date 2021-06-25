#include "raytracer.h"

#include "camera.h"
#include "scene.h"
#include "image.h"
#include "ray.h"
#include "shape.h"
#include "light.h"
#include "math/transform.h"
#include "utils.h"

Raytracer::Raytracer(int max_depth, bool normals_only) : m_max_depth(max_depth), m_normals_only(normals_only) {}

Image Raytracer::raytrace(const Camera &camera, const Scene &scene) {
	Image image(camera.width(), camera.height());
	int i, j, k;
	// const unsigned char red[] = { 255, 0, 0 };
	// const unsigned char green[] = { 0, 255, 0 };
	// const unsigned char blue[] = { 0, 0, 255 };
	// const unsigned char black[] = { 0, 0, 0 };
	unsigned char color[3];

	Vec pixel_color;

	for (i = 0; i < camera.height(); ++i) {
		for (j = 0; j < camera.width(); ++j) {

			Ray ray = camera.ray_through_pixel_center(i, j);
			
			pixel_color = trace(ray, scene, 0); // TODO start at 0 or 1?

			for (k = 0; k < 3; ++k) {
				int new_color = (int)(pixel_color[k] * 255.0f);
				if (new_color > 255)
					new_color = 255;
				color[k] = (unsigned char)new_color;
			}

			image.set_pixel_color(i, j, color);
		}
	}

	return image;
}

Vec Raytracer::trace(const Ray &r, const Scene &scene, int num_recs) {
	Vec color(0.0, 0.0, 0.0);

	if (num_recs > m_max_depth)
		return color;

	float t;
	IntersectionInfo local;

	// TODO is t used?
	if (!r.intersect(scene, t, local))
		return color;
	
	if (m_normals_only) {
		color = 0.5 * (local.m_normal + Vec(1.0, 1.0, 1.0));
	} else {
		// Illumination model
		color = local.m_shape_hit->ambient + local.m_shape_hit->m_emission;
		for (const auto &light : scene.lights) {
			color += light->calc_lighting(r.origin(), scene, local);
		}

		// Reflected ray
		Vec reflected_dir = r.direction() - 2.0 * Transform::dot(r.direction(), local.m_normal) * local.m_normal;
		Ray reflected_ray(local.m_position, reflected_dir, Utils::EPSILON);

		color = color + local.m_shape_hit->m_specular * trace(reflected_ray, scene, num_recs + 1);
	}	

	return color;
}