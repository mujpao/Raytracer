#define BOOST_TEST_MODULE TestBoundingBox
#include <boost/test/unit_test.hpp>

#include "boundingbox.h"
#include "ray.h"

BOOST_AUTO_TEST_CASE(test_min_max) {
    BoundingBox b1(Vec(-1.0, -2.0, -3.0, 1.0), Vec(1.0, 2.0, 3.0, 1.0));
    BoundingBox b2(Vec(1.0, 2.0, 3.0, 1.0), Vec(-1.0, -2.0, -3.0, 1.0));

    Vec min(-1.0, -2.0, -3.0, 1.0);
    Vec max(1.0, 2.0, 3.0, 1.0);

    BOOST_REQUIRE_EQUAL(b1.min(), min);
    BOOST_REQUIRE_EQUAL(b1.max(), max);
    BOOST_REQUIRE_EQUAL(b2.min(), min);
    BOOST_REQUIRE_EQUAL(b2.max(), max);
}

BOOST_AUTO_TEST_CASE(test_intersect1) {
    BoundingBox box(Vec(-1.0, -1.0, 1.0, 1.0), Vec(1.0, 1.0, -1.0, 1.0));
    Ray r1(Vec(0.0, 0.0, 4.0, 1.0), Vec(0.0, 0.0, -1.0));
    Ray r2(Vec(0.0, 0.0, 4.0, 1.0), Vec(0.0, 0.0, 1.0));
    Ray r3(Vec(0.0, 0.0, 4.0, 1.0), Vec(0.1, 0.1, -1.0));

    BOOST_REQUIRE_EQUAL(box.intersect(r1, 0.0, 10.0), true);
    BOOST_REQUIRE_EQUAL(box.intersect(r2, 0.0, 10.0), false);
    BOOST_REQUIRE_EQUAL(box.intersect(r3, 0.0, 10.0), true);
}

BOOST_AUTO_TEST_CASE(test_ray_origin_inside_box) {
    Ray r(Vec(0.0, 0.0, 0.0, 1.0), Vec(0.0, 0.0, -1.0));
    BoundingBox box(Vec(-1.0, -1.0, 1.0), Vec(1.0, 1.0, -1.0));

    BOOST_REQUIRE_EQUAL(box.intersect(r, 0.0, 10.0), true);
}

BOOST_AUTO_TEST_CASE(test_intersect_2d_plane) {
    Ray r(Vec(0.0, 0.0, 1.0, 1.0), Vec(0.0, 0.0, -1.0));
    BoundingBox box(Vec(-1.0, -1.0, 0.0, 1.0), Vec(1.0, 1.0, 0.0, 1.0));

    BOOST_REQUIRE_EQUAL(box.intersect(r, 0.0, 10.0), true);
}

BOOST_AUTO_TEST_CASE(test_not_intersect_2d_plane) {
    Ray r(Vec(0.0, -10.0, 1.0, 1.0), Vec(0.0, -10.0, -1.0));
    BoundingBox box(Vec(-1.0, -1.0, 0.0, 1.0), Vec(1.0, 1.0, 0.0, 1.0));

    BOOST_REQUIRE_EQUAL(box.intersect(r, 0.0, 10.0), false);
}
