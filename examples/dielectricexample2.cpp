#include "camera.h"
#include "image.h"
#include "materials/dielectricmaterial.h"
#include "materials/diffusematerial.h"
#include "materials/metalmaterial.h"
#include "raytracer.h"
#include "readfile.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/sphere.h"

#include "ray.h"

int main() {
    std::string outfile("dielectricexample2.png");

    double width = 400.0;
    double aspect = 16.0 / 9.0;

    Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        40.0, aspect);

    std::shared_ptr<ShapeList> shape_list = std::make_shared<ShapeList>();

    auto material_ground
        = std::make_shared<DiffuseMaterial>(Vec(0.8, 0.8, 0.0));
    auto material_left = std::make_shared<DiffuseMaterial>(Vec(0.1, 0.2, 0.5));
    auto material_right = std::make_shared<DiffuseMaterial>(Vec(0.7, 0.1, 0.1));

    auto material_glass = std::make_shared<DielectricMaterial>(1.5);

    shape_list->add(
        std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, material_glass));
    shape_list->add(std::make_shared<Sphere>(
        Vec(0.0, -100.5, -1.0), 100.0, material_ground));
    shape_list->add(
        std::make_shared<Sphere>(Vec(-1.0, 0.0, -1.0), 0.5, material_left));
    shape_list->add(
        std::make_shared<Sphere>(Vec(1.0, 0.0, -1.0), 0.5, material_right));

    Scene scene(shape_list);

    Raytracer raytracer(50, 100);
    // Raytracer raytracer(5); // debugging

    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    /************************************************************/
    // Rays for debugging:

    // Ray r(Vec(0.0, 0.0, 1.0, 1.0), Vec(0.0, 0.0, -1.0));
    // Ray dirs:
    // r1: <0, 0, -1>, r2: <0, 0, -1>, r3: <0, 0, -1>

    // Ray r(Vec(0.0, 0.0, 1.0, 1.0), Vec(0.002, 0.1, -1.0));
    // Ray dirs:
    // r1: <.002, .1, -1>, r2: <0, -.04, -.999>, r3: <-.0, -.18, -.98>...

    // raytracer.trace(r, scene, 50);

    /************************************************************/

    Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    image.save(outfile);

    return 0;
}
