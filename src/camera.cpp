#include "camera.h"

#include "math/transform.h"
#include "utils.h"
#include "ray.h"

#include <cmath>

Camera::Camera(const Vec &eye, const Vec &center, const Vec &up, double fov, int w, int h)
: m_eye(eye), m_center(center), m_up(up), m_width(w), m_height(h)
{
	double aspect = static_cast<double>(m_width) / m_height;
	m_fovy = Utils::deg2rad(fov);
	// m_fovx = 2.0 * std::atan(std::tan(m_fovy / 2.0) * aspect);

	double viewport_height = 2.0 * std::tan(m_fovy / 2.0);
	double viewport_width = viewport_height * aspect;

	Vec a = m_eye - m_center;
	Vec b = m_up;
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

// Ray Camera::ray_through_pixel_center(int i, int j) const {
// 	double alpha = std::tan(m_fovx / 2.0) * ((j + 0.5 - (m_width / 2.0)) / (m_width / 2.0));
// 	double beta = std::tan(m_fovy / 2.0) * (((m_height / 2.0) - (i + 0.5)) / (m_height / 2.0));

// 	Vec origin = Vec(m_eye.x(), m_eye.y(), m_eye.z(), 1.0);
// 	Vec direction = Vec::normalize(alpha * m_u + beta * m_v - m_w);

// 	return Ray(origin, direction);
// }
