#define BOOST_TEST_MODULE TestRenderScene
#include <boost/test/unit_test.hpp>

#include "camera.h"
#include "image.h"
#include "light.h"
#include "materials/diffusematerial.h"
#include "materials/phongmaterial.h"
#include "raytracer.h"
#include "scene.h"
#include "shapes/sphere.h"
#include "shapes/triangle.h"

#include <filesystem>

void compare_images(const Image& i1, const Image& i2, double tolerance = 0.1) {
    BOOST_REQUIRE_EQUAL(i1.width(), i2.width());
    BOOST_REQUIRE_EQUAL(i1.height(), i2.height());

    unsigned long num_diff = 0;

    // Compare image to original image
    for (unsigned int i = 0; i < i1.height(); ++i) {
        for (unsigned int j = 0; j < i1.width(); ++j) {
            std::array<unsigned char, 3> c1(i1.pixel_color(i, j));
            std::array<unsigned char, 3> c2(i2.pixel_color(i, j));
            for (unsigned int k = 0; k < 3; ++k) {
                int value1 = (int)c1[k];
                int value2 = (int)c2[k];

                if (std::abs(value1 - value2) > 5) {
                    ++num_diff;
                    break;
                }
            }
        }
    }

    double total_pixels = (double)i1.width() * i1.height();

    double pct_different = (double)num_diff / total_pixels;
    BOOST_REQUIRE_SMALL(pct_different, tolerance);
}

BOOST_AUTO_TEST_SUITE(test_render_scene)

