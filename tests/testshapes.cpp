#define BOOST_TEST_MODULE TestShapes
#include <boost/test/unit_test.hpp>

#include "intersectioninfo.h"
#include "materials/diffusematerial.h"
#include "ray.h"
#include "shapes/boundingboxnode.h"
#include "shapes/shapelist.h"
#include "shapes/sphere.h"
#include "shapes/triangle.h"
#include "testutils.h"

namespace utf = boost::unit_test;

struct F {
    F() : material(std::make_shared<DiffuseMaterial>(Vec(0.5, 0.5, 0.5))) {}
    std::shared_ptr<Material> material;
};

BOOST_FIXTURE_TEST_SUITE(suite1, F)

BOOST_AUTO_TEST_CASE(
    test_intersect_sphere, *utf::tolerance(TestUtils::TOLERANCE)) {

    Ray r(Vec(0.0, 0.0, 2.0, 1.0), Vec(0.0, 0.0, -1.0));
    Sphere sphere(Vec(0.0, 0.0, 0.0, 1.0), 1.0, material);

    IntersectionInfo hit_info;

    BOOST_REQUIRE_EQUAL(sphere.intersect(r, 0.0, 10.0, hit_info), true);
    BOOST_TEST(hit_info.t_hit == 1.0);
    BOOST_REQUIRE_EQUAL(hit_info.normal, Vec(0.0, 0.0, 1.0));
}

BOOST_AUTO_TEST_CASE(
    test_not_intersect_sphere, *utf::tolerance(TestUtils::TOLERANCE)) {

    Ray r(Vec(5.0, 5.0, 2.0, 1.0), Vec(5.0, 5.0, -1.0));
    Sphere sphere(Vec(0.0, 0.0, 0.0, 1.0), 1.0, material);

    IntersectionInfo hit_info;

    BOOST_REQUIRE_EQUAL(sphere.intersect(r, 0.0, 10.0, hit_info), false);
}

BOOST_AUTO_TEST_CASE(test_intersect_sphere_not_within_range) {

    Ray r(Vec(0.0, 0.0, 2.0, 1.0), Vec(0.0, 0.0, -1.0));
    Sphere sphere(Vec(0.0, 0.0, 0.0, 1.0), 1.0, material);

    IntersectionInfo hit_info;

    BOOST_REQUIRE_EQUAL(sphere.intersect(r, -10.0, 0.0, hit_info), false);
}

