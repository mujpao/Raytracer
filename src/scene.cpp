#include "scene.h"

#include "intersectioninfo.h"
#include "ray.h"
#include "shapes/shapelist.h"
#include "utils.h"

Scene::Scene(const std::vector<std::shared_ptr<Shape>>& shapes,
    const std::vector<std::shared_ptr<Light>>& lights)
    : m_shapes(std::make_shared<ShapeList>(std::move(shapes))),
      m_lights(lights) {}

Scene::Scene(std::shared_ptr<ShapeList> shape_list,
    const std::vector<std::shared_ptr<Light>>& lights)
    : m_shapes(std::move(shape_list)), m_lights(lights) {}

bool Scene::intersect(
    const Ray& ray, double tolerance, IntersectionInfo& closest_hit_geo) const {

    Ray adjusted_ray(ray.evaluate(tolerance), ray.direction());

    double t = Utils::T_MAX;

    return m_shapes->intersect(adjusted_ray, t, closest_hit_geo);
}

void Scene::add_light(std::shared_ptr<Light> light) {
    m_lights.push_back(std::move(light));
}

void Scene::add_shape(std::shared_ptr<Shape> shape) {
    m_shapes->add(std::move(shape));
}
