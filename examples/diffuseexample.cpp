#include "camera.h"
#include "diffusematerial.h"
#include "image.h"
#include "raytracer.h"
#include "readfile.h"
#include "scene.h"
#include "shape.h"

int main() {
  std::string outfile("example1.png");
  Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
                45.0, 400, 225);
  Scene scene;

  auto diffuse_material = std::make_shared<DiffuseMaterial>();
  scene.objects.push_back(std::make_shared<Sphere>(
      Vec(0.0, 0.0, -1.0), 0.5, Mat4(1.0), diffuse_material));
  scene.objects.push_back(std::make_shared<Sphere>(
      Vec(0.0, -100.5, -1.0), 100.0, Mat4(1.0), diffuse_material));

  Raytracer raytracer(50, 100);
  raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

  Image image = raytracer.raytrace(camera, scene);
  image.save(outfile);

  return 0;
}
