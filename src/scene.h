#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class Shape;
class Light;
class Ray;
class IntersectionInfo;

class Scene {
public:
  bool intersect(const Ray &ray, double tolerance,
                 IntersectionInfo &closest_hit_geo) const;

  std::vector<std::shared_ptr<Shape>> objects;
  std::vector<std::shared_ptr<Light>> lights;

private:
  const double m_t_max = 10000.0;
};

#endif
