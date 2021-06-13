#define BOOST_TEST_MODULE TestRay
#include <boost/test/unit_test.hpp>

#include "ray.h"

BOOST_AUTO_TEST_CASE(test_constructors)
{
    // TODO comparing floating points?
    Vec v1(1.0, 2.0, 3.0);
	BOOST_REQUIRE_EQUAL(v1.x(), 1.0);
	BOOST_REQUIRE_EQUAL(v1.y(), 2.0);
	BOOST_REQUIRE_EQUAL(v1.z(), 3.0);
    BOOST_REQUIRE_EQUAL(v1.w(), 1.0);

	BOOST_REQUIRE_EQUAL(v1[0], 1.0);
	BOOST_REQUIRE_EQUAL(v1[1], 2.0);
	BOOST_REQUIRE_EQUAL(v1[2], 3.0);
    BOOST_REQUIRE_EQUAL(v1[3], 1.0);

    Vec v2;
	BOOST_REQUIRE_EQUAL(v2.x(), 0.0);
	BOOST_REQUIRE_EQUAL(v2.y(), 0.0);
	BOOST_REQUIRE_EQUAL(v2.z(), 0.0);
    BOOST_REQUIRE_EQUAL(v2.w(), 1.0);

	BOOST_REQUIRE_EQUAL(v2[0], 0.0);
	BOOST_REQUIRE_EQUAL(v2[1], 0.0);
	BOOST_REQUIRE_EQUAL(v2[2], 0.0);
    BOOST_REQUIRE_EQUAL(v2[3], 1.0);

    Vec v3(1.0, 2.0, 3.0, 4.3);
	BOOST_REQUIRE_EQUAL(v3.x(), 1.0);
	BOOST_REQUIRE_EQUAL(v3.y(), 2.0);
	BOOST_REQUIRE_EQUAL(v3.z(), 3.0);
    BOOST_REQUIRE_EQUAL(v3.w(), 4.3);

	BOOST_REQUIRE_EQUAL(v3[0], 1.0);
	BOOST_REQUIRE_EQUAL(v3[1], 2.0);
	BOOST_REQUIRE_EQUAL(v3[2], 3.0);
    BOOST_REQUIRE_EQUAL(v3[3], 4.3);
}

BOOST_AUTO_TEST_CASE(test_subscript)
{
    Vec v(1.0, 2.0, 3.0);
    v[0] = 5.0;
	v[1] = 10.0;
	v[2] = 20.0;
    v[3] = 5.0;

    BOOST_REQUIRE_EQUAL(v.x(), 5.0);
	BOOST_REQUIRE_EQUAL(v.y(), 10.0);
	BOOST_REQUIRE_EQUAL(v.z(), 20.0);
    BOOST_REQUIRE_EQUAL(v.w(), 5.0);

	BOOST_REQUIRE_EQUAL(v[0], 5.0);
	BOOST_REQUIRE_EQUAL(v[1], 10.0);
	BOOST_REQUIRE_EQUAL(v[2], 20.0);
    BOOST_REQUIRE_EQUAL(v[3], 5.0);
}

BOOST_AUTO_TEST_CASE(test_add)
{
    Vec v1(3.0, 4.0, 5.0);
	Vec v2(6.0, 7.0, 8.0);

	BOOST_REQUIRE_EQUAL(v1 + v2, Vec(9.0, 11.0, 13.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_subtract)
{
    Vec v1(3.0, 4.0, 5.0);
	Vec v2(6.0, 7.0, 8.0);

	BOOST_REQUIRE_EQUAL(v1 - v2, Vec(-3.0, -3.0, -3.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_multiply_scalar1)
{
    Vec v(1.0, 2.0, 3.0);

	BOOST_REQUIRE_EQUAL(v * 3.0, Vec(3.0, 6.0, 9.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_multiply_scalar2)
{
    Vec v(1.0, 2.0, 3.0);

	BOOST_REQUIRE_EQUAL(3.0 * v, Vec(3.0, 6.0, 9.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_multiply_vec)
{
    Vec v1(1.0, 2.0, 3.0);
	Vec v2(10.0, 4.0, 12.0);
    Vec v3 = v1 * v2;

	BOOST_REQUIRE_EQUAL(v1 * v2, Vec(10.0, 8.0, 36.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_divide_scalar)
{
    Vec v(10.0, 20.0, 30.0);
	v = v / 2.0;

	BOOST_REQUIRE_EQUAL(v / 2.0, Vec(5.0, 10.0, 15.0, 1.0));
}

BOOST_AUTO_TEST_CASE(test_normalize)
{
    Vec v1(1.0, 0.0, 0.0);
	v1 = Vec::normalize(v1);

	BOOST_REQUIRE_EQUAL(Vec::normalize(v1), Vec(1.0, 0.0, 0.0, 1.0));

	Vec v2(1.0, -1.0, 1.0);
	v2 = Vec::normalize(v2);

	BOOST_REQUIRE_EQUAL(Vec::normalize(v2), Vec(1.0 / sqrt(3.0), -1.0 / sqrt(3.0), 1.0 / sqrt(3.0), 1.0));
}

BOOST_AUTO_TEST_CASE(test_point)
{
    Point p1(1.0f, 2.0f, 3.0f);
    BOOST_REQUIRE_EQUAL(p1.x(), 1.0);
	BOOST_REQUIRE_EQUAL(p1.y(), 2.0);
	BOOST_REQUIRE_EQUAL(p1.z(), 3.0);

	BOOST_REQUIRE_EQUAL(p1[0], 1.0);
	BOOST_REQUIRE_EQUAL(p1[1], 2.0);
	BOOST_REQUIRE_EQUAL(p1[2], 3.0);

	BOOST_REQUIRE_EQUAL(p1, Point(1.0, 2.0, 3.0));

    Point p2();
    BOOST_REQUIRE_EQUAL(p2.x(), 0.0);
	BOOST_REQUIRE_EQUAL(p2.y(), 0.0);
	BOOST_REQUIRE_EQUAL(p2.z(), 0.0);

	BOOST_REQUIRE_EQUAL(p2[0], 0.0);
	BOOST_REQUIRE_EQUAL(p2[1], 0.0);
	BOOST_REQUIRE_EQUAL(p2[2], 0.0);

	BOOST_REQUIRE_EQUAL(p2, Point);
}

BOOST_AUTO_TEST_CASE(test_add_point1)
{
    Vec v1(3.0, 4.0, 5.0);
	point p(6.0, 7.0, 8.0);

	BOOST_REQUIRE_EQUAL(v1 + p, Vec(9.0, 11.0, 13.0, 1.0));

	BOOST_REQUIRE_EQUAL(v1, Vec(3.0, 4.0, 5.0, 1.0));
	BOOST_REQUIRE_EQUAL(p, Point(6.0, 7.0, 8.0));
}

BOOST_AUTO_TEST_CASE(test_add_point2)
{

	Vec v1(3.0, 4.0, 5.0);
	point p(6.0, 7.0, 8.0);

	BOOST_REQUIRE_EQUAL(p + v1, Vec(9.0, 11.0, 13.0, 1.0));

	BOOST_REQUIRE_EQUAL(v1, Vec(3.0, 4.0, 5.0, 1.0));
	BOOST_REQUIRE_EQUAL(p, Point(6.0, 7.0, 8.0));
}

BOOST_AUTO_TEST_CASE(test_assign)
{
    Vec v1(3.0, 4.0, 5.0);
	Vec v2 = v1;

	BOOST_REQUIRE_EQUAL(v2, v1);
}
