#define BOOST_TEST_MODULE TestTransform
#include <boost/test/unit_test.hpp>

#include "math/mat4.h"
#include "math/transform.h"
#include "math/vec.h"
#include "testutils.h"
#include "utils.h"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(test_rotate, *utf::tolerance(TestUtils::TOLERANCE)) {
    Mat4 rotated1 = Transform::rotate(90.0, Vec(1.0, 0.0, 0.0));

    BOOST_TEST(rotated1(0, 0) == 1.0);
    BOOST_TEST(rotated1(0, 1) == 0.0);
    BOOST_TEST(rotated1(0, 2) == 0.0);
    BOOST_TEST(rotated1(0, 3) == 0.0);
    BOOST_TEST(rotated1(1, 0) == 0.0);
    BOOST_TEST(rotated1(1, 1) == 0.0);
    BOOST_TEST(rotated1(1, 2) == -1.0);
    BOOST_TEST(rotated1(1, 3) == 0.0);
    BOOST_TEST(rotated1(2, 0) == 0.0);
    BOOST_TEST(rotated1(2, 1) == 1.0);
    BOOST_TEST(rotated1(2, 2) == 0.0);
    BOOST_TEST(rotated1(2, 3) == 0.0);
    BOOST_TEST(rotated1(3, 0) == 0.0);
    BOOST_TEST(rotated1(3, 1) == 0.0);
    BOOST_TEST(rotated1(3, 2) == 0.0);
    BOOST_TEST(rotated1(3, 3) == 1.0);
    BOOST_TEST(Transform::det3x3(rotated1) == 1.0);

    Mat4 rotated2 = Transform::rotate(90.0, Vec(0.0, 1.0, 0.0));

    BOOST_TEST(rotated2(0, 0) == 0.0);
    BOOST_TEST(rotated2(0, 1) == 0.0);
    BOOST_TEST(rotated2(0, 2) == 1.0);
    BOOST_TEST(rotated2(0, 3) == 0.0);
    BOOST_TEST(rotated2(1, 0) == 0.0);
    BOOST_TEST(rotated2(1, 1) == 1.0);
    BOOST_TEST(rotated2(1, 2) == 0.0);
    BOOST_TEST(rotated2(1, 3) == 0.0);
    BOOST_TEST(rotated2(2, 0) == -1.0);
    BOOST_TEST(rotated2(2, 1) == 0.0);
    BOOST_TEST(rotated2(2, 2) == 0.0);
    BOOST_TEST(rotated2(2, 3) == 0.0);
    BOOST_TEST(rotated2(3, 0) == 0.0);
    BOOST_TEST(rotated2(3, 1) == 0.0);
    BOOST_TEST(rotated2(3, 2) == 0.0);
    BOOST_TEST(rotated2(3, 3) == 1.0);
    BOOST_TEST(Transform::det3x3(rotated2) == 1.0);

    Mat4 rotated3 = Transform::rotate(90.0, Vec(0.0, 0.0, 1.0));

    BOOST_TEST(rotated3(0, 0) == 0.0);
    BOOST_TEST(rotated3(0, 1) == -1.0);
    BOOST_TEST(rotated3(0, 2) == 0.0);
    BOOST_TEST(rotated3(0, 3) == 0.0);
    BOOST_TEST(rotated3(1, 0) == 1.0);
    BOOST_TEST(rotated3(1, 1) == 0.0);
    BOOST_TEST(rotated3(1, 2) == 0.0);
    BOOST_TEST(rotated3(1, 3) == 0.0);
    BOOST_TEST(rotated3(2, 0) == 0.0);
    BOOST_TEST(rotated3(2, 1) == 0.0);
    BOOST_TEST(rotated3(2, 2) == 1.0);
    BOOST_TEST(rotated3(2, 3) == 0.0);
    BOOST_TEST(rotated3(3, 0) == 0.0);
    BOOST_TEST(rotated3(3, 1) == 0.0);
    BOOST_TEST(rotated3(3, 2) == 0.0);
    BOOST_TEST(rotated3(3, 3) == 1.0);
    BOOST_TEST(Transform::det3x3(rotated3) == 1.0);

    Mat4 rotated4 = Transform::rotate(70.0, Vec(10.0, -20.0, 3.0));

    BOOST_TEST(rotated4(0, 0) == 0.471289270373671);
    BOOST_TEST(rotated4(0, 1) == -0.383491683487794);
    BOOST_TEST(rotated4(0, 2) == -0.794242124497530);
    BOOST_TEST(rotated4(0, 3) == 0.0);
    BOOST_TEST(rotated4(1, 0) == -0.133584824704215);
    BOOST_TEST(rotated4(1, 1) == 0.859096651517677);
    BOOST_TEST(rotated4(1, 2) == -0.494072907534767);
    BOOST_TEST(rotated4(1, 3) == 0.0);
    BOOST_TEST(rotated4(2, 0) == 0.871803600726332);
    BOOST_TEST(rotated4(2, 1) == 0.338949955077164);
    BOOST_TEST(rotated4(2, 2) == 0.353654364759989);
    BOOST_TEST(rotated4(2, 3) == 0.0);
    BOOST_TEST(rotated4(3, 0) == 0.0);
    BOOST_TEST(rotated4(3, 1) == 0.0);
    BOOST_TEST(rotated4(3, 2) == 0.0);
    BOOST_TEST(rotated4(3, 3) == 1.0);
    BOOST_TEST(Transform::det3x3(rotated4) == 1.0);

    Vec v = Vec(1.0, 2.0, 3.0, 0.0);
    v = rotated4 * v;
    BOOST_TEST(v[0] == -2.678420470094508);
    BOOST_TEST(v[1] == 0.102389755726840);
    BOOST_TEST(v[2] == 2.610666605160627);
    BOOST_TEST(v[3] == 0.0);
}

