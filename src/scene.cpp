#include "scene.h"

#include "intersectioninfo.h"
#include "ray.h"
#include "shapes/boundingboxnode.h"
#include "shapes/shapelist.h"
#include "utils.h"

#include <iostream>

Scene::Scene(const std::vector<std::shared_ptr<AbstractShape>>& shapes,
    const std::vector<std::shared_ptr<Light>>& lights)
    : m_shapes(std::make_shared<ShapeList>(shapes)), m_lights(lights) {
    build_tree();
}

Scene::Scene(std::shared_ptr<ShapeList> shape_list,
    const std::vector<std::shared_ptr<Light>>& lights)
    : m_shapes(std::move(shape_list)), m_lights(lights) {
    build_tree();
}

bool Scene::intersect(
    const Ray& ray, IntersectionInfo& closest_hit_info) const {

    // Ray adjusted_ray(ray.evaluate(Utils::RAY_HIT_TOLERANCE),
    // ray.direction()); double t = Utils::T_MAX;

    return m_shapes->intersect(
        ray, Utils::RAY_HIT_TOLERANCE, Utils::T_MAX, closest_hit_info);

    // return m_root->intersect(adjusted_ray, 0.0, Utils::T_MAX,
    // closest_hit_info);
}

void Scene::add_light(std::shared_ptr<Light> light) {
    m_lights.push_back(std::move(light));
}

// void Scene::add_shape(std::shared_ptr<Shape> shape) {
//     m_shapes->add(std::move(shape));
// }

void Scene::build_tree() {
    m_root.reset(new BoundingBoxNode(m_shapes));
    std::cout << *m_root << '\n';
}
