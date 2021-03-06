#include "camera.h"
#include "image.h"
#include "materials/dielectricmaterial.h"
#include "materials/diffusematerial.h"
#include "materials/metalmaterial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/sphere.h"

int main() {
    std::string outfile("dielectricexample1.png");

    double width = 400.0;
    double aspect = 16.0 / 9.0;

    // Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
    //     40.0, aspect);

    // Camera camera(Vec(-2, 2, 1), Vec(0, 0, -1), Vec(0.0, 1.0, 0.0), 40.0,
    //     aspect);

    Vec lookfrom(3.0, 3.0, 2.0);
    Vec lookat(0.0, 0.0, -1.0);
    Vec vup(0.0, 1.0, 0.0);
    double dist_to_focus = Vec::length(lookfrom - lookat);
    double aperture = 2.0;

    Camera camera(lookfrom, lookat, vup, 20.0, aspect, aperture, dist_to_focus);

    std::shared_ptr<ShapeList> shape_list = std::make_shared<ShapeList>();

    auto material_ground
        = std::make_shared<DiffuseMaterial>(Vec(0.8, 0.8, 0.0));
    auto material_center
        = std::make_shared<DiffuseMaterial>(Vec(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<DielectricMaterial>(1.5);
    auto material_right
        = std::make_shared<MetalMaterial>(Vec(0.8, 0.6, 0.2), 0.0);

    shape_list->add(std::make_shared<Sphere>(
        Vec(0.0, -100.5, -1.0), 100.0, material_ground));
    shape_list->add(
        std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, material_center));
    shape_list->add(
        std::make_shared<Sphere>(Vec(-1.0, 0.0, -1.0), 0.5, material_left));
    shape_list->add(
        std::make_shared<Sphere>(Vec(-1.0, 0.0, -1.0), -0.45, material_left));
    shape_list->add(
        std::make_shared<Sphere>(Vec(1.0, 0.0, -1.0), 0.5, material_right));

    Scene scene(shape_list);

    Raytracer raytracer(50, 100);

    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
