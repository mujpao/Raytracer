#include "camera.h"
#include "image.h"
#include "materials/diffusematerial.h"
#include "math/transform.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/sphere.h"
#include "textures/checkeredtexture.h"
#include "textures/imagetexture.h"

#include <filesystem>

int main() {
    std::string outfile("textureexample2.png");

    std::filesystem::path path(__FILE__);
    std::string texture_file
        = std::string(path.parent_path().parent_path().string())
        + "/resources/earthmap.jpg";

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(0.0, 1.0, 1.5), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        35.0, aspect);

    auto ground_material = std::make_shared<DiffuseMaterial>(
        std::make_shared<CheckeredTexture>(10.0));

    auto sphere_material = std::make_shared<DiffuseMaterial>(
        std::make_shared<ImageTexture>(texture_file));

    Mat4 tx = Transform::rotate(20.0, Vec(1.0, 0.0, 0.0))
        * Transform::rotate(180.0, Vec(0.0, 1.0, 0.0));

    Scene scene({ std::make_shared<Sphere>(
                      Vec(0.0, 0.0, 0.0), 0.5, sphere_material, tx),
        std::make_shared<Sphere>(
            Vec(0.0, -100.5, -1.0), 100.0, ground_material) });

    Raytracer raytracer(50, 100);

    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
