#include "camera.h"
#include "image.h"
#include "importer.h"
#include "materials/diffusematerial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/shapelist.h"
#include "shapes/triangle.h"

int main() {
    // std::string file("/home/mujpao/Documents/3d/defaultcube.obj");
    std::string file("/home/mujpao/Documents/3d/simplescene.fbx");

    Importer importer;

    std::shared_ptr<ShapeList> shapes = importer.read_objects(file);

    std::string outfile("importexample.png");

    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(27.0, 11.03, 0.855), Vec(0.0, 0.0, 0.0),
        Vec(0.0, 1.0, 0.0), 45.0, aspect);

    Raytracer raytracer(5, 10);
    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));
    Scene scene(shapes);

    Image image = raytracer.raytrace(camera, scene, width, aspect, true);
    image.save(outfile);

    return 0;
}
