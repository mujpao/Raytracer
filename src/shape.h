#ifndef SHAPE_H
#define SHAPE_H

#include "math/vec.h"
#include "math/mat4.h"

// TODO redesign interface

class Shape;

class IntersectionInfo {
public:
	IntersectionInfo();
	IntersectionInfo(Vec pos, Vec normal, Shape * s);

	// TODO make private
	Vec m_position;
	Vec m_normal;
	Shape * m_shape_hit; // shape that is hit by the ray
	// TODO keep track of shape material instead of shape?
};

// tests intersections
class Shape {
public:
	virtual bool intersect(const Ray& ray, float& thit, IntersectionInfo& local) = 0;
	virtual bool intersectP(Ray& ray) = 0; // TODO what does this do???
	Shape(Vec d, Vec s, Vec e, Vec a, float shiny);
	virtual ~Shape() = default;

	// TODO
	Vec m_diffuse, m_specular, m_emission, ambient;
	float m_shininess;
};

class Triangle : public Shape {
public:
	bool intersect(const Ray& ray, float& thit, IntersectionInfo& local) override;
	bool intersectP(Ray& ray) override;
	Triangle(Vec p1, Vec p2, Vec p3, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny);

private:
	void barycentric(Vec p, float &u, float &v, float &w);
	Vec m_v1, m_v2, m_v3; // vertices
};

class Sphere : public Shape {
public:
	bool intersect(const Ray& ray, float& thit, IntersectionInfo& local) override;
	bool intersectP(Ray& ray) override;
	Sphere(float cx, float cy, float cz, float r, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny);
private:
	Vec m_center;
	float m_radius;
	Mat4 m_transformation, m_inverse, m_inverse_transpose;
};

#endif