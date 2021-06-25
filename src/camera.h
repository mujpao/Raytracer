#ifndef CAMERA_H
#define CAMERA_H

#include "math/vec.h"

class Ray;

class Camera {
public:
	Camera() = default;
	// fov in degrees
	Camera(const Vec &eye, const Vec &center, const Vec &up, double fov, int w, int h);

	inline int width() const { return m_width; }
	inline int height() const { return m_height; }

	// s and t = pct along image width and height
	Ray get_ray(double s, double t) const;

	Ray ray_through_pixel_center(int i, int j) const;

private:
	Vec m_eye;
	Vec m_center; // TODO remove center and up?
	Vec m_up;
	Vec m_u;
	Vec m_v;
	Vec m_w;

	Vec m_horizontal;
	Vec m_vertical;

	int m_width, m_height;
	double m_fovx, m_fovy; // store in radians

	Vec m_top_left; 
};

#endif
