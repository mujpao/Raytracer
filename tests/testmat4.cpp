#define BOOST_TEST_MODULE TestMat3
#include <boost/test/unit_test.hpp>

#include "mat4.h"
#include "mat3.h"
#include "vec.h"
#include "geometry.h"

BOOST_AUTO_TEST_CASE(test_constructors)
{
    double m[4][4] = {
		1.0, 2.0, 3.0, 0.0,
		4.0, 5.0, 6.0, 0.0,
		7.0, 8.0, 9.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	Mat4 m1(m);

    BOOST_REQUIRE_EQUAL(m1(0, 0), 1.0);
    BOOST_REQUIRE_EQUAL(m1(0, 1), 2.0);
    BOOST_REQUIRE_EQUAL(m1(0, 2), 3.0);
    BOOST_REQUIRE_EQUAL(m1(0, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m1(1, 0), 4.0);
    BOOST_REQUIRE_EQUAL(m1(1, 1), 5.0);
    BOOST_REQUIRE_EQUAL(m1(1, 2), 6.0);
    BOOST_REQUIRE_EQUAL(m1(1, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m1(2, 0), 7.0);
    BOOST_REQUIRE_EQUAL(m1(2, 1), 8.0);
    BOOST_REQUIRE_EQUAL(m1(2, 2), 9.0);
    BOOST_REQUIRE_EQUAL(m1(2, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m1(3, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m1(3, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m1(3, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m1(3, 3), 1.0);

    Mat4 m2;

    BOOST_REQUIRE_EQUAL(m2(0, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m2(0, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m2(0, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m2(0, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m2(1, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m2(1, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m2(1, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m2(1, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m2(2, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m2(2, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m2(2, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m2(2, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m2(3, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m2(3, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m2(3, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m2(3, 3), 0.0);

    Mat4 m3(1.0);
    BOOST_REQUIRE_EQUAL(m3(0, 0), 1.0);
    BOOST_REQUIRE_EQUAL(m3(0, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m3(0, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m3(0, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m3(1, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m3(1, 1), 1.0);
    BOOST_REQUIRE_EQUAL(m3(1, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m3(1, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m3(2, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m3(2, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m3(2, 2), 1.0);
    BOOST_REQUIRE_EQUAL(m3(2, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m3(3, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m3(3, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m3(3, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m3(3, 3), 1.0);
	
    double m3x3[3][3] = {
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	};
	Mat3 m4(m3x3);
	Mat4 m5(m4);

	BOOST_REQUIRE_EQUAL(m5(0, 0), 1.0);
    BOOST_REQUIRE_EQUAL(m5(0, 1), 2.0);
    BOOST_REQUIRE_EQUAL(m5(0, 2), 3.0);
    BOOST_REQUIRE_EQUAL(m5(0, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m5(1, 0), 4.0);
    BOOST_REQUIRE_EQUAL(m5(1, 1), 5.0);
    BOOST_REQUIRE_EQUAL(m5(1, 2), 6.0);
    BOOST_REQUIRE_EQUAL(m5(1, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m5(2, 0), 7.0);
    BOOST_REQUIRE_EQUAL(m5(2, 1), 8.0);
    BOOST_REQUIRE_EQUAL(m5(2, 2), 9.0);
    BOOST_REQUIRE_EQUAL(m5(2, 3), 0.0);
    BOOST_REQUIRE_EQUAL(m5(3, 0), 0.0);
    BOOST_REQUIRE_EQUAL(m5(3, 1), 0.0);
    BOOST_REQUIRE_EQUAL(m5(3, 2), 0.0);
    BOOST_REQUIRE_EQUAL(m5(3, 3), 1.0);
}

BOOST_AUTO_TEST_CASE(test_subscript)
{
    Mat4 m;

    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(0, 2) = 3.0;
    m(0, 3) = 4.0;
    m(1, 0) = 5.0;
    m(1, 1) = 6.0;
    m(1, 2) = 7.0;
    m(1, 3) = 8.0;
    m(2, 0) = 9.0;
    m(2, 1) = 10.0;
    m(2, 2) = 11.0;
    m(2, 3) = 12.0;
    m(3, 0) = 13.0;
    m(3, 1) = 14.0;
    m(3, 2) = 15.0;
    m(3, 3) = 16.0;

    BOOST_REQUIRE_EQUAL(m(0, 0), 1.0);
    BOOST_REQUIRE_EQUAL(m(0, 1), 2.0);
    BOOST_REQUIRE_EQUAL(m(0, 2), 3.0);
    BOOST_REQUIRE_EQUAL(m(0, 3), 4.0);
    BOOST_REQUIRE_EQUAL(m(1, 0), 5.0);
    BOOST_REQUIRE_EQUAL(m(1, 1), 6.0);
    BOOST_REQUIRE_EQUAL(m(1, 2), 7.0);
    BOOST_REQUIRE_EQUAL(m(1, 3), 8.0);
    BOOST_REQUIRE_EQUAL(m(2, 0), 9.0);
    BOOST_REQUIRE_EQUAL(m(2, 1), 10.0);
    BOOST_REQUIRE_EQUAL(m(2, 2), 11.0);
    BOOST_REQUIRE_EQUAL(m(2, 3), 12.0);
    BOOST_REQUIRE_EQUAL(m(3, 0), 13.0);
    BOOST_REQUIRE_EQUAL(m(3, 1), 14.0);
    BOOST_REQUIRE_EQUAL(m(3, 2), 15.0);
    BOOST_REQUIRE_EQUAL(m(3, 3), 16.0);

    m(1, 1) -= 5.0;

    BOOST_REQUIRE_EQUAL(m(0, 0), 1.0);
    BOOST_REQUIRE_EQUAL(m(0, 1), 2.0);
    BOOST_REQUIRE_EQUAL(m(0, 2), 3.0);
    BOOST_REQUIRE_EQUAL(m(0, 3), 4.0);
    BOOST_REQUIRE_EQUAL(m(1, 0), 5.0);
    BOOST_REQUIRE_EQUAL(m(1, 1), 1.0);
    BOOST_REQUIRE_EQUAL(m(1, 2), 7.0);
    BOOST_REQUIRE_EQUAL(m(1, 3), 8.0);
    BOOST_REQUIRE_EQUAL(m(2, 0), 9.0);
    BOOST_REQUIRE_EQUAL(m(2, 1), 10.0);
    BOOST_REQUIRE_EQUAL(m(2, 2), 11.0);
    BOOST_REQUIRE_EQUAL(m(2, 3), 12.0);
    BOOST_REQUIRE_EQUAL(m(3, 0), 13.0);
    BOOST_REQUIRE_EQUAL(m(3, 1), 14.0);
    BOOST_REQUIRE_EQUAL(m(3, 2), 15.0);
    BOOST_REQUIRE_EQUAL(m(3, 3), 16.0);
}

BOOST_AUTO_TEST_CASE(test_add)
{
    Mat4 a(0.0);
    BOOST_REQUIRE_EQUAL(a + a, a);

    double m1[4][4] = {
        1.549060363917804,   2.538813161848725,   2.278232552563897,   3.735740347499977,
        1.727479501334896,   3.306642070516340,   0.894699971212984,   2.996917225812247,
        2.264812438164677,   2.718698945834891,   1.690623744977105,   0.814805001917729,
        3.050432605511240,   2.002444840667468,   1.716453437480027,   0.117380802949563
	};

    double m2[4][4] = {
        2.986890565512533,   0.585978276789577,   0.510648416818384,   2.822939706408993,
        1.491948460463876,   1.573498809806530,   3.567136532203893,   1.644331154755391,
        0.973939536722858,   1.155576247612460,   2.955851251011776,   1.680306471841210,
        2.648286483362376,   0.437318201220109,   2.040371851860524,   0.390112248408781,
	};

    double m3[4][4] = {
        4.535950929430337,   3.124791438638303,   2.788880969382281,   6.558680053908970,
        3.219427961798772,   4.880140880322870,   4.461836503416878,   4.641248380567637,
        3.238751974887535,   3.874275193447351,   4.646474995988881,   2.495111473758938,
        5.698719088873617,   2.439763041887577,   3.756825289340551,   0.507493051358344,
	};

    Mat4 b(m1);
    Mat4 c(m2);
    Mat4 d(m3);

    BOOST_REQUIRE_EQUAL(b + c, d);
    BOOST_REQUIRE_EQUAL(c + b, d);
}

BOOST_AUTO_TEST_CASE(test_subtract)
{
    Mat4 a(0.0);
    BOOST_REQUIRE_EQUAL(a - a, a);

    double m1[4][4] = {
        2.079686340066428,   1.943167500507085,   1.221779377183820,   3.634637100452963,
        3.975188581709318,   2.879717024085005,   2.114681602397119,   1.777173045163217,
        2.332034921337405,   2.189147589244121,   3.112830446987914,   2.452284910775307,
        2.269050744445833,   1.618158742494081,   3.740685691179940,   3.211700642623626
	};

    double m2[4][4] = {
        -2.126803889740476,  -2.319644065516047,  -3.998266481325794,  -0.155509657676701,
        -3.065686687167915,  -0.405921694785352,  -1.816466413275886,  -0.738421163844512,
        -2.951577179687741,  -2.515894888356526,  -2.541587783772891,  -0.349495795105237,
        -2.436119712422753,  -1.567696863169631,  -2.126752193431009,  -3.526148961850058
	};

    double m3[4][4] = {
        4.206490229806905,   4.262811566023132,   5.220045858509614,   3.790146758129665,
        7.040875268877233,   3.285638718870357,   3.931148015673005,   2.515594209007729,
        5.283612101025145,   4.705042477600648,   5.654418230760806,   2.801780705880544,
        4.705170456868586,   3.185855605663712,   5.867437884610949,   6.737849604473684,
	};

    Mat4 b(m1);
    Mat4 c(m2);
    Mat4 d(m3);

    BOOST_REQUIRE_EQUAL(b - c, d);
    BOOST_REQUIRE_EQUAL(d + c, b);
}

BOOST_AUTO_TEST_CASE(test_multiply)
{
    Mat4 a(1.0);
    BOOST_REQUIRE_EQUAL(a * a, a);

    double m1[4][4] = {
        1.549060363917804,   2.538813161848725,   2.278232552563897,   3.735740347499977,
        1.727479501334896,   3.306642070516340,   0.894699971212984,   2.996917225812247,
        2.264812438164677,   2.718698945834891,   1.690623744977105,   0.814805001917729,
        3.050432605511240,   2.002444840667468,   1.716453437480027,   0.117380802949563
	};

    double m2[4][4] = {
        2.986890565512533,   0.585978276789577,   0.510648416818384,   2.822939706408993,
        1.491948460463876,   1.573498809806530,   3.567136532203893,   1.644331154755391,
        0.973939536722858,   1.155576247612460,   2.955851251011776,   1.680306471841210,
        2.648286483362376,   0.437318201220109,   2.040371851860524,   0.390112248408781,
	};

    double m3[4][4] = {
    20.5268235990478   ,   9.168913884456135    ,  24.20373439195176  ,  13.83304055592589  ,
    18.90121082740901  ,    8.559763309666248   ,   21.43680398019737 ,   12.98628931974272 ,
    14.62530799102308  ,    7.914974146389783   ,   17.51423071794012 ,   14.02250176774728 ,
    14.0814327268942   ,   6.973157399222057    ,   14.0137742522495  ,  14.83382926958149
	};

    double m4[4][4] = {
        15.40684945753874 ,      16.5618578662765 ,     13.03786496634441 ,    13.66181380447613,
        18.1241217199192  ,    21.98142851757985  ,    13.65991847506854  ,     13.388711348273 ,
       15.32503574078194  ,    17.69451825617066  ,    11.13415492345686  ,   9.707229692685518 ,
       10.66888452277457  ,    14.49789440453516  ,     10.5437916680763  ,    12.9122139976602
	};

    Mat4 b(m1);
    Mat4 c(m2);
    Mat4 d(m3);
    Mat4 e(m4);

    BOOST_REQUIRE_EQUAL(b * c, d);
    BOOST_REQUIRE_EQUAL(c * b, e);
}

BOOST_AUTO_TEST_CASE(test_multiply_scalar1)
{
    double m1[4][4] = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    };

    double m2[4][4] = {
        2.0, 4.0, 6.0, 8.0,
        10.0, 12.0, 14.0, 16.0,
        18.0, 20.0, 22.0, 24.0,
        26.0, 28.0, 30.0, 32.0
    };

    Mat4 a(m1);
    Mat4 b(m2);

    BOOST_REQUIRE_EQUAL(2 * a, b);
    BOOST_REQUIRE_EQUAL(a * 2, b);
}

BOOST_AUTO_TEST_CASE(test_multiply_vec)
{
    Mat4 a(1.0);
    Vec v1(1.0, 1.0, 1.0, 1.0);

    BOOST_REQUIRE_EQUAL(a * v1, Vec(1.0, 1.0, 1.0, 1.0));

    double m[4][4] = {
        3.192319633374724  ,     1.213299043330458  ,   2.415729792971034  ,     2.446539892841227,
       3.704417871915366   ,   0.1107875860055909   ,  3.162665235584538   ,   0.6072266179468984 ,
      0.8313465431812825   ,   0.9484557378620839   ,  3.338720093710996   ,   0.6014045673822497 ,
        2.86779119965947   ,    3.105505162436734   ,  1.815317900014179   ,    2.022856212538157
    };

    Mat4 b(m);
    Vec v2( 1.20271949785608,
       3.748175301178714,
       1.836690181724781,
      0.4919080538506044);

    Vec v3(14.02754244340887,
       10.97816274646346,
       10.98288523383937,
       19.41836196553342);

    BOOST_REQUIRE_EQUAL(b * v2, v3);

}

BOOST_AUTO_TEST_CASE(test_multiply_ray)
{
   double m[4][4] = {
        3.192319633374724  ,     1.213299043330458  ,   2.415729792971034  ,   0.0,
       3.704417871915366   ,   0.1107875860055909   ,  3.162665235584538   ,   0.0,
      0.8313465431812825   ,   0.9484557378620839   ,  3.338720093710996   ,   0.0,
        0.0, 0.0, 0.0,   1.0
    };

    Mat4 a(m);

    Ray r1(Vec(2.604643814707491,
       2.156353647053825,
       1.117052181454884, 1.0), Vec( 1.818817138444932,
       3.308363437999502,
       1.289032684779756,
       0.0));
    
    Ray r2 = a * r1;
    BOOST_REQUIRE_EQUAL(r2.origin(), a * r1.origin());
    BOOST_REQUIRE_EQUAL(r2.direction(), Vec::normalize(a * r1.direction()));
}

BOOST_AUTO_TEST_CASE(test_assign)
{
    double m[4][4] = {
       4.973133150644529   ,   4.859009894635833   ,   2.246052782351735    ,   2.670584463032503,
       3.545990595883572   ,  0.3188863720572094   ,   4.027399063862153    ,   1.606859385297397,
       2.393700778536176   , 0.08293501425706729   ,  0.8708683568723558    ,    4.38156171602564,
       1.040013065628002   ,   4.891338377354534   ,   1.523080576991909    ,   3.965852860907286
    };

    Mat4 a(m);
    Mat4 b = a;

    BOOST_REQUIRE_EQUAL(b, a);
}
