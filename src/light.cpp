#include "light.h"

#include "math/transform.h"
#include "utils.h"
#include "ray.h"
#include "shape.h"

#include <cmath>

Light::Light(const Vec &light_color)
: m_light_color(light_color) {}

Vec Light::compute_light(float visible, const Vec & light_color, const Vec & direction, const Vec & normal, 
		const Vec & half, const Vec & diffuse, const Vec & specular, float shininess) {

	double ndotl = Transform::dot(direction, normal);
	double hdotn = Transform::dot(half, normal);

	Vec result = visible * light_color * (diffuse * std::max(ndotl, 0.0) + specular * std::pow(std::max(hdotn, 0.0), shininess));
	return result;
}

PointLight::PointLight(const Vec &attenuation, const Vec &light_color, const Vec &position)
: Light(light_color), m_position(position), m_atten_const(attenuation[0]), 
m_atten_lin(attenuation[1]), m_atten_quad(attenuation[2])
{}

Vec PointLight::calc_lighting(const Vec & eye, const Scene & scene, const IntersectionInfo & intersection_info) {
	// dist from light to pixel
	// TODO vector dist function
	float d = std::sqrt(std::pow(intersection_info.m_position.x() - m_position.x(), 2) + std::pow(intersection_info.m_position.y() - m_position.y(), 2) + std::pow(intersection_info.m_position.z() - m_position.z(), 2));

	// create ray from pixel to light source
	Vec ray_dir = Vec::normalize(m_position - intersection_info.m_position);
	ray_dir[3] = 0.0;
	Ray r(intersection_info.m_position, ray_dir, Utils::EPSILON);

	// calculate attenuation
	Vec atten_light_color = light_color() / (m_atten_const + m_atten_lin * d + m_atten_quad * std::pow(d, 2));

	// check if view to light is blocked
	float t, v;
	IntersectionInfo local;
	if (r.intersect(scene, t, local) && t < d) // TODO what if light is between objects?
		v = 0.0f;
	else
		v = 1.0f;


	Vec dir = r.direction();
	Vec pos_vector(intersection_info.m_position.x(), intersection_info.m_position.y(), intersection_info.m_position.z(), 1.0);
	Vec eyedirn = Vec::normalize(eye - pos_vector);
	Vec half = Vec::normalize(dir + eyedirn);

	return compute_light(v, atten_light_color, dir, intersection_info.m_normal, 
		half, intersection_info.m_shape_hit->m_diffuse, intersection_info.m_shape_hit->m_specular, intersection_info.m_shape_hit->m_shininess);
}

DirLight::DirLight(const Vec &light_color, const Vec &direction)
: Light(light_color), m_direction(Vec::normalize(direction)) {}

Vec DirLight::calc_lighting(const Vec & eye, const Scene & scene, const IntersectionInfo & intersection_info) {

	// create ray starting at pixel in dir of light source
	Ray r(Vec(intersection_info.m_position.x(), intersection_info.m_position.y(), intersection_info.m_position.z(), 1.0), Vec::normalize(m_direction), Utils::EPSILON);

	// check if view to light is blocked
	float t, v;
	IntersectionInfo local;
	if (r.intersect(scene, t, local))
		v = 0.0f;
	else
		v = 1.0f;

	Vec pos_vector(intersection_info.m_position.x(), intersection_info.m_position.y(), intersection_info.m_position.z());
	Vec eyedirn = Vec::normalize(eye - pos_vector);
	Vec normalized_dir = Vec::normalize(m_direction);
	Vec half = Vec::normalize(normalized_dir + eyedirn);

	return compute_light(v, light_color(), normalized_dir, intersection_info.m_normal,
		half, intersection_info.m_shape_hit->m_diffuse, intersection_info.m_shape_hit->m_specular, intersection_info.m_shape_hit->m_shininess);
}

