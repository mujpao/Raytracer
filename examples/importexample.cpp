#include "camera.h"
#include "image.h"
#include "importer.h"
#include "materials/diffusematerial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/triangle.h"

#include "materials/lightmaterial.h"
#include "math/transform.h"
#include "math/vec.h"
#include "shapes/rect.h"
#include "textures/imagetexture.h"

#include <filesystem>

int main() {
    // Model from:
    // https://sketchfab.com/3d-models/owl-zun-wine-vessel-13th-12th-century-bce-ca77ae1351ca4b1c9a7d403e09e1c4af

    // std::string file("scene.gltf");
    // std::string dir("/home/mujpao/Documents/3d/"
    //                 "owl_zun_wine_vessel_13th-12th_century_bce_gltf/");

    // Importer importer;

    // std::shared_ptr<ShapeList> shapes = importer.read_objects(dir, file);

    // std::string outfile("importexample.png");

    // int width = 400;
    // double aspect = 16.0 / 9.0;
    // Camera camera(Vec(0.1, 15.0, 5.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0,
    // 0.0),
    //     45.0, aspect);

    // Raytracer raytracer(5, 10);
    // raytracer.set_background_color(Vec(0.5, 0.7, 1.0));
    // Scene scene(shapes);

    // Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    // image.save(outfile);

    std::string file("brickwall.gltf");
    std::string dir("/home/mujpao/Documents/3d/brickwall/");

    Importer importer;

    std::shared_ptr<ShapeList> shapes = importer.read_objects(dir, file);

    std::string outfile("importexample.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    // Camera camera(Vec(0.1, 3.0, 0.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
    //     45.0, aspect);

    Camera camera(Vec(0.0, 0.2, 0.96), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, -1.0),
        45.0, aspect);

    Raytracer raytracer(5, 100);
    raytracer.set_background_color(Vec(0.3, 0.3, 0.3));

    auto light_color = std::make_shared<LightMaterial>(Vec(5.0, 5.0, 5.0));
    Vec p1(1.0, 0.0, 1.0);
    Vec p2(1.0, 0.0, -1.0);
    Vec p3(-1.0, 0.0, -1.0);
    Vec p4(-1.0, 0.0, 1.0);
    auto tx
        = Transform::translate(0.4, 6.0, 1.0) * Transform::scale(1.5, 1.5, 1.5);
    auto light = std::make_shared<Rect>(p1, p2, p3, p4, light_color, tx);

    shapes->add(light);

    Scene scene(shapes);

    Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    image.save(outfile);

    return 0;
}
