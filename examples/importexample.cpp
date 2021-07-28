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
    std::filesystem::path path(__FILE__);
    std::string texture_file = std::string(path.parent_path().parent_path())
        + "/resources/earthmap.jpg";

    auto plane_material = std::make_shared<DiffuseMaterial>(
        std::make_shared<ImageTexture>(texture_file));

    Vertex v1(Vec(2.0, 0.0, 1.0), { 1.0, 0.0 });
    Vertex v2(Vec(2.0, 0.0, -1.0), { 1.0, 1.0 });
    Vertex v3(Vec(-2.0, 0.0, -1.0), { 0.0, 1.0 });
    Vertex v4(Vec(-2.0, 0.0, 1.0), { 0.0, 0.0 });

    std::shared_ptr<ShapeList> shapes = std::make_shared<ShapeList>(
        std::vector<std::shared_ptr<AbstractShape>>{
            std::make_shared<Triangle>(v1, v2, v3, plane_material),
            std::make_shared<Triangle>(v1, v3, v4, plane_material) });

    std::string outfile("importexample.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(0.0, 3.0, 0.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, -1.0),
        45.0, aspect);

    Raytracer raytracer(5, 10);
    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));
    Scene scene(shapes);

    Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    image.save(outfile);

    // // std::string file("/home/mujpao/Documents/3d/defaultcube.obj");
    // std::string file("/home/mujpao/Documents/3d/simplescene.fbx");

    // Importer importer;

    // std::shared_ptr<ShapeList> shapes = importer.read_objects(file);

    // std::string outfile("importexample.png");

    // int width = 400;
    // double aspect = 16.0 / 9.0;
    // Camera camera(Vec(27.0, 11.03, 0.855), Vec(0.0, 0.0, 0.0),
    //     Vec(0.0, 1.0, 0.0), 45.0, aspect);

    // Raytracer raytracer(5, 10);
    // raytracer.set_background_color(Vec(0.5, 0.7, 1.0));
    // Scene scene(shapes);

    // Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    // image.save(outfile);

    return 0;
}
