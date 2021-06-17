#ifndef LIGHT_H
#define LIGHT_H

#include "math/vec.h"

class Scene;
class IntersectionInfo;

// TODO redesign interface
class Light {
public:
	virtual Vec calc_lighting(const Vec & eye, Scene & s, IntersectionInfo & local) = 0;
	Vec light_color;
	Light(Vec col);
	virtual ~Light() = default;

	Vec compute_light(float visible, Vec light_color, Vec dir, Vec normal, 
		Vec half, Vec diffuse, Vec specular, float shininess);

};

// Point Lights
class PointLight : public Light {
public:
	Vec calc_lighting(const Vec & eye, Scene & s, IntersectionInfo & local) override;
	Vec p;
	float atten_const = 1, atten_lin = 0, atten_quad = 0;
	PointLight(Vec atten, Vec col, Vec p);
};

// Directional Lights
class DirLight : public Light {
public:
	Vec calc_lighting(const Vec & eye, Scene & s, IntersectionInfo & local) override;
	Vec dir;
	DirLight(Vec col, Vec dir);
};

#endif
