#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

class Shape;
class Light;

class Scene {
public:
	std::vector<std::shared_ptr<Shape>> objects;
	std::vector<std::shared_ptr<Light>> lights;
};

#endif
