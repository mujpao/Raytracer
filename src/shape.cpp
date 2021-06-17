#include "shape.h"

#include "math/transform.h"
#include "ray.h"

#include <cmath>

IntersectionInfo::IntersectionInfo() {}

IntersectionInfo::IntersectionInfo(Vec pos, Vec normal, Shape * s)
: pos(pos), normal(normal), shape_hit(s) {}


Shape::Shape(Vec d, Vec s, Vec e, Vec a, float shiny)
:  diffuse(d), specular(s), emission(e), ambient(a), shininess(shiny)
{}

bool Triangle::intersect(Ray& ray, float& thit, IntersectionInfo& local) {
	Vec a = v1;
	Vec b = v2;
	Vec c = v3;

	Vec n = Vec::normalize(Transform::cross(b - a, c - a));
	
	float denom = Transform::dot(ray.direction(), n);
	if (denom == 0)
		return false;

	thit = (Transform::dot(a, n) - Transform::dot(ray.origin(), n)) / denom;

	// TODO inside triangle?

	local.pos = ray.evaluate(thit);
	local.normal = n;
	local.shape_hit = this;

	float alpha, beta, gamma;
	barycentric(local.pos, alpha, beta, gamma);

	if (alpha >= 0 && alpha <= 1 &&
		beta >= 0 && beta <= 1 &&
		gamma >= 0 && gamma <= 1)
		return true;


	return false;
}


bool Triangle::intersectP(Ray& ray) {
	Vec a = v1;
	Vec b = v2;
	Vec c = v3;

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
: Shape(d, s, e, a, shiny), v1(t * p1), v2(t * p2), v3(t * p3) // apply transformation to vertices
{}

// from Real-Time Collision Detection
void Triangle::barycentric(Vec p, float &u, float &v, float &w)
{
	Vec a = v2 - v1;
	Vec b = v3 - v1;
	Vec c = p - v1;
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

bool Sphere::intersect(Ray& ray, float& thit, IntersectionInfo& local) {
	float a, b, c, disc;
	Ray r2 = inverse * ray;

	a = Transform::dot(r2.direction(), r2.direction());
	b = 2 * Transform::dot(r2.direction(), r2.origin() - center);
	c = Transform::dot(r2.origin() - center, r2.origin() - center) - std::pow(radius, 2.0f);

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
	Vec untransformed_normal = Vec::normalize(untransformed_point - center);

	local.pos = transformation * untransformed_point;
	local.normal = Vec::normalize(inverse_transpose * untransformed_normal);
	local.shape_hit = this;

	return true;
}

bool Sphere::intersectP(Ray& ray) {
	float a, b, c, disc;

	Ray r2 = Transform::inverse(transformation) * ray;

	a = Transform::dot(r2.direction(), r2.direction());
	b = 2 * Transform::dot(r2.direction(), r2.origin() - center);
	c = Transform::dot(r2.origin() - center, r2.origin() - center) - std::pow(radius, 2.0f);

	// check if discriminant >= 0
	disc = std::pow(b, 2.0f) - 4.0f * a * c;
	return disc >= 0;
}

Sphere::Sphere(float cx, float cy, float cz, float r, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny)
: Shape(d, s, e, a, shiny), center(cx, cy, cz, 1.0), radius(r), transformation(t)
{
	inverse = Transform::inverse(transformation);
	inverse_transpose = Transform::transpose3x3(Transform::inverse3x3(transformation));
}
