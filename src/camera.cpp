#include "camera.h"

#include "math/transform.h"
#include "ray.h"
#include "utils.h"

#include <cmath>

Camera::Camera(const Vec& eye, const Vec& center, const Vec& up, double fov,
    double aspect, double aperture, double focus_dist)
    : m_eye(eye), m_lens_radius(aperture / 2.0) {
    double fovy = Utils::deg2rad(fov);

    double viewport_height = 2.0 * std::tan(fovy / 2.0);
    double viewport_width = viewport_height * aspect;

    Vec a = m_eye - center;
    Vec b = up;
    m_w = Vec::normalize(a);
    m_u = Vec::normalize(Transform::cross(b, m_w));
    m_v = Transform::cross(m_w, m_u);

    m_horizontal = focus_dist * viewport_width * m_u;
    m_vertical = focus_dist * -viewport_height * m_v;
    m_top_left
        = m_eye - m_horizontal / 2.0 - m_vertical / 2.0 - focus_dist * m_w;
}

Ray Camera::get_ray(double s, double t) const {
    Vec rd = m_lens_radius * Utils::random_in_unit_disk();
    Vec offset = m_u * rd.x() + m_v * rd.y();

    Vec origin = Vec::to_point(m_eye);
    return Ray(origin + offset,
        m_top_left + s * m_horizontal + t * m_vertical - origin - offset);
}