BOOST_AUTO_TEST_CASE(test_scale, *utf::tolerance(TestUtils::TOLERANCE)) {
    Mat4 scale1 = Transform::scale(1.0, 1.0, 1.0);

    BOOST_TEST(scale1(0, 0) == 1.0);
    BOOST_TEST(scale1(0, 1) == 0.0);
    BOOST_TEST(scale1(0, 2) == 0.0);
    BOOST_TEST(scale1(0, 3) == 0.0);
    BOOST_TEST(scale1(1, 0) == 0.0);
    BOOST_TEST(scale1(1, 1) == 1.0);
    BOOST_TEST(scale1(1, 2) == 0.0);
    BOOST_TEST(scale1(1, 3) == 0.0);
    BOOST_TEST(scale1(2, 0) == 0.0);
    BOOST_TEST(scale1(2, 1) == 0.0);
    BOOST_TEST(scale1(2, 2) == 1.0);
    BOOST_TEST(scale1(2, 3) == 0.0);
    BOOST_TEST(scale1(3, 0) == 0.0);
    BOOST_TEST(scale1(3, 1) == 0.0);
    BOOST_TEST(scale1(3, 2) == 0.0);
    BOOST_TEST(scale1(3, 3) == 1.0);

    Mat4 scale2 = Transform::scale(5.0, -3.432, 21.3);

    BOOST_TEST(scale2(0, 0) == 5.0);
    BOOST_TEST(scale2(0, 1) == 0.0);
    BOOST_TEST(scale2(0, 2) == 0.0);
    BOOST_TEST(scale2(0, 3) == 0.0);
    BOOST_TEST(scale2(1, 0) == 0.0);
    BOOST_TEST(scale2(1, 1) == -3.432);
    BOOST_TEST(scale2(1, 2) == 0.0);
    BOOST_TEST(scale2(1, 3) == 0.0);
    BOOST_TEST(scale2(2, 0) == 0.0);
    BOOST_TEST(scale2(2, 1) == 0.0);
    BOOST_TEST(scale2(2, 2) == 21.3);
    BOOST_TEST(scale2(2, 3) == 0.0);
    BOOST_TEST(scale2(3, 0) == 0.0);
    BOOST_TEST(scale2(3, 1) == 0.0);
    BOOST_TEST(scale2(3, 2) == 0.0);
    BOOST_TEST(scale2(3, 3) == 1.0);
}