BOOST_AUTO_TEST_CASE(test_intersect_triangle) {

    Ray r(Vec(0.5, -0.5, 1.0, 1.0), Vec(0.5, -0.5, -1.0));
    Triangle tri(Vec(1.0, -1.0, 0.0, 1.0), Vec(1.0, 1.0, 0.0, 1.0),
        Vec(-1.0, -1.0, 0.0, 1.0), material);

    IntersectionInfo hit_info;

    BOOST_REQUIRE_EQUAL(tri.intersect(r, 0.0, 10.0, hit_info), true);
    BOOST_TEST(hit_info.t_hit == 1.0);
    BOOST_REQUIRE_EQUAL(hit_info.normal, Vec(0.0, 0.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_not_intersect_triangle) {

    Ray r(Vec(-1.0, 1.0, 1.0, 1.0), Vec(-1.0, 1.0, -1.0));
    Triangle tri(Vec(1.0, -1.0, 0.0, 1.0), Vec(1.0, 1.0, 0.0, 1.0),
        Vec(-1.0, -1.0, 0.0, 1.0), material);

    IntersectionInfo hit_info;

    BOOST_REQUIRE_EQUAL(tri.intersect(r, 0.0, 10.0, hit_info), false);
}

BOOST_AUTO_TEST_CASE(test_intersect_triangle_not_within_range) {

    Ray r(Vec(0.5, -0.5, 1.0, 1.0), Vec(0.5, -0.5, -1.0));
    Triangle tri(Vec(1.0, -1.0, 0.0, 1.0), Vec(1.0, 1.0, 0.0, 1.0),
        Vec(-1.0, -1.0, 0.0, 1.0), material);

    IntersectionInfo hit_info;

    BOOST_REQUIRE_EQUAL(tri.intersect(r, -10.0, 0.0, hit_info), false);
}

BOOST_AUTO_TEST_CASE(test_intersect_list) {

    std::shared_ptr<Triangle> tri1
        = std::make_shared<Triangle>(Vec(1.0, -1.0, 0.0, 1.0),
            Vec(1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);
    std::shared_ptr<Triangle> tri2
        = std::make_shared<Triangle>(Vec(1.0, 1.0, 0.0, 1.0),
            Vec(-1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);
    std::shared_ptr<Sphere> sphere
        = std::make_shared<Sphere>(Vec(0.0, 0.0, 0.0, 1.0), 1.0, material);

    ShapeList list({ tri1, tri2, sphere });

    IntersectionInfo hit_info;

    Ray r1(Vec(0.0, 0.0, 2.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(list.intersect(r1, 0.0, 10.0, hit_info), true);
    BOOST_TEST(hit_info.t_hit == 1.0);
    BOOST_REQUIRE_EQUAL(hit_info.normal, Vec(0.0, 0.0, 1.0));
    BOOST_REQUIRE_EQUAL(hit_info.position, Vec(0.0, 0.0, 1.0, 1.0));

    Ray r2(Vec(0.9, 0.9, 1.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(list.intersect(r2, 0.0, 10.0, hit_info), true);
    BOOST_TEST(hit_info.t_hit == 1.0);
    BOOST_REQUIRE_EQUAL(hit_info.normal, Vec(0.0, 0.0, 1.0));
    BOOST_REQUIRE_EQUAL(hit_info.position, Vec(0.9, 0.9, 0.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_not_intersect_list) {

    std::shared_ptr<Triangle> tri1
        = std::make_shared<Triangle>(Vec(1.0, -1.0, 0.0, 1.0),
            Vec(1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);
    std::shared_ptr<Triangle> tri2
        = std::make_shared<Triangle>(Vec(1.0, 1.0, 0.0, 1.0),
            Vec(-1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);
    std::shared_ptr<Sphere> sphere
        = std::make_shared<Sphere>(Vec(0.0, 0.0, 0.0, 1.0), 1.0, material);

    ShapeList list({ tri1, tri2, sphere });

    IntersectionInfo hit_info;

    Ray r1(Vec(10.0, 10.0, 2.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(list.intersect(r1, 0.0, 10.0, hit_info), false);

    Ray r2(Vec(0.0, 0.0, 2.0, 1.0), Vec(1.0, 0.1, -0.1));

    BOOST_REQUIRE_EQUAL(list.intersect(r2, 0.0, 10.0, hit_info), false);
}

BOOST_AUTO_TEST_CASE(test_intersect_list_not_within_range) {

    std::shared_ptr<Triangle> tri1
        = std::make_shared<Triangle>(Vec(1.0, -1.0, 0.0, 1.0),
            Vec(1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);
    std::shared_ptr<Triangle> tri2
        = std::make_shared<Triangle>(Vec(1.0, 1.0, 0.0, 1.0),
            Vec(-1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);
    std::shared_ptr<Sphere> sphere
        = std::make_shared<Sphere>(Vec(0.0, 0.0, 0.0, 1.0), 1.0, material);

    ShapeList list({ tri1, tri2, sphere });

    IntersectionInfo hit_info;

    Ray r1(Vec(0.0, 0.0, 2.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(list.intersect(r1, -10.0, 0.0, hit_info), false);

    Ray r2(Vec(0.9, 0.9, 1.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(list.intersect(r2, -10.0, 0.0, hit_info), false);
}

BOOST_AUTO_TEST_CASE(test_intersect_box) {

    std::shared_ptr<Triangle> tri1
        = std::make_shared<Triangle>(Vec(1.0, -1.0, 0.0, 1.0),
            Vec(1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);
    std::shared_ptr<Triangle> tri2
        = std::make_shared<Triangle>(Vec(1.0, 1.0, 0.0, 1.0),
            Vec(-1.0, 1.0, 0.0, 1.0), Vec(-1.0, -1.0, 0.0, 1.0), material);

    std::shared_ptr<Triangle> tri3
        = std::make_shared<Triangle>(Vec(5.0, -1.0, -2.0, 1.0),
            Vec(5.0, 1.0, -2.0, 1.0), Vec(3.0, -1.0, -2.0, 1.0), material);
    std::shared_ptr<Triangle> tri4
        = std::make_shared<Triangle>(Vec(5.0, 1.0, -2.0, 1.0),
            Vec(3.0, 1.0, -2.0, 1.0), Vec(3.0, -1.0, -2.0, 1.0), material);

    std::shared_ptr<Sphere> sphere
        = std::make_shared<Sphere>(Vec(2.0, 0.0, 0.0, 1.0), 1.0, material);

    std::shared_ptr<ShapeList> list = std::make_shared<ShapeList>(
        std::vector<std::shared_ptr<AbstractShape>>{
            tri1, tri2, tri3, tri4, sphere });

    BoundingBoxNode root(list);

    IntersectionInfo hit_info;

    Ray r1(Vec(2.0, 0.0, 2.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(root.intersect(r1, 0.0, 10.0, hit_info), true);
    BOOST_TEST(hit_info.t_hit == 1.0);
    BOOST_REQUIRE_EQUAL(hit_info.normal, Vec(0.0, 0.0, 1.0));
    BOOST_REQUIRE_EQUAL(hit_info.position, Vec(2.0, 0.0, 1.0, 1.0));

    Ray r2(Vec(0.9, 0.9, 1.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(root.intersect(r2, 0.0, 10.0, hit_info), true);
    BOOST_TEST(hit_info.t_hit == 1.0);
    BOOST_REQUIRE_EQUAL(hit_info.normal, Vec(0.0, 0.0, 1.0));
    BOOST_REQUIRE_EQUAL(hit_info.position, Vec(0.9, 0.9, 0.0, 1.0));

    Ray r3(Vec(4.0, 0.0, 1.0, 1.0), Vec(0.0, 0.0, -1.0));

    BOOST_REQUIRE_EQUAL(root.intersect(r3, 0.0, 10.0, hit_info), true);
    BOOST_TEST(hit_info.t_hit == 3.0);
    BOOST_REQUIRE_EQUAL(hit_info.normal, Vec(0.0, 0.0, 1.0));
    BOOST_REQUIRE_EQUAL(hit_info.position, Vec(4.0, 0.0, -2.0, 1.0));
}

BOOST_AUTO_TEST_SUITE_END()
