#ifndef RAY_H
#define RAY_H

#include "math/vec.h"

class Camera;
class Scene;
class IntersectionInfo;

class Ray {
public:
// TODO pass by const reference
	Ray(Vec origin, Vec dir, double t_min = 0.0); //TODO should t_min and max be different depending on whether this is shadow ray?
	Ray();
	Ray(Camera cam, int i, int j); //ray through center of pixel i, j
	// TODO Only need to know eye pos

	inline Vec origin() const { return m_origin; }
	inline Vec direction() const { return m_direction; }
	inline double t_min() const { return m_t_min; }

	Vec evaluate(double t) const;

	// TODO move to scene class?
	bool intersect(const Scene &s, float & t_closest, IntersectionInfo & closest_hit_geo) const;
	friend std::ostream& operator<<(std::ostream& os, const Ray& r);

private:
	Vec m_origin;
	Vec m_direction;
	
	double m_t_min;
	const double m_t_max = 10000.0;
};

#endif
