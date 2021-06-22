#include "camera.h"

#include "math/transform.h"
#include "utils.h"
#include "ray.h"

#include <cmath>

Camera::Camera(const Vec &eye, const Vec &center, const Vec &up, double fov, int w, int h)
: m_eye(eye), m_center(center), m_up(up), m_width(w), m_height(h)
{
	m_fovy = Utils::deg2rad(fov);
	m_fovx = 2.0 * std::atan(std::tan(m_fovy / 2.0) * (static_cast<double>(m_width) / static_cast<double>(m_height)));

	Vec a = m_eye - m_center;
	Vec b = m_up;
	m_w = Vec::normalize(a);
	m_u = Vec::normalize(Transform::cross(b, m_w));
	m_v = Transform::cross(m_w, m_u);
}

Ray Camera::ray_through_pixel_center(int i, int j) const {
	double alpha = std::tan(m_fovx / 2.0) * ((j + 0.5 - (m_width / 2.0)) / (m_width / 2.0));
	double beta = std::tan(m_fovy / 2.0) * (((m_height / 2.0) - (i + 0.5)) / (m_height / 2.0));

	Vec origin = Vec(m_eye.x(), m_eye.y(), m_eye.z(), 1.0);
	Vec direction = Vec::normalize(alpha * m_u + beta * m_v - m_w);

	return Ray(origin, direction);
}
