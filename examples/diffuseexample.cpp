#include "camera.h"
#include "image.h"
#include "materials/diffusematerial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/sphere.h"

int main() {
    std::string outfile("diffuseexample.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        45.0, aspect);

    auto diffuse_material
        = std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5));

    Scene scene(
        { std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, diffuse_material),
            std::make_shared<Sphere>(
                Vec(0.0, -100.5, -1.0), 100.0, diffuse_material) });

    Raytracer raytracer(50, 100);
    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
