#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <memory>
#include <iosfwd>

const float EPSILON = 1.0f / 1000.0f;

class Vec;

class Point {
public:
	Point();
	Point(float x, float y, float z);
	Vec operator+(const Vec & v); // return type?
	Vec operator-(const Vec & v);
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
	Vec to_vec();

	float x, y, z;
	float w = 1; // w?
};

class Vec {
public:
	Vec();
	Vec(float x, float y, float z);
	Vec(float x, float y, float z, float w);
	Vec(Point a, Point b); // vector with tail at a and tip at b
	
	Point to_point();

	float& operator[](int idx);
	const float operator[](int idx) const;

	static Vec normalize(const Vec & v);

	Vec& operator+=(const Vec& rhs);
	Vec& operator-=(const Vec& rhs);
	Vec& operator*=(const Vec& rhs);

	Vec& operator*=(float scalar);
	Vec& operator/=(float scalar);


	friend Vec operator+(Vec lhs, const Vec & rhs);
	friend Vec operator-(Vec lhs, const Vec & rhs);

 	// Component-wise multiplication
	friend Vec operator*(Vec lhs, const Vec & rhs);

	// Scalar operations
	friend Vec operator*(Vec v, float scalar);
	friend Vec operator*(float scalar, Vec v);
	friend Vec operator/(Vec v, float scalar);

	friend std::ostream& operator<<(std::ostream& os, const Vec& v);

	// TODO make private
	// TODO store x y and z as array?
	float x, y, z;
	float w = 0;
};

class Camera;
class Scene;
class LocalGeo;

class Ray {
public:
	Ray(Point origin, Vec dir, float t_min); //TODO should t_min and max be different depending on whether this is shadow ray?
	Ray();
	Ray(Camera cam, int i, int j); //ray through center of pixel i, j

	Vec evaluate(float t);
	bool intersect(Scene &s, float & t_closest, LocalGeo & closest_hit_geo);
	friend std::ostream& operator<<(std::ostream& os, const Ray& r);

	Point origin;
	Vec dir;
	float t_min = 0.0f, t_max = 10000.0f; // maximum possible value. fixed for now
};

class Mat3 {
public:
	Mat3(float m[3][3]);
	Mat3(float val); // sets diagonal to value
	Mat3(); // initializes all elements to 0
	// todo should it initialize to identity matrix?

	Mat3& operator+=(const Mat3& rhs);
	Mat3& operator-=(const Mat3& rhs);

	Mat3& operator*=(float scalar);

	friend Mat3 operator+(Mat3 lhs, const Mat3 & rhs);
	friend Mat3 operator-(Mat3 lhs, const Mat3 & rhs);

	friend Mat3 operator*(Mat3 m, float scalar);
	friend Mat3 operator*(float scalar, Mat3 m);

	// TODO
	float mat[3][3];
};

class Mat4 {
public:
	Mat4(float m[4][4]);
	Mat4(float val); // sets diagonal to value, sets m[3][3] to 1.0f
	Mat4(); // initializes all elements to 0, sets m[3][3] to 1.0f
	Mat4(const Mat3 &other); // initializes with 3x3 matrix, sets fourth row and column to 0 0 0 1

	Mat4& operator+=(const Mat4& rhs);
	Mat4& operator-=(const Mat4& rhs);
	Mat4& operator*=(const Mat4& rhs);


	Mat4& operator*=(float scalar);

	friend Mat4 operator+(Mat4 lhs, const Mat4 & rhs);
	friend Mat4 operator-(Mat4 lhs, const Mat4 & rhs);
	friend Mat4 operator*(Mat4 lhs, const Mat4 & rhs);

	friend Mat4 operator*(Mat4 m, float scalar);
	friend Mat4 operator*(float scalar, Mat4 m);



	// Mat4 operator+(const Mat4& other);
	// Mat4 operator-(const Mat4& other);
	// Mat4 operator*(const Mat4& other);

	// Mat4 operator*(float scalar);
	// friend Mat4 operator*(float scalar, Mat4 m);

	friend Point operator*(const Mat4 & m, const Point & p);
	friend Vec operator*(const Mat4 & m, const Vec & v);
	friend Ray operator*(const Mat4 & m, const Ray & r);

	float mat[4][4]; // TODO
};

class Shape;

class LocalGeo {
public:
	LocalGeo();
	LocalGeo(Point pos, Vec normal, Shape * s);
	Point pos;
	Vec normal;
	Shape * shape_hit; // shape that is hit by the ray
};

class Light {
public:
	virtual Vec calc_lighting(const Vec & eye, Scene & s, LocalGeo & local) = 0;
	Vec light_color;
	Light(Vec col);
	Vec compute_light(float visible, Vec light_color, Vec dir, Vec normal, 
		Vec half, Vec diffuse, Vec specular, float shininess);

};

// Point Lights
class PointLight : public Light {
public:
	Vec calc_lighting(const Vec & eye, Scene & s, LocalGeo & local) override;
	Point p;
	float atten_const = 1, atten_lin = 0, atten_quad = 0;
	PointLight(Vec atten, Vec col, Point p);
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
	virtual bool intersectP(Ray& ray) = 0;
	Shape(Vec d, Vec s, Vec e, Vec a, float shiny);

	Vec diffuse, specular, emission, ambient;
	float shininess;
};

class Triangle : public Shape {
public:
	bool intersect(Ray& ray, float& thit, LocalGeo& local) override;
	bool intersectP(Ray& ray) override;
	Triangle(Point p1, Point p2, Point p3, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny);

private:
	void barycentric(Point p, float &u, float &v, float &w);
	Point v1, v2, v3; // vertices
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
	void color_pixel(int i, int j, const unsigned char color[]);
	void save(std::string file);
	unsigned char * bytes;
};

class Raytracer {
public:
	Image raytrace(Camera cam, Scene scene);
	Raytracer(int max_depth);
private:
	Vec trace(Ray r, Scene scene, int num_recs); // recursively determines the color of the intersection of ray with the scene
	int max_depth;
};
#endif