#include "camera.h"
#include "image.h"
#include "materials/dielectricmaterial.h"
#include "materials/diffusematerial.h"
#include "materials/metalmaterial.h"
#include "raytracer.h"
#include "readfile.h"
#include "scene.h"
#include "shape.h"

#include "ray.h"

int main() {
    std::string outfile("dielectricexample1.png");

    double width = 400.0;
    double aspect = 16.0 / 9.0;
    double height = width / aspect;

    // Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
    // 40.0, (int)width, (int)height);

    // Camera camera(Vec(-2, 2, 1), Vec(0, 0, -1), Vec(0.0, 1.0, 0.0), 40.0,
    //     (int)width, (int)height);

    Camera camera(Vec(-2, 2, 1), Vec(0, 0, -1), Vec(0.0, 1.0, 0.0), 20.0,
        (int)width, (int)height);

    Scene scene;

    auto material_ground
        = std::make_shared<DiffuseMaterial>(Vec(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<DielectricMaterial>(1.5);
    auto material_left = std::make_shared<DielectricMaterial>(1.5);
    auto material_right
        = std::make_shared<MetalMaterial>(Vec(0.8, 0.6, 0.2), 0.0);

    scene.objects.push_back(std::make_shared<Sphere>(
        Vec(0.0, -100.5, -1.0), 100.0, material_ground));
    scene.objects.push_back(
        std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, material_center));
    scene.objects.push_back(
        std::make_shared<Sphere>(Vec(-1.0, 0.0, -1.0), 0.5, material_left));
    scene.objects.push_back(
        std::make_shared<Sphere>(Vec(-1.0, 0.0, -1.0), -0.45, material_left));
    scene.objects.push_back(
        std::make_shared<Sphere>(Vec(1.0, 0.0, -1.0), 0.5, material_right));

    Raytracer raytracer(50, 100);
    // Raytracer raytracer(5);

    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    // Ray r(Vec(0.0, 0.0, 1.0, 1.0), Vec(0.0, 0.0, -1.0)); // for debugging
    // raytracer.trace(r, scene, 50);

    Image image = raytracer.raytrace(camera, scene, true);
    image.save(outfile);

    return 0;
}
