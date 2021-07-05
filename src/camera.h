#ifndef CAMERA_H
#define CAMERA_H

#include "math/vec.h"

class Ray;

class Camera {
public:
    Camera() = default;
    // fov in degrees
    Camera(const Vec& eye, const Vec& center, const Vec& up, double fov,
        double aspect, double aperture = 0.0, double focus_dist = 1.0);

    // s and t = pct along image width and height
    Ray get_ray(double s, double t) const;

private:
    Vec m_eye;

    Vec m_u;
    Vec m_v;
    Vec m_w;

    Vec m_horizontal;
    Vec m_vertical;

    Vec m_top_left;

    double m_lens_radius;
};

#endif