BOOST_AUTO_TEST_CASE(test_translate, *utf::tolerance(TestUtils::TOLERANCE)) {
    Mat4 translated1 = Transform::translate(1.0, 1.0, 1.0);

    BOOST_TEST(translated1(0, 0) == 1.0);
    BOOST_TEST(translated1(0, 1) == 0.0);
    BOOST_TEST(translated1(0, 2) == 0.0);
    BOOST_TEST(translated1(0, 3) == 1.0);
    BOOST_TEST(translated1(1, 0) == 0.0);
    BOOST_TEST(translated1(1, 1) == 1.0);
    BOOST_TEST(translated1(1, 2) == 0.0);
    BOOST_TEST(translated1(1, 3) == 1.0);
    BOOST_TEST(translated1(2, 0) == 0.0);
    BOOST_TEST(translated1(2, 1) == 0.0);
    BOOST_TEST(translated1(2, 2) == 1.0);
    BOOST_TEST(translated1(2, 3) == 1.0);
    BOOST_TEST(translated1(3, 0) == 0.0);
    BOOST_TEST(translated1(3, 1) == 0.0);
    BOOST_TEST(translated1(3, 2) == 0.0);
    BOOST_TEST(translated1(3, 3) == 1.0);

    Mat4 translated2 = Transform::translate(5.0, -3.432, 21.3);

    BOOST_TEST(translated2(0, 0) == 1.0);
    BOOST_TEST(translated2(0, 1) == 0.0);
    BOOST_TEST(translated2(0, 2) == 0.0);
    BOOST_TEST(translated2(0, 3) == 5.0);
    BOOST_TEST(translated2(1, 0) == 0.0);
    BOOST_TEST(translated2(1, 1) == 1.0);
    BOOST_TEST(translated2(1, 2) == 0.0);
    BOOST_TEST(translated2(1, 3) == -3.432);
    BOOST_TEST(translated2(2, 0) == 0.0);
    BOOST_TEST(translated2(2, 1) == 0.0);
    BOOST_TEST(translated2(2, 2) == 1.0);
    BOOST_TEST(translated2(2, 3) == 21.3);
    BOOST_TEST(translated2(3, 0) == 0.0);
    BOOST_TEST(translated2(3, 1) == 0.0);
    BOOST_TEST(translated2(3, 2) == 0.0);
    BOOST_TEST(translated2(3, 3) == 1.0);
}

BOOST_AUTO_TEST_CASE(test_dot, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec a(1.0, 0.0, 0.0);
    Vec b(1.0, 0.0, 0.0);

    BOOST_TEST(Transform::dot(a, b) == 1.0);

    Vec c(0.0, 1.0, 0.0);

    BOOST_TEST(Transform::dot(a, c) == 0.0);

    Vec d(0.375570427299602, 0.781683132211818, 0.318763245329810);
    Vec e(0.842963855279980, 0.751121346931999, 0.135462999234790);

    BOOST_TEST(Transform::dot(d, e) == 0.946911807724777);
}

BOOST_AUTO_TEST_CASE(test_cross, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec a(1.0, 0.0, 0.0);
    Vec b(0.0, 1.0, 0.0);

    BOOST_REQUIRE_EQUAL(Transform::cross(a, a), Vec(0.0, 0.0, 0.0));
    BOOST_REQUIRE_EQUAL(Transform::cross(a, b), Vec(0.0, 0.0, 1.0));
    BOOST_REQUIRE_EQUAL(Transform::cross(b, a), Vec(0.0, 0.0, -1.0));

    Vec c(0.375570427299602, 0.781683132211818, 0.318763245329810);
    Vec d(0.842963855279980, 0.751121346931999, 0.135462999234790);

    BOOST_REQUIRE_EQUAL(Transform::cross(c, d),
        Vec(-0.133540736643884, 0.217829997698879, -0.376831661515501));
    BOOST_REQUIRE_EQUAL(Transform::cross(d, c),
        Vec(0.133540736643884, -0.217829997698879, 0.376831661515501));
}

BOOST_AUTO_TEST_CASE(test_det3x3, *utf::tolerance(TestUtils::TOLERANCE)) {
    double m1[4][4] = { 1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 6.0, 0.0, 7.0, 8.0, 9.0,
        0.0, 0.0, 0.0, 0.0, 1.0 };

    Mat4 a(m1);

    BOOST_TEST(Transform::det3x3(a) == 0.0);

    double m2[4][4] = { 1.0, 4.0, 7.0, 0.0, 2.0, 5.0, 8.0, 0.0, 3.0, 6.0, 9.0,
        0.0, 0.0, 0.0, 0.0, 1.0 };

    Mat4 b(m2);

    BOOST_TEST(Transform::det3x3(b) == 0.0);

    Mat4 c(1.0);

    BOOST_TEST(Transform::det3x3(c) == 1.0);

    double m3[4][4] = { 8.426716313562338, 2.262987866030466, 2.800791359248318,
        0.0, 9.670135666161023, 5.575910938364416, 9.840544044027542, 0.0,
        5.327092299851457, 5.867961084823797, 4.194536698309856, 0.0, 0.0, 0.0,
        0.0, 1.0 };

    Mat4 d(m3);
    BOOST_TEST(Transform::det3x3(d) == -186.9311036497346);
}

