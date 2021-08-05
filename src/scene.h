#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

#include <memory>
#include <vector>

class AbstractShape;
class ShapeList;
class Light;
class Ray;
class IntersectionInfo;
class BoundingBoxNode;

class Scene {
public:
    Scene() = default;

    Scene(const std::vector<std::shared_ptr<AbstractShape>>& shapes,
        const std::vector<std::shared_ptr<Light>>& lights
        = std::vector<std::shared_ptr<Light>>(),
        const Camera& camera = Camera());

    Scene(std::shared_ptr<ShapeList> shape_list,
        const std::vector<std::shared_ptr<Light>>& lights
        = std::vector<std::shared_ptr<Light>>(),
        const Camera& camera = Camera());

    bool intersect(const Ray& ray, IntersectionInfo& closest_hit_info) const;

    inline const std::vector<std::shared_ptr<Light>>& lights() const {
        return m_lights;
    }

    Camera camera() const { return m_camera; }

    void add_light(std::shared_ptr<Light> light);

    // void add_shape(std::shared_ptr<Shape> shape); // TODO

private:
    void build_tree();

    std::shared_ptr<ShapeList> m_shapes;
    std::vector<std::shared_ptr<Light>> m_lights;

    Camera m_camera;

    std::shared_ptr<BoundingBoxNode> m_root;
};

#endif
