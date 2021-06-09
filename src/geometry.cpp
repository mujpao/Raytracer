#include "geometry.h"

#include "transform.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb_image_write.h"

#include <algorithm>
#include <iostream>



Point::Point() : x(0.0f), y(0.0f), z(0.0f) {}

Point::Point(float x, float y, float z)
: x(x), y(y), z(z)
{
}
Vec Point::operator+(const Vec & v) {
	Vec result(x + v.x, y + v.y, z + v.z);
	return result;
}
Vec Point::operator-(const Vec & v) {
	Vec result(x - v.x, y - v.y, z - v.z);
	return result;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << "(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
	return os;
}

Vec Point::to_vec() {
	return Vec(x, y, z, 0);
}

Vec::Vec() : x(0.0f), y(0.0f), z(0.0f) {}

Vec::Vec(float x, float y, float z)
: x(x), y(y), z(z)
{
}

Vec::Vec(float x, float y, float z, float w)
: x(x), y(y), z(z), w(w)
{
}

Vec::Vec(Point a, Point b)
: x(b.x - a.x), y(b.y - a.y), z(b.z - a.z)
{
}

Vec& Vec::operator+=(const Vec& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec& Vec::operator-=(const Vec& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vec& Vec::operator*=(const Vec& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vec& Vec::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vec& Vec::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vec operator+(Vec lhs, const Vec & rhs) {
	lhs += rhs;
	return lhs;
}

Vec operator-(Vec lhs, const Vec & rhs) {
	lhs -= rhs;
	return lhs;
}

Vec operator*(Vec lhs, const Vec & rhs) {
	lhs *= rhs;
	return lhs;
}

Vec operator*(Vec v, float scalar) {
	v *= scalar;
	return v;
}

Vec operator*(float scalar, Vec v) {
	v *= scalar;
	return v;
}

Vec operator/(Vec v, float scalar) {
	v /= scalar;
	return v;
}

std::ostream& operator<<(std::ostream& os, const Vec& v) {
	os << "<" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ">";
	return os;
}

Point Vec::to_point() {
	return Point(x, y, z);
}

float& Vec::operator[](int idx) {
	switch (idx) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		return x; // TODO throw exception?
		break;
	}
}


const float Vec::operator[](int idx) const {
	switch (idx) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		return x; // TODO throw exception?
		break;
	}
}


Vec Vec::normalize(const Vec & v) {
	float mag = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	Vec result = v / mag;
	return result;
}

// constructs a ray, normalizing dir
Ray::Ray(Point origin, Vec dir, float t_min)
: origin(origin), dir(Vec::normalize(dir)), t_min(t_min)
{}

Ray::Ray()
: origin(Point(0.0f, 0.0f, 0.0f)), dir(Vec(0.0f, 0.0f, 0.0f)), 
	t_min(0.0f)
{
}

Ray::Ray(Camera cam, int i, int j)
{
	origin.x = cam.eye.x;
	origin.y = cam.eye.y;
	origin.z = cam.eye.z;

	float alpha = tan(cam.fovx / 2.0f) * ((j + 0.5f - (cam.w / 2.0f)) / (cam.w / 2.0f));
	float beta = tan(cam.fovy / 2.0f) * (((cam.h/ 2.0f) - (i + 0.5f)) / (cam.h / 2.0f));

	dir = Vec::normalize(alpha * cam.u_vec + beta * cam.v_vec - cam.w_vec);
	t_min = 0.0f;
}

Vec Ray::evaluate(float t) {
	return origin + dir * t;
}

bool Ray::intersect(Scene &s, float & t_closest, LocalGeo & closest_hit_geo) {
	LocalGeo local;
	float t;
	bool has_intersect = false;
	t_closest = t_max;
	for (auto & obj : s.objects) {
		if (obj->intersect(*this, t, local)) {
			// make sure intersection is a certain distance past object surface
			if (t > t_min && t < t_closest) {
				t_closest = t;
				closest_hit_geo = local;
				has_intersect = true;
			}
		}
	}
	return has_intersect;
}

std::ostream& operator<<(std::ostream& os, const Ray& r) {
	os << r.origin << " + " << r.dir << " * t";
	return os;
}

Mat3::Mat3(float m[3][3]) {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			mat[i][j] = m[i][j];
	}
}

