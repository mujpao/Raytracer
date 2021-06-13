#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec.h"
#include "mat4.h"

#include <vector>
#include <memory>
#include <iosfwd>

class Camera;
class Scene;
class LocalGeo;

// TODO redesign interface
class Ray {
public:
	Ray(Vec origin, Vec dir, double t_min = 0.0); //TODO should t_min and max be different depending on whether this is shadow ray?
	Ray();
	Ray(Camera cam, int i, int j); //ray through center of pixel i, j
	// TODO Only need to know eye pos

	inline Vec origin() const { return m_origin; }
	inline Vec direction() const { return m_direction; }
	inline double t_min() const { return m_t_min; }

	Vec evaluate(double t);

	// TODO move to scene class?
	bool intersect(Scene &s, float & t_closest, LocalGeo & closest_hit_geo);
	friend std::ostream& operator<<(std::ostream& os, const Ray& r);

private:
	Vec m_origin;
	Vec m_direction;
	
	double m_t_min = 0.0;
	double m_t_max = 10000.0;
};

class Shape;

class LocalGeo { // TODO change name to IntersectionInfo
public:
	LocalGeo();
	LocalGeo(Vec pos, Vec normal, Shape * s);

	// TODO make private
	Vec pos;
	Vec normal;
	Shape * shape_hit; // shape that is hit by the ray
	// TODO keep track of shape material instead of shape?
};

class Light {
public:
	virtual Vec calc_lighting(const Vec & eye, Scene & s, LocalGeo & local) = 0;
	Vec light_color;
	Light(Vec col);
	virtual ~Light() = default;

	Vec compute_light(float visible, Vec light_color, Vec dir, Vec normal, 
		Vec half, Vec diffuse, Vec specular, float shininess);

};

// Point Lights
class PointLight : public Light {
public:
	Vec calc_lighting(const Vec & eye, Scene & s, LocalGeo & local) override;
	Vec p;
	float atten_const = 1, atten_lin = 0, atten_quad = 0;
	PointLight(Vec atten, Vec col, Vec p);
};

// Directional Lights
class DirLight : public Light {
public:
	Vec calc_lighting(const Vec & eye, Scene & s, LocalGeo & local) override;
	Vec dir;
	DirLight(Vec col, Vec dir);
};

// tests intersections
class Shape {
public:
	virtual bool intersect(Ray& ray, float& thit, LocalGeo& local) = 0;
	virtual bool intersectP(Ray& ray) = 0; // TODO what does this do???
	Shape(Vec d, Vec s, Vec e, Vec a, float shiny);
	virtual ~Shape() = default;

	Vec diffuse, specular, emission, ambient;
	float shininess;
};

class Triangle : public Shape {
public:
	bool intersect(Ray& ray, float& thit, LocalGeo& local) override;
	bool intersectP(Ray& ray) override;
	Triangle(Vec p1, Vec p2, Vec p3, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny);

private:
	void barycentric(Vec p, float &u, float &v, float &w);
	Vec v1, v2, v3; // vertices
};

class Sphere : public Shape {
public:
	bool intersect(Ray& ray, float& thit, LocalGeo& local) override;
	bool intersectP(Ray& ray) override;
	Sphere(float cx, float cy, float cz, float r, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny);
	Vec center;
	float radius;
	Mat4 transformation, inverse, inverse_transpose;
};


class Scene {
public:
	std::vector<std::shared_ptr<Shape>> objects;
	std::vector<std::shared_ptr<Light>> lights;
};

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

class Image {
public:
	int w, h;
	Image(int w, int h);
	Image(const Image & i);
	~Image();
	// TODO change name to set_pixel_color()?
	void color_pixel(int i, int j, const unsigned char color[]);
	void save(std::string file); // TODO
	unsigned char * bytes;
};

class Raytracer {
public:
	Image raytrace(Camera cam, Scene scene);
	Raytracer(int max_depth);
private:
	// TODO change name to calc_intersection_color() or something...
	Vec trace(Ray r, Scene scene, int num_recs); // recursively determines the color of the intersection of ray with the scene
	int max_depth;
};
#endif