BOOST_AUTO_TEST_CASE(test_det, *utf::tolerance(TestUtils::TOLERANCE)) {
    double m1[4][4] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0, 16.0 };

    Mat4 a(m1);

    BOOST_TEST(Transform::det(a) == 0.0);

    double m2[4][4] = { 1.0, 5.0, 9.0, 13.0, 2.0, 6.0, 10.0, 14.0, 3.0, 7.0,
        11.0, 15.0, 4.0, 8.0, 12.0, 16.0 };

    Mat4 b(m2);

    BOOST_TEST(Transform::det(b) == 0.0);

    Mat4 c(1.0);

    BOOST_TEST(Transform::det(c) == 1.0);

    double m3[4][4] = { 6.089890454058282, 8.821876541024963, 0.842936802020632,
        1.156350542365741, 8.008006706514379, 8.428596280087191,
        0.480231811934019, 2.321580081610167, 0.192677892390324,
        4.794441436245354, 9.286861317970306, 5.049215260831591,
        1.110481915805210, 7.110468420479518, 4.822240027970071,
        8.457436957249394 };

    Mat4 d(m3);
    BOOST_TEST(Transform::det(d) == -1131.813224140513);
}

BOOST_AUTO_TEST_CASE(test_inverse3x3, *utf::tolerance(TestUtils::TOLERANCE)) {
    Mat4 a(1.0);

    BOOST_REQUIRE_EQUAL(Transform::inverse3x3(a), Mat4(1.0));

    double m1[4][4] = { 0.960443348134518, 0.297213221762461, 0.770982635804027,
        0.0, 0.378177232791555, 0.186982390039708, 0.947883487107537, 0.0,
        0.890650028568978, 0.916382599638053, 0.503950322257627, 0.0, 0.0, 0.0,
        0.0, 1.0 };

    double m2[4][4] = { 1.885562417589953, -1.355585499548645,
        -0.334951214131064, 0.0, -1.591563933020902, 0.493454207868426,
        1.506757764231940, 0.0, -0.438326392319080, 1.498479871406530,
        -0.163592094171723, 0.0, 0.0, 0.0, 0.0, 1.0 };

    Mat4 b(m1);
    Mat4 c(m2);

    BOOST_REQUIRE_EQUAL(Transform::inverse3x3(b), c);
    BOOST_REQUIRE_EQUAL(Transform::inverse3x3(c), b);
}

BOOST_AUTO_TEST_CASE(test_transpose3x3, *utf::tolerance(TestUtils::TOLERANCE)) {
    double m1[4][4] = { 1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 6.0, 0.0, 7.0, 8.0, 9.0,
        0.0, 0.0, 0.0, 0.0, 1.0 };

    double m2[4][4] = { 1.0, 4.0, 7.0, 0.0, 2.0, 5.0, 8.0, 0.0, 3.0, 6.0, 9.0,
        0.0, 0.0, 0.0, 0.0, 1.0 };

    Mat4 a(m1);
    Mat4 b(m2);

    BOOST_REQUIRE_EQUAL(Transform::transpose3x3(a), b);
    BOOST_REQUIRE_EQUAL(Transform::transpose3x3(b), a);
}

BOOST_AUTO_TEST_CASE(test_trace3x3, *utf::tolerance(TestUtils::TOLERANCE)) {
    double m1[4][4] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0, 16.0 };

    Mat4 a(m1);

    BOOST_TEST(Transform::trace3x3(a) == 18.0);

    double m2[4][4] = { 1.0, 5.0, 9.0, 13.0, 2.0, 6.0, 10.0, 14.0, 3.0, 7.0,
        11.0, 15.0, 4.0, 8.0, 12.0, 16.0 };

    Mat4 b(m2);

    BOOST_TEST(Transform::trace3x3(b) == 18.0);
}

