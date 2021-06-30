#define BOOST_TEST_MODULE TestRenderScene
#include <boost/test/unit_test.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb_image.h"

#include "camera.h"
#include "image.h"
#include "raytracer.h"
#include "readfile.h"
#include "scene.h"

#include "configure.h"

struct CompareImagesFixture {
  CompareImagesFixture(const std::string &scene_name,
                       const char *extension = ".jpg", double tolerance = 0.1)
      : m_scene_dir(std::string(SOURCE_DIR) + "/scenes/testscenes/"),
        m_scene_name(scene_name) {
    std::string infile(m_scene_dir + m_scene_name + ".test");
    int max_depth = 5;
    Camera cam;
    Scene scene;
    std::string temp;
    readfile(infile.c_str(), cam, scene, max_depth, temp);
    Raytracer r(max_depth);
    Image rendered_image = r.raytrace(cam, scene);

    std::string compare_to_file(m_scene_dir + m_scene_name + extension);

    int x, y, n;
    unsigned char *data = stbi_load(compare_to_file.c_str(), &x, &y, &n, 0);

    Image compare_to(data, x, y);
    stbi_image_free(data);

    BOOST_REQUIRE_EQUAL(rendered_image.width(), compare_to.width());
    BOOST_REQUIRE_EQUAL(rendered_image.height(), compare_to.height());

    unsigned long num_diff = 0;

    // Compare image to original image
    for (unsigned int i = 0; i < rendered_image.height(); ++i) {
      for (unsigned int j = 0; j < rendered_image.width(); ++j) {
        std::array<unsigned char, 3> c1(rendered_image.pixel_color(i, j));
        std::array<unsigned char, 3> c2(compare_to.pixel_color(i, j));
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

    double total_pixels =
        (double)rendered_image.width() * rendered_image.height();

    double pct_different = (double)num_diff / total_pixels;
    BOOST_REQUIRE_SMALL(pct_different, tolerance);
  }

  ~CompareImagesFixture() {}

private:
  std::string m_scene_dir;
  std::string m_scene_name;
};

BOOST_AUTO_TEST_CASE(test_render_scene1_camera1) {
  CompareImagesFixture f("scene1-camera1");
}

BOOST_AUTO_TEST_CASE(test_render_scene1_camera2) {
  CompareImagesFixture f("scene1-camera2");
}

BOOST_AUTO_TEST_CASE(test_render_scene1_camera3) {
  CompareImagesFixture f("scene1-camera3");
}

BOOST_AUTO_TEST_CASE(test_render_scene1_camera4) {
  CompareImagesFixture f("scene1-camera4");
}

BOOST_AUTO_TEST_CASE(test_render_scene2_camera1) {
  CompareImagesFixture f("scene2-camera1");
}

BOOST_AUTO_TEST_CASE(test_render_scene2_camera2) {
  CompareImagesFixture f("scene2-camera2");
}

BOOST_AUTO_TEST_CASE(test_render_scene2_camera3) {
  CompareImagesFixture f("scene2-camera3");
}

BOOST_AUTO_TEST_CASE(test_render_scene3) { CompareImagesFixture f("scene3"); }

BOOST_AUTO_TEST_CASE(test_render_scene4_ambient) {
  CompareImagesFixture f("scene4-ambient", ".png", 0.01);
}

BOOST_AUTO_TEST_CASE(test_render_scene4_diffuse) {
  CompareImagesFixture f("scene4-diffuse", ".png", 0.01);
}

BOOST_AUTO_TEST_CASE(test_render_scene4_emission) {
  CompareImagesFixture f("scene4-emission", ".png", 0.01);
}

BOOST_AUTO_TEST_CASE(test_render_scene4_specular) {
  CompareImagesFixture f("scene4-specular", ".png", 0.01);
}
