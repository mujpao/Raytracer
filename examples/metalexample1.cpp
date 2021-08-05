#include "camera.h"
#include "image.h"
#include "materials/diffusematerial.h"
#include "materials/metalmaterial.h"
#include "raytracer.h"
#include "readfile.h"
#include "scene.h"
#include "shapes/sphere.h"

int main() {
    std::string outfile("metalexample1.png");

    double width = 400.0;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        45.0, aspect);

    auto material_ground
        = std::make_shared<DiffuseMaterial>(Vec(0.8, 0.8, 0.0));
    auto material_center
        = std::make_shared<DiffuseMaterial>(Vec(0.7, 0.3, 0.3));
    auto material_left
        = std::make_shared<MetalMaterial>(Vec(0.8, 0.8, 0.8), 0.3);
    auto material_right
        = std::make_shared<MetalMaterial>(Vec(0.8, 0.6, 0.2), 1.0);

    Scene scene({ std::make_shared<Sphere>(
                      Vec(0.0, -100.5, -1.0), 100.0, material_ground),
        std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, material_center),
        std::make_shared<Sphere>(Vec(-1.0, 0.0, -1.0), 0.5, material_left),
        std::make_shared<Sphere>(Vec(1.0, 0.0, -1.0), 0.5, material_right) });

    // scene.objects.push_back(std::make_shared<Sphere>(
    //     Vec(0.0, -100.5, -1.0), 100.0, material_ground));
    // scene.objects.push_back(
    //     std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, material_center));
    // scene.objects.push_back(
    //     std::make_shared<Sphere>(Vec(-1.0, 0.0, -1.0), 0.5, material_left));
    // scene.objects.push_back(
    //     std::make_shared<Sphere>(Vec(1.0, 0.0, -1.0), 0.5, material_right));

    Raytracer raytracer(50, 100);
    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
