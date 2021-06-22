#include "ray.h"

#include "camera.h"
#include "shape.h"
#include "scene.h"
#include "utils.h"

#include <iostream>

Ray::Ray(const Vec &origin, const Vec &direction, double t_min)
: m_origin(origin), m_direction(direction), m_t_min(t_min)
{
	if (!Utils::is_equal(m_origin[3] , 1.0)) {
		std::cout << "here"; // TODO warning
	}
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