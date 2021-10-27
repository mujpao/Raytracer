#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "math/vec.h"
#include "progressindicator.h"

#include <vector>

class Image;
class Camera;
class Scene;
class Ray;

class Raytracer {
public:
    Raytracer(int max_depth, int num_samples = 1, bool normals_only = false);

    Image raytrace(const Scene& scene, const Camera& camera,
        const std::size_t width, bool gamma_corrected = false,
        unsigned int num_threads = 4);

    // Determines color of pixels where ray does not hit an object. Default is
    // black.
    void set_background_color(const Vec& color) { m_background_color = color; }

    void trace_row(std::size_t row, const Scene& scene, const Camera& camera,
        std::size_t width, std::size_t height,
        std::vector<std::vector<Vec>>& colors);

    Vec trace(const Ray& r, const Scene& scene, int depth) const;

private:
    int m_max_depth;
    int m_num_samples;
    bool m_normals_only;

    Vec m_background_color = Vec(0.0, 0.0, 0.0);

    ProgressIndicator m_progress_indicator;
};

#endif
