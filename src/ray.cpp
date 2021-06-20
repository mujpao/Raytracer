#include "ray.h"

#include "camera.h"
#include "shape.h"
#include "scene.h"
#include "utils.h"

#include <iostream>
#include <cmath>

Ray::Ray(const Vec &origin, const Vec &dir, double t_min)
: m_origin(origin), m_direction(dir), m_t_min(t_min)
{
	if (!Utils::is_equal(m_origin[3] , 1.0)) {
		std::cout << "here"; // TODO warning
	}
}

Ray::Ray()
: m_origin(Vec(0.0, 0.0, 0.0, 0.0)), m_direction(Vec(0.0, 0.0, 0.0)), m_t_min(0.0)
{}

Ray::Ray(const Camera &cam, int i, int j)
: m_t_min(0.0)
{
	m_origin = cam.eye;
	m_origin[3] = 1.0;

	float alpha = std::tan(cam.fovx / 2.0) * ((j + 0.5 - (cam.w / 2.0)) / (cam.w / 2.0));
	float beta = std::tan(cam.fovy / 2.0) * (((cam.h/ 2.0) - (i + 0.5)) / (cam.h / 2.0));

	m_direction = Vec::normalize(alpha * cam.u_vec + beta * cam.v_vec - cam.w_vec);
}

Vec Ray::evaluate(double t) const {
	Vec result = m_origin + m_direction * t;
	result[3] = 1.0;
	return result;
}

bool Ray::intersect(const Scene &s, float & t_closest, IntersectionInfo & closest_hit_geo) const {
	IntersectionInfo local;
	float t;
	bool has_intersect = false;
	t_closest = m_t_max;
	for (auto & obj : s.objects) {
		if (obj->intersect(*this, t, local)) {
			
			// make sure intersection is a certain distance past object surface
			if (t > m_t_min && t < t_closest) {
				t_closest = t;
				closest_hit_geo = local;
				has_intersect = true;
			}
		}
	}
	return has_intersect;
}

std::ostream& operator<<(std::ostream& os, const Ray& r) {
	os << r.m_origin << " + " << r.m_direction << " * t";
	return os;
}