Mat3::Mat3(float val) {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			mat[i][j] = 0.0f;
	}
	mat[0][0] = val;
	mat[1][1] = val;
	mat[2][2] = val;
}

Mat3::Mat3() {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			mat[i][j] = 0.0f;
	}
}

Mat3& Mat3::operator+=(const Mat3& rhs) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			mat[i][j] += rhs.mat[i][j];
		}
	}

	return *this;
}

Mat3& Mat3::operator-=(const Mat3& rhs) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			mat[i][j] -= rhs.mat[i][j];
		}
	}

	return *this;
}

Mat3& Mat3::operator*=(float scalar) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			mat[i][j] *= scalar;
		}
	}

	return *this;
}

Mat3 operator+(Mat3 lhs, const Mat3 & rhs) {
	lhs += rhs;
	return lhs;
}

Mat3 operator-(Mat3 lhs, const Mat3 & rhs) {
	lhs -= rhs;
	return lhs;
}

Mat3 operator*(Mat3 m, float scalar) {
	m *= scalar;
	return m;
}

Mat3 operator*(float scalar, Mat3 m) {
	m *= scalar;
	return m;
}

Mat4::Mat4(float m[4][4])
{
	int i, j;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j)
			mat[i][j] = m[i][j];
	}
}

Mat4::Mat4(float val)
{
	int i, j;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j)
			mat[i][j] = 0.0f;
	}
	mat[0][0] = val;
	mat[1][1] = val;
	mat[2][2] = val;
	mat[3][3] = 1.0f;
}

Mat4::Mat4()
{
	int i, j;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j)
			mat[i][j] = 0.0f;
	}

	mat[3][3] = 1.0f;
}

Mat4::Mat4(const Mat3 &other) {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			mat[i][j] = other.mat[i][j];
	}

	// set fourth row and column
	for (i = 0; i < 3; ++i) {
		mat[i][3] = 0.0f;
		mat[3][i] = 0.0f;
	}

	mat[3][3] = 1.0f;
}

Mat4& Mat4::operator+=(const Mat4& rhs) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] += rhs.mat[i][j];
		}
	}

	return *this;
}

Mat4& Mat4::operator-=(const Mat4& rhs) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] -= rhs.mat[i][j];
		}
	}

	return *this;
}

Mat4& Mat4::operator*=(const Mat4& rhs) {
	Mat4 result;

	int i, j, k;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			result.mat[i][j] = 0;
			for (k = 0; k < 4; ++k) {
				result.mat[i][j] += mat[i][k] * rhs.mat[k][j];
			}
		}
	}

	// TODO copy constructor
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] = result.mat[i][j];
		}
	}
	return *this;
}

Mat4& Mat4::operator*=(float scalar) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] *= scalar;
		}
	}

	return *this;
}

Mat4 operator+(Mat4 lhs, const Mat4 & rhs) {
	lhs += rhs;
	return lhs;
}

Mat4 operator-(Mat4 lhs, const Mat4 & rhs) {
	lhs -= rhs;
	return lhs;
}

Mat4 operator*(Mat4 lhs, const Mat4 & rhs) {
	lhs *= rhs;
	return lhs;
}

Mat4 operator*(Mat4 m, float scalar) {
	m *= scalar;
	return m;
}

Mat4 operator*(float scalar, Mat4 m) {
	m *= scalar;
	return m;
}


// Mat4 Mat4::operator+(const Mat4 & other) {
// 	Mat4 result;

// 	int i, j;
// 	for (i = 0; i < 4; ++i) {
// 		for (j = 0; j < 4; ++j) {
// 			result.mat[i][j] = mat[i][j] + other.mat[i][j];
// 		}
// 	}

// 	return result;
// }
// Mat4 Mat4::operator-(const Mat4 & other) {
// 	Mat4 result;

// 	int i, j;
// 	for (i = 0; i < 4; ++i) {
// 		for (j = 0; j < 4; ++j) {
// 			result.mat[i][j] = mat[i][j] - other.mat[i][j];
// 		}
// 	}

// 	return result;
// }

// Mat4 Mat4::operator*(const Mat4& other) {
// 	Mat4 result;

// 	int i, j, k;
// 	for (i = 0; i < 4; ++i) {
// 		for (j = 0; j < 4; ++j) {
// 			result.mat[i][j] = 0;
// 			for (k = 0; k < 4; ++k) {
// 				result.mat[i][j] += mat[i][k] * other.mat[k][j];
// 			}
// 		}
// 	}
// 	return result;
// }


