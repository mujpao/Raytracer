#include "shape.h"

#include "math/transform.h"
#include "ray.h"

#include <cmath>

IntersectionInfo::IntersectionInfo() {}

IntersectionInfo::IntersectionInfo(Vec pos, Vec normal, Shape * s)
: m_position(pos), m_normal(normal), m_shape_hit(s) {}


Shape::Shape(Vec d, Vec s, Vec e, Vec a, float shiny)
:  m_diffuse(d), m_specular(s), m_emission(e), ambient(a), m_shininess(shiny)
{}

bool Triangle::intersect(const Ray& ray, float& thit, IntersectionInfo& local) {
	Vec a = m_v1;
	Vec b = m_v2;
	Vec c = m_v3;

	Vec n = Vec::normalize(Transform::cross(b - a, c - a));
	
	float denom = Transform::dot(ray.direction(), n);
	if (denom == 0)
		return false;

	thit = (Transform::dot(a, n) - Transform::dot(ray.origin(), n)) / denom;

	// TODO inside triangle?

	local.m_position = ray.evaluate(thit);
	local.m_normal = n;
	local.m_shape_hit = this;

	float alpha, beta, gamma;
	barycentric(local.m_position, alpha, beta, gamma);

	if (alpha >= 0 && alpha <= 1 &&
		beta >= 0 && beta <= 1 &&
		gamma >= 0 && gamma <= 1)
		return true;


	return false;
}


bool Triangle::intersectP(Ray& ray) {
	Vec a = m_v1;
	Vec b = m_v2;
	Vec c = m_v3;

	Vec n = Vec::normalize(Transform::cross(b - a, c - a));

	float denom = Transform::dot(ray.direction(), n);
	if (denom == 0)
		return false;

	float thit;
	thit = (Transform::dot(a, n) - Transform::dot(ray.origin(), n)) / denom;


	Vec pos = ray.evaluate(thit);

	float alpha, beta, gamma;
	barycentric(pos, alpha, beta, gamma);

	if (alpha >= 0 && alpha <= 1 &&
		beta >= 0 && beta <= 1 &&
		gamma >= 0 && gamma <= 1)
		return true;


	return false;
}

Triangle::Triangle(Vec p1, Vec p2, Vec p3, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny)
: Shape(d, s, e, a, shiny), m_v1(t * p1), m_v2(t * p2), m_v3(t * p3) // apply transformation to vertices
{}

// from Real-Time Collision Detection
void Triangle::barycentric(Vec p, float &u, float &v, float &w)
{
	Vec a = m_v2 - m_v1;
	Vec b = m_v3 - m_v1;
	Vec c = p - m_v1;
	float d00 = Transform::dot(a, a);
	float d01 = Transform::dot(a, b);
	float d11 = Transform::dot(b, b);
	float d20 = Transform::dot(c, a);
	float d21 = Transform::dot(c, b);
	float denom = d00 * d11 - d01 * d01;
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	u = 1.0f - v - w;
}

bool Sphere::intersect(const Ray& ray, float& thit, IntersectionInfo& local) {
	float a, b, c, disc;
	Ray r2 = m_inverse * ray;

	a = Transform::dot(r2.direction(), r2.direction());
	b = 2 * Transform::dot(r2.direction(), r2.origin() - m_center);
	c = Transform::dot(r2.origin() - m_center, r2.origin() - m_center) - std::pow(m_radius, 2.0f);

	// check if discriminant < 0
	disc = std::pow(b, 2.0f) - 4.0f * a * c;

	if (disc < 0)
		return false;

	float t1, t2;

	t1 = (-b + std::sqrt(disc)) / (2.0f * a);
	t2 = (-b - std::sqrt(disc)) / (2.0f * a);

	if (t1 > 0 && t2 > 0) {
		if (t1 < t2)
			thit = t1;
		else
			thit = t2;
	}
	else if (t1 == t2) {
		thit = t1;
	}
	else if (t1 > 0 && t2 < 0) {
		thit = t1;
	}
	else if (t1 < 0 && t2 > 0) {
		thit = t2;
	}
	else {
		return false;
	}

	Vec untransformed_point = r2.evaluate(thit);
	Vec untransformed_normal = Vec::normalize(untransformed_point - m_center);

	local.m_position = m_transformation * untransformed_point;
	local.m_normal = Vec::normalize(m_inverse_transpose * untransformed_normal);
	local.m_shape_hit = this;

	return true;
}

bool Sphere::intersectP(Ray& ray) {
	float a, b, c, disc;

	Ray r2 = Transform::inverse(m_transformation) * ray;

	a = Transform::dot(r2.direction(), r2.direction());
	b = 2 * Transform::dot(r2.direction(), r2.origin() - m_center);
	c = Transform::dot(r2.origin() - m_center, r2.origin() - m_center) - std::pow(m_radius, 2.0f);

	// check if discriminant >= 0
	disc = std::pow(b, 2.0f) - 4.0f * a * c;
	return disc >= 0;
}

Sphere::Sphere(float cx, float cy, float cz, float r, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny)
: Shape(d, s, e, a, shiny), m_center(cx, cy, cz, 1.0), m_radius(r), m_transformation(t)
{
	m_inverse = Transform::inverse(m_transformation);
	m_inverse_transpose = Transform::transpose3x3(Transform::inverse3x3(m_transformation));
}
