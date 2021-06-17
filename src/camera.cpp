#include "camera.h"

#include "transform.h"
#include <cmath>

Camera::Camera()
: w(0), h(0), fovx(0.0f), fovy(0.0f) {}

void Camera::init(Vec new_eye, Vec new_center, Vec new_up, float fov, int new_w, int new_h) {
	eye = new_eye;
	center = new_center;
	up = new_up;
	w = new_w;
	h = new_h;

	// convert fov to radians, store in fovy
	fovy = fov * (float)(M_PI / 180.0);
	// calculate fovx in radians
	fovx = 2.0f * std::atan(std::tan(fovy / 2.0f) * ((float)w / (float)h));

	// construct coord frame (u_vec, v_vec, and w_vec)
	Vec a = eye - center;
	Vec b = up;
	w_vec = Vec::normalize(a);
	u_vec = Vec::normalize(Transform::cross(b, w_vec));
	v_vec = Transform::cross(w_vec, u_vec);
}
