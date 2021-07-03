#define BOOST_TEST_MODULE TestVec
#include <boost/test/unit_test.hpp>

#include "math/vec.h"
#include "testutils.h"

#include <cmath>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(test_constructors, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v1(1.0, 2.0, 3.0);
    BOOST_TEST(v1.x() == 1.0);
    BOOST_TEST(v1.y() == 2.0);
    BOOST_TEST(v1.z() == 3.0);
    BOOST_TEST(v1.w() == 0.0);

    BOOST_TEST(v1[0] == 1.0);
    BOOST_TEST(v1[1] == 2.0);
    BOOST_TEST(v1[2] == 3.0);
    BOOST_TEST(v1[3] == 0.0);

    Vec v2;
    BOOST_TEST(v2.x() == 0.0);
    BOOST_TEST(v2.y() == 0.0);
    BOOST_TEST(v2.z() == 0.0);
    BOOST_TEST(v2.w() == 0.0);

    BOOST_TEST(v2[0] == 0.0);
    BOOST_TEST(v2[1] == 0.0);
    BOOST_TEST(v2[2] == 0.0);
    BOOST_TEST(v2[3] == 0.0);

    Vec v3(1.0, 2.0, 3.0, 4.3);
    BOOST_TEST(v3.x() == 1.0);
    BOOST_TEST(v3.y() == 2.0);
    BOOST_TEST(v3.z() == 3.0);
    BOOST_TEST(v3.w() == 4.3);

    BOOST_TEST(v3[0] == 1.0);
    BOOST_TEST(v3[1] == 2.0);
    BOOST_TEST(v3[2] == 3.0);
    BOOST_TEST(v3[3] == 4.3);
}

BOOST_AUTO_TEST_CASE(test_subscript, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v(1.0, 2.0, 3.0);
    v[0] = 5.0;
    v[1] = 10.0;
    v[2] = 20.0;
    v[3] = 5.0;

    BOOST_TEST(v.x() == 5.0);
    BOOST_TEST(v.y() == 10.0);
    BOOST_TEST(v.z() == 20.0);
    BOOST_TEST(v.w() == 5.0);

    BOOST_TEST(v[0] == 5.0);
    BOOST_TEST(v[1] == 10.0);
    BOOST_TEST(v[2] == 20.0);
    BOOST_TEST(v[3] == 5.0);
}

BOOST_AUTO_TEST_CASE(test_add, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v1(3.0, 4.0, 5.0);
    Vec v2(6.0, 7.0, 8.0);

    BOOST_REQUIRE_EQUAL(v1 + v2, Vec(9.0, 11.0, 13.0, 0.0));
}

BOOST_AUTO_TEST_CASE(test_subtract, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v1(3.0, 4.0, 5.0);
    Vec v2(6.0, 7.0, 8.0);

    BOOST_REQUIRE_EQUAL(v1 - v2, Vec(-3.0, -3.0, -3.0, 0.0));
}

BOOST_AUTO_TEST_CASE(test_unary_minus, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v(3.0, -4.0, 5.0);

    BOOST_REQUIRE_EQUAL(-v, -1.0 * v);
}

BOOST_AUTO_TEST_CASE(
    test_multiply_scalar1, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v(1.0, 2.0, 3.0);

    BOOST_REQUIRE_EQUAL(v * 3.0, Vec(3.0, 6.0, 9.0, 0.0));
}

BOOST_AUTO_TEST_CASE(
    test_multiply_scalar2, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v(1.0, 2.0, 3.0);

    BOOST_REQUIRE_EQUAL(3.0 * v, Vec(3.0, 6.0, 9.0, 0.0));
}

BOOST_AUTO_TEST_CASE(test_multiply_vec, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v1(1.0, 2.0, 3.0);
    Vec v2(10.0, 4.0, 12.0);

    BOOST_REQUIRE_EQUAL(v1 * v2, Vec(10.0, 8.0, 36.0, 0.0));
}

BOOST_AUTO_TEST_CASE(
    test_divide_scalar, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v(10.0, 20.0, 30.0);

    BOOST_REQUIRE_EQUAL(v / 2.0, Vec(5.0, 10.0, 15.0, 0.0));
}

BOOST_AUTO_TEST_CASE(test_normalize, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v1(1.0, 0.0, 0.0);
    v1 = Vec::normalize(v1);

    BOOST_REQUIRE_EQUAL(Vec::normalize(v1), Vec(1.0, 0.0, 0.0, 0.0));

    Vec v2(1.0, -1.0, 1.0);
    v2 = Vec::normalize(v2);

    BOOST_REQUIRE_EQUAL(Vec::normalize(v2),
        Vec(1.0 / std::sqrt(3.0), -1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0),
            0.0));
}

BOOST_AUTO_TEST_CASE(test_assign, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v1(3.0, 4.0, 5.0);
    Vec v2 = v1;

    BOOST_REQUIRE_EQUAL(v2, v1);
}

BOOST_AUTO_TEST_CASE(test_convert) {
    Vec v(1.0, 2.0, 3.0, 0.0);
    v = Vec::to_point(v);
    BOOST_REQUIRE_EQUAL(v, Vec(1.0, 2.0, 3.0, 1.0));
    v = Vec::to_vec(v);
    BOOST_REQUIRE_EQUAL(v, Vec(1.0, 2.0, 3.0, 0.0));
}

BOOST_AUTO_TEST_CASE(test_dist, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec a(1.0, 2.0, 3.0);
    Vec b(10.0, 9.0, 8.0);
    BOOST_TEST(Vec::dist(a, b) == 12.449899597988733);
}

BOOST_AUTO_TEST_CASE(test_length, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec a(1.0, 2.0, 3.0);
    BOOST_TEST(Vec::length_squared(a) == 14.0);
    BOOST_TEST(Vec::length(a) == std::sqrt(14.0));
}
