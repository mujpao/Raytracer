#include "scene.h"

#include "intersectioninfo.h"
#include "shape.h"

bool Scene::intersect(const Ray &ray, double tolerance, IntersectionInfo & closest_hit_geo) const {
	IntersectionInfo local;
	double t;
	bool has_intersect = false;
	double t_closest = m_t_max;
	for (auto & obj : objects) {
		if (obj->intersect(ray, t, local)) {
			if (t > tolerance && t < t_closest) {
				t_closest = t;
				closest_hit_geo = local;
				has_intersect = true;
			}
		}
	}
	return has_intersect;
}
