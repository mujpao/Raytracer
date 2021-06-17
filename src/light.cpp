#include "light.h"

#include "transform.h"
#include "utils.h"
#include "ray.h"
#include "shape.h"

#include <cmath>

Vec Light::compute_light(float visible, Vec light_color, Vec dir, Vec normal,
	Vec half, Vec diffuse, Vec specular, float shininess) {

	double ndotl = Transform::dot(dir, normal);
	double hdotn = Transform::dot(half, normal);

	Vec result = visible * light_color * (diffuse * std::max(ndotl, 0.0) + specular * std::pow(std::max(hdotn, 0.0), shininess));
	return result;
}

Light::Light(Vec col)
: light_color(col) {}

Vec PointLight::calc_lighting(const Vec & eye, Scene & s, IntersectionInfo & local) {
	// dist from light to pixel
	// TODO vector dist function
	float d = std::sqrt(std::pow(local.pos.x() - p.x(), 2) + std::pow(local.pos.y() - p.y(), 2) + std::pow(local.pos.z() - p.z(), 2));

	// create ray from pixel to light source
	Vec ray_dir = Vec::normalize(p - local.pos);
	ray_dir[3] = 0.0;
	Ray r(local.pos, ray_dir, Utils::EPSILON);

	// calculate attenuation
	Vec atten_light_color = light_color / (atten_const + atten_lin * d + atten_quad * std::pow(d, 2));

	// check if view to light is blocked
	float t, v;
	IntersectionInfo local2;
	if (r.intersect(s, t, local2) && t < d) // TODO what if light is between objects?
		v = 0.0f;
	else
		v = 1.0f;


	Vec dir = r.direction();
	Vec pos_vector(local.pos.x(), local.pos.y(), local.pos.z(), 1.0);
	Vec eyedirn = Vec::normalize(eye - pos_vector);
	Vec half = Vec::normalize(dir + eyedirn);

	return compute_light(v, atten_light_color, dir, local.normal, 
		half, local.shape_hit->diffuse, local.shape_hit->specular, local.shape_hit->shininess);
}

PointLight::PointLight(Vec atten, Vec col, Vec p)
: Light(col), p(p), atten_const(atten[0]), atten_lin(atten[1]), atten_quad(atten[2])
{}

Vec DirLight::calc_lighting(const Vec & eye, Scene & s, IntersectionInfo & local) {

	// create ray starting at pixel in dir of light source
	Ray r(Vec(local.pos.x(), local.pos.y(), local.pos.z(), 1.0), Vec::normalize(dir), Utils::EPSILON);

	// check if view to light is blocked
	float t, v;
	IntersectionInfo local2;
	if (r.intersect(s, t, local2))
		v = 0.0f;
	else
		v = 1.0f;

	Vec pos_vector(local.pos.x(), local.pos.y(), local.pos.z());
	Vec eyedirn = Vec::normalize(eye - pos_vector);
	Vec normalized_dir = Vec::normalize(dir);
	Vec half = Vec::normalize(normalized_dir + eyedirn);

	return compute_light(v, light_color, normalized_dir, local.normal,
		half, local.shape_hit->diffuse, local.shape_hit->specular, local.shape_hit->shininess);
}

DirLight::DirLight(Vec col, Vec dir)
: Light(col), dir(Vec::normalize(dir)) {}
