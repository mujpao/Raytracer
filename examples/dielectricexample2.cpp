#include "camera.h"
#include "image.h"
#include "materials/dielectricmaterial.h"
#include "materials/diffusematerial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/sphere.h"

int main() {
    std::string outfile("dielectricexample2.png");

    double width = 400.0;
    double aspect = 16.0 / 9.0;

    Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        40.0, aspect);

    std::shared_ptr<ShapeList> shape_list = std::make_shared<ShapeList>();

    auto material_ground
        = std::make_shared<DiffuseMaterial>(Vec(0.3, 0.3, 0.6));
    auto material_left = std::make_shared<DiffuseMaterial>(Vec(0.1, 0.5, 0.2));
    auto material_right = std::make_shared<DiffuseMaterial>(Vec(0.7, 0.1, 0.1));

    auto material_glass = std::make_shared<DielectricMaterial>(1.5);

    shape_list->add(
        std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, material_glass));
    shape_list->add(std::make_shared<Sphere>(
        Vec(0.0, -100.5, -1.0), 100.0, material_ground));
    shape_list->add(
        std::make_shared<Sphere>(Vec(-0.75, 0.0, -2.5), 0.5, material_left));
    shape_list->add(
        std::make_shared<Sphere>(Vec(0.75, 0.0, -2.5), 0.5, material_right));

    Scene scene(shape_list);

    Raytracer raytracer(50, 200);

    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