// Mat4 Mat4::operator*(const float & scalar) {
// 	Mat4 result;

// 	int i, j;
// 	for (i = 0; i < 4; ++i) {
// 		for (j = 0; j < 4; ++j) {
// 			result.mat[i][j] = mat[i][j] * scalar;
// 		}
// 	}

// 	return result;
// }

// Mat4 operator*(const float & scalar, Mat4 m) {
// 	return m * scalar;
// }

Point operator*(const Mat4 & m, const Point & p) {
	Point p2;

	p2.x = m.mat[0][0] * p.x + m.mat[0][1] * p.y + m.mat[0][2] * p.z + m.mat[0][3] * p.w;
	p2.y = m.mat[1][0] * p.x + m.mat[1][1] * p.y + m.mat[1][2] * p.z + m.mat[1][3] * p.w;
	p2.z = m.mat[2][0] * p.x + m.mat[2][1] * p.y + m.mat[2][2] * p.z + m.mat[2][3] * p.w;
	p2.w = m.mat[3][0] * p.x + m.mat[3][1] * p.y + m.mat[3][2] * p.z + m.mat[3][3] * p.w;
	
	return p2;
}

Vec operator*(const Mat4 & m, const Vec & v) {
	Vec v2;

	v2.x = m.mat[0][0] * v.x + m.mat[0][1] * v.y + m.mat[0][2] * v.z + m.mat[0][3] * v.w;
	v2.y = m.mat[1][0] * v.x + m.mat[1][1] * v.y + m.mat[1][2] * v.z + m.mat[1][3] * v.w;
	v2.z = m.mat[2][0] * v.x + m.mat[2][1] * v.y + m.mat[2][2] * v.z + m.mat[2][3] * v.w;
	v2.w = m.mat[3][0] * v.x + m.mat[3][1] * v.y + m.mat[3][2] * v.z + m.mat[3][3] * v.w;

	return v2;
}

Ray operator*(const Mat4 & m, const Ray & r) {
	Ray r2;

	r2.origin = m * r.origin;
	r2.dir = m * r.dir;
	r2.t_max = r.t_max; // TODO  is this right?
	r2.t_min = r.t_min;
	return r2;
	return r;
}


LocalGeo::LocalGeo() {}

LocalGeo::LocalGeo(Point pos, Vec normal, Shape * s)
: pos(pos), normal(normal), shape_hit(s) {}


Vec Light::compute_light(float visible, Vec light_color, Vec dir, Vec normal,
	Vec half, Vec diffuse, Vec specular, float shininess) {

	float ndotl = Transform::dot(dir, normal);
	float hdotn = Transform::dot(half, normal);

	Vec result = visible * light_color * (diffuse * std::max(ndotl, 0.0f) + specular * pow(std::max(hdotn, 0.0f), shininess));
	return result;
}

Light::Light(Vec col)
: light_color(col) {}

Vec PointLight::calc_lighting(const Vec & eye, Scene & s, LocalGeo & local) {
	// dist from light to pixel
	float d = sqrt(pow(local.pos.x - p.x, 2) + pow(local.pos.y - p.y, 2) + pow(local.pos.z - p.z, 2));

	// create ray from pixel to light source
	Ray r(Point(local.pos.x, local.pos.y, local.pos.z), Vec(p.x - local.pos.x, p.y - local.pos.y, p.z - local.pos.z), EPSILON);
	// calculate attenuation
	Vec atten_light_color = light_color / (atten_const + atten_lin * d + atten_quad * pow(d, 2));

	// check if view to light is blocked
	float t, v;
	LocalGeo local2;
	if (r.intersect(s, t, local2) && t < d) // TODO what if light is between objects?
		v = 0.0f;
	else
		v = 1.0f;


	Vec dir = r.dir;
	Vec pos_vector(local.pos.x, local.pos.y, local.pos.z);
	Vec eyedirn = Vec::normalize(eye - pos_vector);
	Vec half = Vec::normalize(dir + eyedirn);

	return compute_light(v, atten_light_color, dir, local.normal, 
		half, local.shape_hit->diffuse, local.shape_hit->specular, local.shape_hit->shininess);
}

PointLight::PointLight(Vec atten, Vec col, Point p)
: Light(col), p(p), atten_const(atten[0]), atten_lin(atten[1]), atten_quad(atten[2])
{}

