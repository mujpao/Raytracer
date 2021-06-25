#include "camera.h"

#include "math/transform.h"
#include "utils.h"
#include "ray.h"

#include <cmath>

Camera::Camera(const Vec &eye, const Vec &center, const Vec &up, double fov, int w, int h)
: m_eye(eye), m_width(w), m_height(h)
{
	double aspect = static_cast<double>(m_width) / m_height;
	double fovy = Utils::deg2rad(fov);

	double viewport_height = 2.0 * std::tan(fovy / 2.0);
	double viewport_width = viewport_height * aspect;

	Vec a = m_eye - center;
	Vec b = up;
	m_w = Vec::normalize(a);
	m_u = Vec::normalize(Transform::cross(b, m_w));
	m_v = Transform::cross(m_w, m_u);

	m_horizontal = viewport_width * m_u;
	m_vertical = -viewport_height * m_v;
	m_top_left = m_eye - m_horizontal / 2.0 - m_vertical / 2.0 - m_w;
}

Ray Camera::get_ray(double s, double t) const {
	Vec origin = Vec(m_eye.x(), m_eye.y(), m_eye.z(), 1.0);
	Vec direction = m_top_left + s * m_horizontal + t * m_vertical - origin;

	return Ray(origin, direction);
}
