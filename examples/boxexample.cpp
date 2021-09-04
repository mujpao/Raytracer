#include "camera.h"
#include "image.h"
#include "materials/diffusematerial.h"
#include "materials/lightmaterial.h"
#include "math/transform.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/rect.h"
#include "shapes/shapelist.h"

int main() {
    // Cornell box
    std::string outfile("boxexample.png");

    int width = 600;
    double aspect = 1.0;
    Camera camera(Vec(278.0, 273.0, -800.0), Vec(278.0, 273.0, 0.0),
        Vec(0.0, 1.0, 0.0), 40.0, aspect);

    auto red = std::make_shared<DiffuseMaterial>(Vec(0.65, 0.05, 0.05));
    auto white = std::make_shared<DiffuseMaterial>(Vec(0.73, 0.73, 0.73));
    auto green = std::make_shared<DiffuseMaterial>(Vec(0.12, 0.45, 0.15));
    auto light_color = std::make_shared<LightMaterial>(Vec(15.0, 15.0, 15.0));

    Vec p1(552.8, 0.0, 0.0);
    Vec p2(0.0, 0.0, 0.0);
    Vec p3(0.0, 0.0, 559.2);
    Vec p4(549.6, 0.0, 559.2);
    auto floor = std::make_shared<Rect>(p1, p2, p3, p4, white);

    p1 = Vec(343.0, 548.79, 227.0);
    p2 = Vec(343.0, 548.79, 332.0);
    p3 = Vec(213.0, 548.79, 332.0);
    p4 = Vec(213.0, 548.79, 227.0);
    auto light = std::make_shared<Rect>(p1, p2, p3, p4, light_color);

    p1 = Vec(556.0, 548.8, 0.0);
    p2 = Vec(556.0, 548.8, 559.2);
    p3 = Vec(0.0, 548.8, 559.2);
    p4 = Vec(0.0, 548.8, 0.0);
    auto ceiling = std::make_shared<Rect>(p1, p2, p3, p4, white);

    p1 = Vec(549.6, 0.0, 559.2);
    p2 = Vec(0.0, 0.0, 559.2);
    p3 = Vec(0.0, 548.8, 559.2);
    p4 = Vec(556.0, 548.8, 559.2);
    auto back = std::make_shared<Rect>(p1, p2, p3, p4, white);

    p1 = Vec(0.0, 0.0, 559.2);
    p2 = Vec(0.0, 0.0, 0.0);
    p3 = Vec(0.0, 548.8, 0.0);
    p4 = Vec(0.0, 548.8, 559.2);
    auto right = std::make_shared<Rect>(p1, p2, p3, p4, green);

    p1 = Vec(552.8, 0.0, 0.0);
    p2 = Vec(549.6, 0.0, 559.2);
    p3 = Vec(556.0, 548.8, 559.2);
    p4 = Vec(556.0, 548.8, 0.0);
    auto left = std::make_shared<Rect>(p1, p2, p3, p4, red);

    auto short_block = std::make_shared<
        ShapeList>(std::vector<std::shared_ptr<AbstractShape>>{
        std::make_shared<Rect>(Vec(130.0, 165.0, 65.0), Vec(82.0, 165.0, 225.0),
            Vec(240.0, 165.0, 272.0), Vec(290.0, 165.0, 114.0), white),
        std::make_shared<Rect>(Vec(290.0, 0.0, 114.0), Vec(290.0, 165.0, 114.0),
            Vec(240.0, 165.0, 272.0), Vec(240.0, 0.0, 272.0), white),
        std::make_shared<Rect>(Vec(130.0, 0.0, 65.0), Vec(130.0, 165.0, 65.0),
            Vec(290.0, 165.0, 114.0), Vec(290.0, 0.0, 114.0), white),
        std::make_shared<Rect>(Vec(82.0, 0.0, 225.0), Vec(82.0, 165.0, 225.0),
            Vec(130.0, 165.0, 65.0), Vec(130.0, 0.0, 65.0), white),
        std::make_shared<Rect>(Vec(240.0, 0.0, 272.0), Vec(240.0, 165.0, 272.0),
            Vec(82.0, 165.0, 225.0), Vec(82.0, 0.0, 225.0), white) });

    auto tall_block = std::make_shared<
        ShapeList>(std::vector<std::shared_ptr<AbstractShape>>{
        std::make_shared<Rect>(Vec(423.0, 330.0, 247.0),
            Vec(265.0, 330.0, 296.0), Vec(314.0, 330.0, 456.0),
            Vec(472.0, 330.0, 406.0), white),
        std::make_shared<Rect>(Vec(423.0, 0.0, 247.0), Vec(423.0, 330.0, 247.0),
            Vec(472.0, 330.0, 406.0), Vec(472.0, 0.0, 406.0), white),
        std::make_shared<Rect>(Vec(472.0, 0.0, 406.0), Vec(472.0, 330.0, 406.0),
            Vec(314.0, 330.0, 456.0), Vec(314.0, 0.0, 456.0), white),
        std::make_shared<Rect>(Vec(314.0, 0.0, 456.0), Vec(314.0, 330.0, 456.0),
            Vec(265.0, 330.0, 296.0), Vec(265.0, 0.0, 296.0), white),
        std::make_shared<Rect>(Vec(265.0, 0.0, 296.0), Vec(265.0, 330.0, 296.0),
            Vec(423.0, 330.0, 247.0), Vec(423.0, 0.0, 247.0), white) });

    Scene scene(
        { floor, light, ceiling, back, right, left, short_block, tall_block });

    Raytracer raytracer(50, 600);
    // Raytracer raytracer(5, 10);
    // raytracer.set_background_color(Vec(0.1, 0.1, 0.1));

    Image image = raytracer.raytrace(scene, camera, width, true);
    image.save(outfile);

    return 0;
}
