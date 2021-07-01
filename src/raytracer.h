#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "math/vec.h"

class Image;
class Camera;
class Scene;
class Ray;

class Raytracer {
public:
    Raytracer(int max_depth, int num_samples = 1, bool normals_only = false);

    Image raytrace(
        const Camera& camera, const Scene& scene, bool gamma_corrected = false);

    // Determines color of pixels where ray does not hit an object. Default is
    // black.
    void set_background_color(const Vec& color);

private:
    Vec trace(const Ray& r, const Scene& scene, int depth);

    int m_max_depth;
    int m_num_samples;
    bool m_normals_only;

    Vec m_background_color = Vec(0.0, 0.0, 0.0);
};

#endif
