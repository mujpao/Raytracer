#ifndef LIGHT_H
#define LIGHT_H

#include "math/vec.h"

class Scene;
class IntersectionInfo;

// TODO redesign interface
class Light {
public:
	Light(const Vec &light_color);
	virtual ~Light() = default;

	virtual Vec calc_lighting(const Vec & eye, const Scene & scene, const IntersectionInfo & intersection_info) const = 0;

protected:
	// TODO light_color argument does what?
	// TODO change visible to visibility?
	Vec compute_light(float visible, const Vec & light_color, const Vec & direction, const Vec & normal, 
		const Vec & half, const Vec & diffuse, const Vec & specular, float shininess) const;

	inline const Vec& light_color() const { return m_light_color; }

private:
	Vec m_light_color;
};

class PointLight : public Light {
public:
	PointLight(const Vec &attenuation, const Vec &light_color, const Vec &position);

	Vec calc_lighting(const Vec & eye, const Scene & scene, const IntersectionInfo & intersection_info) const override;

private:
	Vec m_position;

	double m_atten_const = 1.0, m_atten_lin = 0.0, m_atten_quad = 0.0;
};

class DirLight : public Light {
public:
	DirLight(const Vec &light_color, const Vec &direction);

	Vec calc_lighting(const Vec & eye, const Scene & scene, const IntersectionInfo & intersection_info) const override;

private:
	Vec m_direction;
};

#endif
