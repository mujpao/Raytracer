#ifndef SCENE_H
#define SCENE_H

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
        = std::vector<std::shared_ptr<Light>>());

    Scene(std::shared_ptr<ShapeList> shape_list,
        const std::vector<std::shared_ptr<Light>>& lights
        = std::vector<std::shared_ptr<Light>>());

    bool intersect(const Ray& ray, IntersectionInfo& closest_hit_info) const;

    inline const std::vector<std::shared_ptr<Light>>& lights() const {
        return m_lights;
    }

    void add_light(std::shared_ptr<Light> light);

    // void add_shape(std::shared_ptr<Shape> shape); // TODO

private:
    void build_tree();

    std::shared_ptr<ShapeList> m_shapes;
    std::vector<std::shared_ptr<Light>> m_lights;

    std::shared_ptr<BoundingBoxNode> m_root;
};

#endif
