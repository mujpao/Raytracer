#ifndef RAYTRACER_H
#define RAYTRACER_H

class Image;
class Camera;
class Scene;
class Vec;
class Ray;

class Raytracer {
public:
	Raytracer(int max_depth, bool normals_only = false);

	Image raytrace(const Camera &camera, const Scene &scene);
private:
	// TODO change name to calc_intersection_color() or something...
	Vec trace(const Ray &r, const Scene &scene, int num_recs); // recursively determines the color of the intersection of ray with the scene

	int m_max_depth;
	bool m_normals_only = false;
};

#endif
