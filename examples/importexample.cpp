#include "image.h"
#include "importer.h"
#include "raytracer.h"
#include "scene.h"

#include "math/vec.h"

#include <filesystem>

int main() {
    // Model from:
    // https://sketchfab.com/3d-models/owl-zun-wine-vessel-13th-12th-century-bce-ca77ae1351ca4b1c9a7d403e09e1c4af
    std::string file("owl_zun.gltf");
    std::string dir(
        std::filesystem::path(__FILE__).parent_path().string() + "/owl_zun/");

    Importer importer;

    Scene scene = importer.read_file(dir, file);

    std::string outfile("importexample.png");

    int width = 400;

    Raytracer raytracer(5, 200);

    raytracer.set_background_color(Vec(0.4, 0.4, 0.4));

    Image image = raytracer.raytrace(scene, scene.camera(), width, true);
    image.save(outfile);

    return 0;
}
