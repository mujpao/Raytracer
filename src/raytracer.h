#ifndef RAYTRACER_H
#define RAYTRACER_H

class Image;
class Camera;
class Scene;
class Vec;
class Ray;

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
