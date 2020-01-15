#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, AddAndMultiply) {
        Complex a = (Complex) { 2, 3 },
                b = (Complex) { 4, 5 },
                c = (Complex) { 0, 3 },
                d = (Complex) { 5, -6 },
                e = (Complex) { -9, 7 },
                f = (Complex) { -3, -2 };
        EXPECT_EQ(add(a,b).real, 6);
        EXPECT_EQ(add(a,b).im, 8);
        EXPECT_EQ(multiply(a,b).real, -7);
        EXPECT_EQ(multiply(a,b).im, 22);

        EXPECT_EQ(add(c,d).real, 5);
        EXPECT_EQ(add(c,d).im, -3);
        EXPECT_EQ(multiply(c,d).real, 18);
        EXPECT_EQ(multiply(c,d).im, 15);

        EXPECT_EQ(add(e,f).real, -12);
        EXPECT_EQ(add(e,f).im, 5);
        EXPECT_EQ(multiply(e,f).real, 41);
        EXPECT_EQ(multiply(e,f).im, -3);

        EXPECT_EQ(negate(a).real, -2);
        EXPECT_EQ(negate(a).im, -3);
        EXPECT_EQ(negate(b).real, -4);
        EXPECT_EQ(negate(b).im, -5);
        EXPECT_EQ(negate(c).real, 0);
        EXPECT_EQ(negate(c).im, -3);
        EXPECT_EQ(negate(d).real, -5);
        EXPECT_EQ(negate(d).im, 6);
        EXPECT_EQ(negate(e).real, 9);
        EXPECT_EQ(negate(e).im, -7);
        EXPECT_EQ(negate(f).real, 3);
        EXPECT_EQ(negate(f).im, 2);

        EXPECT_EQ(magnitude(a), sqrt(2 * 2 + 3 * 3));
        EXPECT_EQ(magnitude(b), sqrt(4 * 4 + 5 * 5));
        EXPECT_EQ(magnitude(c), sqrt(0 * 0 + 3 * 3));
        EXPECT_EQ(magnitude(d), sqrt(5 * 5 + (-6) * (-6)));
        EXPECT_EQ(magnitude(e), sqrt((-9) * (-9) + 7 * 7));
        EXPECT_EQ(magnitude(f), sqrt((-3) * (-3) + (-2) * (-2)));
    }

}
