#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(Examples,GetMethod) {
        Complex x(1,2);
        Complex y(3);
        EXPECT_DOUBLE_EQ(x.getRe(), 1);
        EXPECT_DOUBLE_EQ(x.getIm(), 2);

        EXPECT_DOUBLE_EQ(y.getRe(), 3);
        EXPECT_DOUBLE_EQ(y.getIm(), 0);
    }

    TEST(Examples,Conjugate) {
        Complex x(1,2);
        Complex y(3);

        Complex a = x.conjugate();
        EXPECT_DOUBLE_EQ(a.getRe(), 1);
        EXPECT_DOUBLE_EQ(a.getIm(), -2);

        Complex b = y.conjugate();
        EXPECT_DOUBLE_EQ(b.getRe(), 3);
        EXPECT_DOUBLE_EQ(b.getIm(), 0);
    }

    TEST(Examples,Times) {
        Complex x(3,2);
        Complex y(7,-9);

        Complex a = x * y;
        EXPECT_DOUBLE_EQ(a.getRe(), 39);
        EXPECT_DOUBLE_EQ(a.getIm(), -13);
    }

    TEST(Examples,Plus) {
        Complex x(3,2);
        Complex y(7,-9);

        Complex a = x + y;
        EXPECT_DOUBLE_EQ(a.getRe(), 10);
        EXPECT_DOUBLE_EQ(a.getIm(), -7);
    }

    TEST(Examples,Equal) {
        Complex x(3,2);
        Complex y(7,-9);
        Complex z(3,2);
        ASSERT_EQ(x==y, false);
        ASSERT_EQ(x==z, true);
        ASSERT_EQ(x, z);
    }
}