#define BOOST_TEST_MODULE TestMat3
#include <boost/test/unit_test.hpp>

#include "mat3.h"
#include "testutils.h"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(test_constructors, * utf::tolerance(TestUtils::TOLERANCE))
{
    double m[3][3] = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	};

	Mat3 m1(m);

    BOOST_TEST(m1(0, 0) == 1.0);
    BOOST_TEST(m1(0, 1) == 2.0);
    BOOST_TEST(m1(0, 2) == 3.0);
    BOOST_TEST(m1(1, 0) == 4.0);
    BOOST_TEST(m1(1, 1) == 5.0);
    BOOST_TEST(m1(1, 2) == 6.0);
    BOOST_TEST(m1(2, 0) == 7.0);
    BOOST_TEST(m1(2, 1) == 8.0);
    BOOST_TEST(m1(2, 2) == 9.0);

	Mat3 m2;
    BOOST_TEST(m2(0, 0) == 0.0);
    BOOST_TEST(m2(0, 1) == 0.0);
    BOOST_TEST(m2(0, 2) == 0.0);
    BOOST_TEST(m2(1, 0) == 0.0);
    BOOST_TEST(m2(1, 1) == 0.0);
    BOOST_TEST(m2(1, 2) == 0.0);
    BOOST_TEST(m2(2, 0) == 0.0);
    BOOST_TEST(m2(2, 1) == 0.0);
    BOOST_TEST(m2(2, 2) == 0.0);

	Mat3 m3(1.0f);
    BOOST_TEST(m3(0, 0) == 1.0);
    BOOST_TEST(m3(0, 1) == 0.0);
    BOOST_TEST(m3(0, 2) == 0.0);
    BOOST_TEST(m3(1, 0) == 0.0);
    BOOST_TEST(m3(1, 1) == 1.0);
    BOOST_TEST(m3(1, 2) == 0.0);
    BOOST_TEST(m3(2, 0) == 0.0);
    BOOST_TEST(m3(2, 1) == 0.0);
    BOOST_TEST(m3(2, 2) == 1.0);
}

BOOST_AUTO_TEST_CASE(test_subscript, * utf::tolerance(TestUtils::TOLERANCE))
{
    Mat3 m;

    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(0, 2) = 3.0;
    m(1, 0) = 4.0;
    m(1, 1) = 5.0;
    m(1, 2) = 6.0;
    m(2, 0) = 7.0;
    m(2, 1) = 8.0;
    m(2, 2) = 9.0;

    BOOST_TEST(m(0, 0) == 1.0);
    BOOST_TEST(m(0, 1) == 2.0);
    BOOST_TEST(m(0, 2) == 3.0);
    BOOST_TEST(m(1, 0) == 4.0);
    BOOST_TEST(m(1, 1) == 5.0);
    BOOST_TEST(m(1, 2) == 6.0);
    BOOST_TEST(m(2, 0) == 7.0);
    BOOST_TEST(m(2, 1) == 8.0);
    BOOST_TEST(m(2, 2) == 9.0);

    m(1, 1) -= 5.0;
    
    BOOST_TEST(m(0, 0) == 1.0);
    BOOST_TEST(m(0, 1) == 2.0);
    BOOST_TEST(m(0, 2) == 3.0);
    BOOST_TEST(m(1, 0) == 4.0);
    BOOST_TEST(m(1, 1) == 0.0);
    BOOST_TEST(m(1, 2) == 6.0);
    BOOST_TEST(m(2, 0) == 7.0);
    BOOST_TEST(m(2, 1) == 8.0);
    BOOST_TEST(m(2, 2) == 9.0);
}

BOOST_AUTO_TEST_CASE(test_add, * utf::tolerance(TestUtils::TOLERANCE))
{
    double m[3][3] = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	};

	Mat3 m1(m);

    Mat3 m2(1.0f);

    Mat3 m3 = m1 + m2;

	BOOST_TEST(m3(0, 0) == 2.0);
    BOOST_TEST(m3(0, 1) == 2.0);
    BOOST_TEST(m3(0, 2) == 3.0);
    BOOST_TEST(m3(1, 0) == 4.0);
    BOOST_TEST(m3(1, 1) == 6.0);
    BOOST_TEST(m3(1, 2) == 6.0);
    BOOST_TEST(m3(2, 0) == 7.0);
    BOOST_TEST(m3(2, 1) == 8.0);
    BOOST_TEST(m3(2, 2) == 10.0);
}

BOOST_AUTO_TEST_CASE(test_subtract, * utf::tolerance(TestUtils::TOLERANCE))
{
    double m[3][3] = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	};

	Mat3 m1(m);

    Mat3 m2(1.0f);

    Mat3 m3 = m1 - m2;

	BOOST_TEST(m3(0, 0) == 0.0);
    BOOST_TEST(m3(0, 1) == 2.0);
    BOOST_TEST(m3(0, 2) == 3.0);
    BOOST_TEST(m3(1, 0) == 4.0);
    BOOST_TEST(m3(1, 1) == 4.0);
    BOOST_TEST(m3(1, 2) == 6.0);
    BOOST_TEST(m3(2, 0) == 7.0);
    BOOST_TEST(m3(2, 1) == 8.0);
    BOOST_TEST(m3(2, 2) == 8.0);
}

BOOST_AUTO_TEST_CASE(test_multiply_scalar1, * utf::tolerance(TestUtils::TOLERANCE))
{
    double m[3][3] = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	};

	Mat3 m1(m);

    Mat3 m2 = m1 * 3.0;

	BOOST_TEST(m2(0, 0) == 3.0);
    BOOST_TEST(m2(0, 1) == 6.0);
    BOOST_TEST(m2(0, 2) == 9.0);
    BOOST_TEST(m2(1, 0) == 12.0);
    BOOST_TEST(m2(1, 1) == 15.0);
    BOOST_TEST(m2(1, 2) == 18.0);
    BOOST_TEST(m2(2, 0) == 21.0);
    BOOST_TEST(m2(2, 1) == 24.0);
    BOOST_TEST(m2(2, 2) == 27.0);
}

BOOST_AUTO_TEST_CASE(test_multiply_scalar2, * utf::tolerance(TestUtils::TOLERANCE))
{
    double m[3][3] = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	};

	Mat3 m1(m);

    Mat3 m2 = 3.0 * m1;

	BOOST_TEST(m2(0, 0) == 3.0);
    BOOST_TEST(m2(0, 1) == 6.0);
    BOOST_TEST(m2(0, 2) == 9.0);
    BOOST_TEST(m2(1, 0) == 12.0);
    BOOST_TEST(m2(1, 1) == 15.0);
    BOOST_TEST(m2(1, 2) == 18.0);
    BOOST_TEST(m2(2, 0) == 21.0);
    BOOST_TEST(m2(2, 1) == 24.0);
    BOOST_TEST(m2(2, 2) == 27.0);
}

BOOST_AUTO_TEST_CASE(test_assign, * utf::tolerance(TestUtils::TOLERANCE))
{
    double m[3][3] = {
        0.825466920404930,   0.675540312110681,   0.393762932838329,
        0.155379413297363,   0.213957715996724,   0.431626169136190,
        0.828444487793538,   0.129952582616658,   0.649443580557875
    };

    Mat3 a(m);
    Mat3 b = a;

    BOOST_REQUIRE_EQUAL(b, a);

    // TODO test not equal
}
