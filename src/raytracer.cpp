#include "raytracer.h"

#include "camera.h"
#include "scene.h"
#include "image.h"
#include "ray.h"
#include "shape.h"
#include "light.h"
#include "math/transform.h"
#include "utils.h"


Image Raytracer::raytrace(Camera cam, Scene scene) {
	Image image(cam.w, cam.h);
	int i, j, k;
	// const unsigned char red[] = { 255, 0, 0 };
	// const unsigned char green[] = { 0, 255, 0 };
	// const unsigned char blue[] = { 0, 0, 255 };
	// const unsigned char black[] = { 0, 0, 0 };
	unsigned char color[3];

	//float t;
	//LocalGeo local;

	Vec pixel_color;

	for (i = 0; i < cam.h; ++i) {
		for (j = 0; j < cam.w; ++j) {

			Ray ray(cam, i, j);
			
			pixel_color = trace(ray, scene, 0); // TODO start at 0 or 1?

			for (k = 0; k < 3; ++k) {
				// change pixel_color to range 0 to 255
				// make sure new values are not greater than 255
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

Raytracer::Raytracer(int max_depth) : max_depth(max_depth) {}

Vec Raytracer::trace(Ray r, Scene scene, int num_recs) {
	Vec color(0.0f, 0.0f, 0.0f);

	if (num_recs > max_depth)
		return color;

	float t;
	IntersectionInfo local;

	// TODO is t used?
	if (!r.intersect(scene, t, local))
		return color;

	
	// Illumination model
	color = local.shape_hit->ambient + local.shape_hit->emission;
	for (auto & light : scene.lights) {
		color += light->calc_lighting(r.origin(), scene, local);
	}

	// Reflected ray
	Vec reflected_dir = r.direction() - 2.0f * Transform::dot(r.direction(), local.normal) * local.normal;
	Ray reflected_ray(local.pos, reflected_dir, Utils::EPSILON);

	color = color + local.shape_hit->specular * trace(reflected_ray, scene, num_recs + 1);

	return color;
}
