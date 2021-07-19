#include <boost/test/unit_test.hpp>

#include "image.h"
#include "math/vec.h"

BOOST_AUTO_TEST_SUITE(test_image)

BOOST_AUTO_TEST_CASE(test_copy) {
    const unsigned char red[] = { 255, 0, 0 };
    const unsigned char blue[] = { 0, 0, 255 };

    Vec red_vec(1.0, 0.0, 0.0);
    Vec blue_vec(0.0, 0.0, 1.0);

    Image a(100, 200);
    BOOST_REQUIRE_EQUAL(a.width(), 100);
    BOOST_REQUIRE_EQUAL(a.height(), 200);

    for (std::size_t i = 0; i < a.width(); ++i) {
        for (std::size_t j = 0; j < a.height(); ++j) {
            a.set_pixel_color(i, j, red_vec);
        }
    }

    Image b(a);
    BOOST_REQUIRE_EQUAL(b.width(), 100);
    BOOST_REQUIRE_EQUAL(b.height(), 200);

    a.set_pixel_color(3, 3, blue_vec);
    BOOST_REQUIRE_EQUAL(a.pixel_color(3, 3)[0], blue[0]);
    BOOST_REQUIRE_EQUAL(a.pixel_color(3, 3)[1], blue[1]);
    BOOST_REQUIRE_EQUAL(a.pixel_color(3, 3)[2], blue[2]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[0], red[0]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[1], red[1]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[2], red[2]);

    b = b;
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[0], red[0]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[1], red[1]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[2], red[2]);

    Image c(400, 400);
    for (std::size_t i = 0; i < c.width(); ++i) {
        for (std::size_t j = 0; j < c.height(); ++j) {
            c.set_pixel_color(i, j, red_vec);
        }
    }

    Image d(10, 10);
    d = c;
    BOOST_REQUIRE_EQUAL(c.width(), 400);
    BOOST_REQUIRE_EQUAL(c.height(), 400);
    BOOST_REQUIRE_EQUAL(d.width(), 400);
    BOOST_REQUIRE_EQUAL(d.height(), 400);
    BOOST_REQUIRE_EQUAL(d.pixel_color(3, 3)[0], red[0]);
    BOOST_REQUIRE_EQUAL(d.pixel_color(3, 3)[1], red[1]);
    BOOST_REQUIRE_EQUAL(d.pixel_color(3, 3)[2], red[2]);
}

BOOST_AUTO_TEST_CASE(test_move) {
    const unsigned char red[] = { 255, 0, 0 };
    const unsigned char blue[] = { 0, 0, 255 };

    Vec red_vec(1.0, 0.0, 0.0);
    Vec blue_vec(0.0, 0.0, 1.0);

    Image a(100, 200);
    BOOST_REQUIRE_EQUAL(a.width(), 100);
    BOOST_REQUIRE_EQUAL(a.height(), 200);

    for (std::size_t i = 0; i < a.width(); ++i) {
        for (std::size_t j = 0; j < a.height(); ++j) {
            a.set_pixel_color(i, j, red_vec);
        }
    }

    Image b(std::move(a));
    BOOST_REQUIRE_EQUAL(b.width(), 100);
    BOOST_REQUIRE_EQUAL(b.height(), 200);

    b.set_pixel_color(3, 3, blue_vec);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[0], blue[0]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[1], blue[1]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[2], blue[2]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(0, 0)[0], red[0]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(0, 0)[1], red[1]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(0, 0)[2], red[2]);

    b = std::move(b);
    BOOST_REQUIRE_EQUAL(b.width(), 100);
    BOOST_REQUIRE_EQUAL(b.height(), 200);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[0], blue[0]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[1], blue[1]);
    BOOST_REQUIRE_EQUAL(b.pixel_color(3, 3)[2], blue[2]);

    Image c(400, 400);
    for (std::size_t i = 0; i < c.width(); ++i) {
        for (std::size_t j = 0; j < c.height(); ++j) {
            c.set_pixel_color(i, j, red_vec);
        }
    }

    Image d(10, 10);
    d = std::move(c);
    BOOST_REQUIRE_EQUAL(c.width(), 0);
    BOOST_REQUIRE_EQUAL(c.height(), 0);
    BOOST_REQUIRE_EQUAL(d.width(), 400);
    BOOST_REQUIRE_EQUAL(d.height(), 400);
    BOOST_REQUIRE_EQUAL(d.pixel_color(3, 3)[0], red[0]);
    BOOST_REQUIRE_EQUAL(d.pixel_color(3, 3)[1], red[1]);
    BOOST_REQUIRE_EQUAL(d.pixel_color(3, 3)[2], red[2]);
}

BOOST_AUTO_TEST_SUITE_END()
