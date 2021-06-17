#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

class Camera {
public:
	Vec eye;
	Vec center;
	Vec up;
	Vec u_vec;
	Vec v_vec;
	Vec w_vec;
	int w, h;
	float fovx, fovy; // stored in radians
	Camera();
	void init(Vec new_eye, Vec new_center, Vec new_up, float fov, int new_w, int new_h); // assume fov input is in degrees
};

#endif
