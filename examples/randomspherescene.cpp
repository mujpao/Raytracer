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
#include "utils.h"

Scene random_scene() {

    std::shared_ptr<ShapeList> shape_list = std::make_shared<ShapeList>();

    auto ground_material
        = std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5));
    shape_list->add(
        std::make_shared<Sphere>(Vec(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            auto choose_mat = Utils::random_double();
            Vec center(a + 0.9 * Utils::random_double(), 0.2,
                b + 0.9 * Utils::random_double());

            if (Vec::length(center - Vec(4, 0.2, 0)) > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Utils::random_vec() * Utils::random_vec();
                    sphere_material = std::make_shared<DiffuseMaterial>(albedo);
                    shape_list->add(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Utils::random_vec(0.5, 1);
                    auto fuzz = Utils::random_double(0, 0.5);
                    sphere_material
                        = std::make_shared<MetalMaterial>(albedo, fuzz);
                    shape_list->add(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<DielectricMaterial>(1.5);
                    shape_list->add(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<DielectricMaterial>(1.5);
    shape_list->add(std::make_shared<Sphere>(Vec(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<DiffuseMaterial>(Vec(0.4, 0.2, 0.1));
    shape_list->add(std::make_shared<Sphere>(Vec(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<MetalMaterial>(Vec(0.7, 0.6, 0.5), 0.0);
    shape_list->add(std::make_shared<Sphere>(Vec(4, 1, 0), 1.0, material3));

    return Scene(shape_list);
}

int main() {
    std::string outfile("randomspherescene.png");

    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    Scene scene = random_scene();

    Vec lookfrom(13, 2, 3);
    Vec lookat(0, 0, 0);
    Vec vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera camera(
        lookfrom, lookat, vup, 20.0, aspect_ratio, aperture, dist_to_focus);

    Raytracer raytracer(max_depth, samples_per_pixel);
    // Raytracer raytracer(5);

    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Image image
        = raytracer.raytrace(camera, scene, image_width, aspect_ratio, true);
    image.save(outfile);

    return 0;
}