BOOST_AUTO_TEST_CASE(test_trace, *utf::tolerance(TestUtils::TOLERANCE)) {
    double m1[4][4] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0, 16.0 };

    Mat4 a(m1);

    BOOST_TEST(Transform::trace(a) == 34.0);

    double m2[4][4] = { 1.0, 5.0, 9.0, 13.0, 2.0, 6.0, 10.0, 14.0, 3.0, 7.0,
        11.0, 15.0, 4.0, 8.0, 12.0, 16.0 };

    Mat4 b(m2);

    BOOST_TEST(Transform::trace(b) == 34.0);
}

BOOST_AUTO_TEST_CASE(test_reflect, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v1(5.0, 0.0, 0.0);
    Vec n1(-1.0, 0.0, 0.0);
    Vec r1 = Transform::reflect(v1, n1);
    BOOST_REQUIRE_EQUAL(r1, Vec(-5.0, 0.0, 0.0));

    Vec v2(5.0, -5.0, 0.0);
    Vec n2(0.0, 1.0, 0.0);
    Vec r2 = Transform::reflect(v2, n2);
    BOOST_REQUIRE_EQUAL(r2, Vec(5.0, 5.0, 0.0));
}

BOOST_AUTO_TEST_CASE(test_random_double1, *utf::tolerance(0.01)) {
    int n = 10000;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double num = Utils::random_double(0.0, 1.0);
        sum += num;
        BOOST_REQUIRE_GT(num, -0.000001);
        BOOST_REQUIRE_LT(num, 1.0);
    }

    double avg = sum / n;
    BOOST_TEST(avg == 0.5);
}

BOOST_AUTO_TEST_CASE(test_random_double2, *utf::tolerance(0.1)) {
    int n = 10000;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double num = Utils::random_double(-30.0, 20.0);
        sum += num;
        BOOST_REQUIRE_GT(num, -31.000001);
        BOOST_REQUIRE_LT(num, 20.0);
    }

    double avg = sum / n;
    BOOST_TEST(avg == -5.0);
}

BOOST_AUTO_TEST_CASE(test_random_vec, *utf::tolerance(TestUtils::TOLERANCE)) {
    Vec v = Utils::random_vec(-100.0, 0.0);
    for (int i = 0; i < 3; ++i) {
        BOOST_REQUIRE_GT(v[i], -100.0);
        BOOST_REQUIRE_LT(v[i], 0.0);
    }

    BOOST_TEST(v[3] == 0.0);
}

BOOST_AUTO_TEST_CASE(
    test_random_in_unit_sphere, *utf::tolerance(TestUtils::TOLERANCE)) {
    for (int i = 0; i < 10; ++i) {
        Vec v = Utils::random_in_unit_sphere();
        BOOST_TEST(Vec::length_squared(v) < 1.0);
    }
}

BOOST_AUTO_TEST_CASE(test_clamp, *utf::tolerance(0.000001)) {
    double a = Utils::clamp(0.0, 0.0, 1.0);
    BOOST_TEST(a == 0.0);
    a = Utils::clamp(1.0, 0.0, 1.0);
    BOOST_TEST(a == 1.0);
    a = Utils::clamp(0.5, 0.0, 1.0);
    BOOST_TEST(a == 0.5);
    a = Utils::clamp(1.1, 0.0, 1.0);
    BOOST_TEST(a == 1.0);
    a = Utils::clamp(-0.1, 0.0, 1.0);
    BOOST_TEST(a == 0.0);
}

BOOST_AUTO_TEST_CASE(test_is_small) {
    double a = 0.0001;
    BOOST_REQUIRE_EQUAL(Utils::is_small(a), false);
    double b = 0.0000000001;
    BOOST_REQUIRE_EQUAL(Utils::is_small(b), true);

    Vec v(0.1, 0.1, 0.1);
    BOOST_REQUIRE_EQUAL(Utils::is_small(v), false);
    v[0] = b;
    BOOST_REQUIRE_EQUAL(Utils::is_small(v), false);
    v[1] = b;
    BOOST_REQUIRE_EQUAL(Utils::is_small(v), false);
    v[2] = b;
    BOOST_REQUIRE_EQUAL(Utils::is_small(v), true);
}