BOOST_AUTO_TEST_CASE(test_render_scene1) {
    int width = 640;
    double aspect = width / 480.0;

    std::array<Camera, 4> cameras{ Camera(Vec(0.0, 0.0, 4.0),
                                       Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
                                       30.0, aspect),
        Camera(Vec(0.0, -3.0, 3.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
            30.0, aspect),
        Camera(Vec(-4.0, 0.0, 1.0), Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 1.0),
            45.0, aspect),
        Camera(Vec(-4.0, -4.0, 4.0), Vec(1.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
            30.0, aspect) };

    auto mat = std::make_shared<PhongMaterial>(
        Vec(0.1, 0.1, 0.1), Vec(1.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0);

    Scene scene({ std::make_shared<Triangle>(Vec(-1.0, -1.0, 0.0),
                      Vec(1.0, -1.0, 0.0), Vec(1.0, 1.0, 0.0), mat),
                    std::make_shared<Triangle>(Vec(-1.0, -1.0, 0.0),
                        Vec(1.0, 1.0, 0.0), Vec(-1.0, 1.0, 0.0), mat) },
        { std::make_shared<DirectionalLight>(
              Vec(0.5, 0.5, 0.5), Vec(0.0, 0.0, 1.0)),
            std::make_shared<PointLight>(
                Vec(1.0, 0.0, 0.0), Vec(0.5, 0.5, 0.5), Vec(4.0, 0.0, 4.0)) });

    std::string dir = std::filesystem::path(__FILE__).parent_path().string()
        + "/testscenes/";

    std::array<std::string, 4> filenames{ "scene1-camera1.jpg",
        "scene1-camera2.jpg", "scene1-camera3.jpg", "scene1-camera4.jpg" };

    Raytracer r(5);

    for (std::size_t i = 0; i < cameras.size(); ++i) {
        Image rendered_image = r.raytrace(scene, cameras[i], width);
        Image compare_to(dir + filenames[i]);
        compare_images(rendered_image, compare_to);
    }
}

BOOST_AUTO_TEST_CASE(test_render_scene2) {
    int width = 640;
    double aspect = width / 480.0;

    std::array<Camera, 3> cameras{ Camera(Vec(-2.0, -2.0, 2.0),
                                       Vec(0.0, 0.0, 0.0), Vec(1.0, 1.0, 2.0),
                                       60.0, aspect),
        Camera(Vec(2.0, 2.0, 2.0), Vec(0.0, 0.0, 0.0), Vec(-1.0, -1.0, 2.0),
            60.0, aspect),
        Camera(Vec(-2.0, -2.0, -2.0), Vec(0.0, 0.0, 0.0), Vec(-1.0, -1.0, 2.0),
            60.0, aspect) };

    std::array<Vec, 8> v{ Vec(-1.0, -1.0, -1.0), Vec(1.0, -1.0, -1.0),
        Vec(1.0, 1.0, -1.0), Vec(-1.0, 1.0, -1.0), Vec(-1.0, -1.0, 1.0),
        Vec(1.0, -1.0, 1.0), Vec(1.0, 1.0, 1.0), Vec(-1.0, 1.0, 1.0) };

    std::array<std::shared_ptr<Material>, 6> m{
        std::make_shared<PhongMaterial>(
            Vec(0.5, 0.0, 0.5), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0),
        std::make_shared<PhongMaterial>(
            Vec(0.5, 1.0, 0.5), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0),
        std::make_shared<PhongMaterial>(
            Vec(1.0, 0.5, 0.5), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0),
        std::make_shared<PhongMaterial>(
            Vec(0.0, 0.5, 0.5), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0),
        std::make_shared<PhongMaterial>(
            Vec(0.5, 0.5, 0.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0),
        std::make_shared<PhongMaterial>(
            Vec(0.5, 0.5, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0)
    };

    std::shared_ptr<Material> sphere_mat = std::make_shared<PhongMaterial>(
        Vec(1.0, 1.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 0.0, 0.0), 0.0);

    double sphere_rad = 0.15;

    Scene scene({
        std::make_shared<Triangle>(v[0], v[1], v[5], m[0]),
        std::make_shared<Triangle>(v[0], v[5], v[4], m[0]),

        std::make_shared<Triangle>(v[3], v[7], v[6], m[1]),
        std::make_shared<Triangle>(v[3], v[6], v[2], m[1]),

        std::make_shared<Triangle>(v[1], v[2], v[6], m[2]),
        std::make_shared<Triangle>(v[1], v[6], v[5], m[2]),

        std::make_shared<Triangle>(v[0], v[7], v[3], m[3]),
        std::make_shared<Triangle>(v[0], v[4], v[7], m[3]),

        std::make_shared<Triangle>(v[0], v[3], v[2], m[4]),
        std::make_shared<Triangle>(v[0], v[2], v[1], m[4]),

        std::make_shared<Triangle>(v[4], v[5], v[6], m[5]),
        std::make_shared<Triangle>(v[4], v[6], v[7], m[5]),

        std::make_shared<Sphere>(Vec(1.0, 0.0, 0.0), sphere_rad, sphere_mat),

        std::make_shared<Sphere>(Vec(-0.5, 1.0, -0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, 1.0, 0.5), sphere_rad, sphere_mat),

        std::make_shared<Sphere>(Vec(0.0, 0.0, 1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(-0.5, -0.5, 1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, 0.5, 1.0), sphere_rad, sphere_mat),

        std::make_shared<Sphere>(Vec(-1.0, -0.5, -0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(-1.0, -0.5, 0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(-1.0, 0.5, 0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(-1.0, 0.5, -0.5), sphere_rad, sphere_mat),

        std::make_shared<Sphere>(Vec(-0.5, -1.0, -0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(-0.5, -1.0, 0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, -1.0, 0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, -1.0, -0.5), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.0, -1.0, 0.0), sphere_rad, sphere_mat),

        std::make_shared<Sphere>(Vec(-0.5, -0.5, -1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(-0.5, 0.0, -1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(-0.5, 0.5, -1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, -0.5, -1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, -0.5, -1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, 0.0, -1.0), sphere_rad, sphere_mat),
        std::make_shared<Sphere>(Vec(0.5, 0.5, -1.0), sphere_rad, sphere_mat),
    });

    std::string dir = std::filesystem::path(__FILE__).parent_path().string()
        + "/testscenes/";

    std::array<std::string, 3> filenames{ "scene2-camera1.jpg",
        "scene2-camera2.jpg", "scene2-camera3.jpg" };

    Raytracer r(5);

    for (std::size_t i = 0; i < cameras.size(); ++i) {
        Image rendered_image = r.raytrace(scene, cameras[i], width);
        Image compare_to(dir + filenames[i]);
        compare_images(rendered_image, compare_to);
    }
}

BOOST_AUTO_TEST_CASE(test_render_diffuse_scene) {
    int width = 400;
    double aspect = 16.0 / 9.0;
    Camera camera(Vec(0.0, 0.0, 1.0), Vec(0.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0),
        45.0, aspect);

    auto diffuse_material
        = std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5));

    Scene scene(
        { std::make_shared<Sphere>(Vec(0.0, 0.0, -1.0), 0.5, diffuse_material),
            std::make_shared<Sphere>(
                Vec(0.0, -100.5, -1.0), 100.0, diffuse_material) });

    Raytracer raytracer(50, 100);
    raytracer.set_background_color(Vec(0.5, 0.7, 1.0));

    std::string dir = std::filesystem::path(__FILE__).parent_path().string()
        + "/testscenes/";

    std::string filename("diffusescene.png");

    Image rendered_image = raytracer.raytrace(scene, camera, width, true);
    rendered_image.save(filename);

    Image compare_to(dir + filename);
    compare_images(rendered_image, compare_to);
}

BOOST_AUTO_TEST_SUITE_END()
