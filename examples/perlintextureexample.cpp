#include "camera.h"
#include "image.h"
#include "materials/diffusematerial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/sphere.h"
#include "textures/perlintexture.h"

int main() {
    std::string outfile("perlinexample.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(-1.2, 0.3, 0.7), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        40.0, aspect);

    // auto perlin_material1 = std::make_shared<DiffuseMaterial>(
    //     std::make_shared<PerlinTexture>(6.0, 1.0, 5, 2.2, 0.4));

    auto perlin_material1 = std::make_shared<DiffuseMaterial>(
        std::make_shared<MarbleTexture>(0.05, 10.0, 1.0, 5, 2.0, 0.5));

    auto perlin_material2 = std::make_shared<DiffuseMaterial>(
        std::make_shared<TurbulentNoiseTexture>(10.0));

    Scene scene(
        { std::make_shared<Sphere>(Vec(0.0, 0.0, 0.0), 0.5, perlin_material1),
            std::make_shared<Sphere>(
                Vec(0.0, -100.5, -1.0), 100.0, perlin_material2) });

    Raytracer raytracer(50, 100);
    // Raytracer raytracer(5);

    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
