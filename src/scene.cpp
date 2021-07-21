#include "scene.h"

#include "intersectioninfo.h"
#include "ray.h"
#include "shapes/boundingboxnode.h"
#include "shapes/shapelist.h"
#include "utils.h"

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

    return m_root->intersect(
        ray, Utils::RAY_HIT_TOLERANCE, Utils::T_MAX, closest_hit_info);
}

void Scene::add_light(std::shared_ptr<Light> light) {
    m_lights.push_back(std::move(light));
}

void Scene::build_tree() {
    m_root.reset(new BoundingBoxNode(m_shapes));
    // std::cout << '\n' << *m_root << std::endl;
}
