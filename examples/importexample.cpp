#include "camera.h"
#include "image.h"
#include "importer.h"
#include "materials/diffusematerial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/triangle.h"

#include "math/vec.h"
#include "textures/imagetexture.h"

#include <filesystem>

int main() {
    // Model from:
    // https://sketchfab.com/3d-models/owl-zun-wine-vessel-13th-12th-century-bce-ca77ae1351ca4b1c9a7d403e09e1c4af

    std::string file("scene.gltf");
    std::string dir("/home/mujpao/Documents/3d/"
                    "owl_zun_wine_vessel_13th-12th_century_bce_gltf/");

    Importer importer;

    std::shared_ptr<ShapeList> shapes = importer.read_objects(dir, file);

    std::string outfile("importexample.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(0.1, 15.0, 5.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        45.0, aspect);

    Raytracer raytracer(5, 10);
    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));
    Scene scene(shapes);

    Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    image.save(outfile);

    return 0;
}
