#include "camera.h"
#include "image.h"
#include "materials/diffusematerial.h"
#include "materials/lightmaterial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/sphere.h"
#include "textures/checkeredtexture.h"

int main() {
    std::string outfile("textureexample1.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(-1.2, 0.1, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        40.0, aspect);

    auto checker_material1 = std::make_shared<DiffuseMaterial>(
        std::make_shared<CheckeredTexture>(10.0));

    auto checker_material2
        = std::make_shared<DiffuseMaterial>(std::make_shared<CheckeredTexture>(
            Vec(0.4, 0.8, 0.8), Vec(0.98, 0.09, 0.95), 50.0));

    auto light_material = std::make_shared<LightMaterial>(Vec(4.0, 10.0, 6.0));

    Scene scene({ std::make_shared<Sphere>(
                      Vec(0.0, 0.0, 0.0), 0.5, checker_material2),
        std::make_shared<Sphere>(
            Vec(0.0, -100.5, -1.0), 100.0, checker_material1),
        std::make_shared<Sphere>(Vec(0.0, 30.0, 0.0), 10.0, light_material) });

    Raytracer raytracer(50, 100);
    // Raytracer raytracer(5, 10);

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
