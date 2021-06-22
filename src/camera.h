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

	Ray ray_through_pixel_center(int i, int j) const;

private:
	Vec m_eye;
	Vec m_center;
	Vec m_up;
	Vec m_u;
	Vec m_v;
	Vec m_w;
	int m_width, m_height;
	double m_fovx, m_fovy; // store in radians
};

#endif