Vec DirLight::calc_lighting(const Vec & eye, Scene & s, LocalGeo & local) {

	// create ray starting at pixel in dir of light source
	Ray r(Point(local.pos.x, local.pos.y, local.pos.z), dir, EPSILON);

	// check if view to light is blocked
	float t, v;
	LocalGeo local2;
	if (r.intersect(s, t, local2))
		v = 0.0f;
	else
		v = 1.0f;

	Vec pos_vector(local.pos.x, local.pos.y, local.pos.z);
	Vec eyedirn = Vec::normalize(eye - pos_vector);
	Vec normalized_dir = Vec::normalize(dir);
	Vec half = Vec::normalize(normalized_dir + eyedirn);

	return compute_light(v, light_color, normalized_dir, local.normal,
		half, local.shape_hit->diffuse, local.shape_hit->specular, local.shape_hit->shininess);
}

DirLight::DirLight(Vec col, Vec dir)
: Light(col), dir(Vec::normalize(dir)) {}

Shape::Shape(Vec d, Vec s, Vec e, Vec a, float shiny)
:  diffuse(d), specular(s), emission(e), ambient(a), shininess(shiny)
{}

bool Triangle::intersect(Ray& ray, float& thit, LocalGeo& local) {
	Vec a = v1.to_vec();
	Vec b = v2.to_vec();
	Vec c = v3.to_vec();

	Vec n = Vec::normalize(Transform::cross(b - a, c - a));
	
	float denom = Transform::dot(ray.dir, n);
	if (denom == 0)
		return false;

	thit = (Transform::dot(a, n) - Transform::dot(ray.origin.to_vec(), n)) / denom;

	// TODO inside triangle?

	local.pos = ray.evaluate(thit).to_point();
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
	Vec a = v1.to_vec();
	Vec b = v2.to_vec();
	Vec c = v3.to_vec();

	Vec n = Vec::normalize(Transform::cross(b - a, c - a));

	float denom = Transform::dot(ray.dir, n);
	if (denom == 0)
		return false;

	float thit;
	thit = (Transform::dot(a, n) - Transform::dot(ray.origin.to_vec(), n)) / denom;


	Point pos = ray.evaluate(thit).to_point();

	float alpha, beta, gamma;
	barycentric(pos, alpha, beta, gamma);

	if (alpha >= 0 && alpha <= 1 &&
		beta >= 0 && beta <= 1 &&
		gamma >= 0 && gamma <= 1)
		return true;


	return false;
}

Triangle::Triangle(Point p1, Point p2, Point p3, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny)
: Shape(d, s, e, a, shiny), v1(t * p1), v2(t * p2), v3(t * p3) // apply transformation to vertices
{}

