#ifndef SHAPE_H
#define SHAPE_H

#include "vec.h"
#include "mat4.h"

// TODO redesign interface

class Shape;

class IntersectionInfo {
public:
	IntersectionInfo();
	IntersectionInfo(Vec pos, Vec normal, Shape * s);

	// TODO make private
	Vec pos;
	Vec normal;
	Shape * shape_hit; // shape that is hit by the ray
	// TODO keep track of shape material instead of shape?
};

// tests intersections
class Shape {
public:
	virtual bool intersect(Ray& ray, float& thit, IntersectionInfo& local) = 0;
	virtual bool intersectP(Ray& ray) = 0; // TODO what does this do???
	Shape(Vec d, Vec s, Vec e, Vec a, float shiny);
	virtual ~Shape() = default;

	Vec diffuse, specular, emission, ambient;
	float shininess;
};

class Triangle : public Shape {
public:
	bool intersect(Ray& ray, float& thit, IntersectionInfo& local) override;
	bool intersectP(Ray& ray) override;
	Triangle(Vec p1, Vec p2, Vec p3, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny);

private:
	void barycentric(Vec p, float &u, float &v, float &w);
	Vec v1, v2, v3; // vertices
};

class Sphere : public Shape {
public:
	bool intersect(Ray& ray, float& thit, IntersectionInfo& local) override;
	bool intersectP(Ray& ray) override;
	Sphere(float cx, float cy, float cz, float r, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny);
	Vec center;
	float radius;
	Mat4 transformation, inverse, inverse_transpose;
};

#endif