// from Real-Time Collision Detection
void Triangle::barycentric(Point p, float &u, float &v, float &w)
{
	Vec a = v2.to_vec() - v1.to_vec();
	Vec b = v3.to_vec() - v1.to_vec();
	Vec c = p - v1.to_vec();
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

bool Sphere::intersect(Ray& ray, float& thit, LocalGeo& local) {
	float a, b, c, disc;
	Ray r2 = inverse * ray;

	a = Transform::dot(r2.dir, r2.dir);
	b = 2 * Transform::dot(r2.dir, r2.origin - center);
	c = Transform::dot(r2.origin - center, r2.origin - center) - pow(radius, 2.0f);

	// check if discriminant < 0
	disc = pow(b, 2.0f) - 4.0f * a * c;

	if (disc < 0)
		return false;

	float t1, t2;

	t1 = (-b + sqrt(disc)) / (2.0f * a);
	t2 = (-b - sqrt(disc)) / (2.0f * a);

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

	Vec ray_tip = r2.evaluate(thit);
	Point untransformed_point = ray_tip.to_point();
	Vec untransformed_normal = Vec::normalize(ray_tip - center);

	local.pos = transformation * untransformed_point;
	local.normal = Vec::normalize(inverse_transpose * untransformed_normal);
	local.shape_hit = this;

	return true;
}

bool Sphere::intersectP(Ray& ray) {
	float a, b, c, disc;

	Ray r2 = Transform::inverse(transformation) * ray;

	a = Transform::dot(r2.dir, r2.dir);
	b = 2 * Transform::dot(r2.dir, r2.origin - center);
	c = Transform::dot(r2.origin - center, r2.origin - center) - pow(radius, 2.0f);

	// check if discriminant >= 0
	disc = pow(b, 2.0f) - 4.0f * a * c;
	return disc >= 0;
}

Sphere::Sphere(float cx, float cy, float cz, float r, Mat4 t, Vec d, Vec s, Vec e, Vec a, float shiny)
: Shape(d, s, e, a, shiny), center(cx, cy, cz), radius(r), transformation(t)
{
	inverse = Transform::inverse(transformation);
	inverse_transpose = Transform::transpose3x3(Transform::inverse3x3(transformation));
}

Camera::Camera()
: w(0), h(0), fovx(0.0f), fovy(0.0f) {}

void Camera::init(Vec new_eye, Vec new_center, Vec new_up, float fov, int new_w, int new_h) {
	eye = new_eye;
	center = new_center;
	up = new_up;
	w = new_w;
	h = new_h;

	// convert fov to radians, store in fovy
	fovy = fov * (float)(M_PI / 180.0);
	// calculate fovx in radians
	fovx = 2.0f * atan(tan(fovy / 2.0f) * ((float)w / (float)h));

	// construct coord frame (u_vec, v_vec, and w_vec)
	Vec a = eye - center;
	Vec b = up;
	w_vec = Vec::normalize(a);
	u_vec = Vec::normalize(Transform::cross(b, w_vec));
	v_vec = Transform::cross(w_vec, u_vec);
}

Image::Image(int w, int h)
: w(w), h(h)
{
	bytes = new unsigned char[3 * w * h]; // 3 bytes for each pixel
}

Image::Image(const Image & other)
: w(other.w), h(other.h)
{
	bytes = new unsigned char[3 * w * h];
	// copy bytes into this image
	int i;
	for (i = 0; i < 3 * w * h; ++i) {
		bytes[i] = other.bytes[i];
	}
}


Image::~Image() {
	delete[] bytes;
}

void Image::color_pixel(int i, int j, const unsigned char color[]) {
	int starting_byte = 3 * (i * w + j);

	for (int idx = 0; idx < 3; ++idx) {
		bytes[starting_byte + idx] = color[idx];
	}

}

void Image::save(std::string file) {
	stbi_write_png(file.c_str(), w, h, 3, (const void *)bytes, w * 3);
}

Image Raytracer::raytrace(Camera cam, Scene scene) {
	Image image(cam.w, cam.h);
	int i, j, k;
	// const unsigned char red[] = { 255, 0, 0 };
	// const unsigned char green[] = { 0, 255, 0 };
	// const unsigned char blue[] = { 0, 0, 255 };
	// const unsigned char black[] = { 0, 0, 0 };
	unsigned char color[3];

	//float t;
	//LocalGeo local;

	Vec pixel_color;

	for (i = 0; i < cam.h; ++i) {
		for (j = 0; j < cam.w; ++j) {

			Ray ray(cam, i, j);
			
			pixel_color = trace(ray, scene, 0); // TODO start at 0 or 1?

			for (k = 0; k < 3; ++k) {
				// change pixel_color to range 0 to 255
				// make sure new values are not greater than 255
				int new_color = (int)(pixel_color[k] * 255.0f);
				if (new_color > 255)
					new_color = 255;
				color[k] = (unsigned char)new_color;
			}

			image.color_pixel(i, j, color);
		}
	}

	return image;
}

Raytracer::Raytracer(int max_depth) : max_depth(max_depth) {}

Vec Raytracer::trace(Ray r, Scene scene, int num_recs) {
	Vec color(0.0f, 0.0f, 0.0f);

	if (num_recs > max_depth)
		return color;

	float t;
	LocalGeo local;

	if (!r.intersect(scene, t, local))
		return color;

	
	// Illumination model
	color = local.shape_hit->ambient + local.shape_hit->emission;
	for (auto & light : scene.lights) {
		color = color + light->calc_lighting(r.origin.to_vec(), scene, local); // TODO implement += for Vec
	}

	// Reflected ray
	Vec reflected_dir = r.dir - 2.0f * Transform::dot(r.dir, local.normal) * local.normal;
	Ray reflected_ray(local.pos, reflected_dir, EPSILON);

	color = color + local.shape_hit->specular * trace(reflected_ray, scene, num_recs + 1);

	return color;
}