#include "fraction.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, Basics) {
        Fraction a = (Fraction) { 2, 3 },
                 b = (Fraction) { 4, 5 };
        EXPECT_EQ(add(a,b).num,22);
        EXPECT_EQ(add(a,b).den,15);
        EXPECT_EQ(multiply(a,b).num,8);
        EXPECT_EQ(multiply(a,b).den,15);
    }

    
    TEST(Fractions, Second) {
        Fraction a = (Fraction) { 1, 2 },
                 b = (Fraction) { 1, 2 };
        EXPECT_EQ(add(a,b).num,4);
        EXPECT_EQ(add(a,b).den,4);
        EXPECT_EQ(multiply(a,b).num,1);
        EXPECT_EQ(multiply(a,b).den,4);
    }

    TEST(Fractions, Third) {
        Fraction a = (Fraction) { -1, 2 },
                 b = (Fraction) { -1, 2 };
        EXPECT_EQ(add(a,b).num,-4);
        EXPECT_EQ(add(a,b).den,4);
        EXPECT_EQ(multiply(a,b).num,1);
        EXPECT_EQ(multiply(a,b).den,4);
    }

    TEST(Fractions, Forth) {
        Fraction a = (Fraction) { 2, 4 },
                 b = (Fraction) { -2, 4 },
                 c = (Fraction) { -1, 0 },
                 d = (Fraction) { 0, 2 },
                 e = (Fraction) { 0, 0 },
                 f = (Fraction) { -0, 0 },
                 g = (Fraction) { 24, 36 },
                 h = (Fraction) { 12, 0 },
                 i = (Fraction) { -36, 12 },
                 j = (Fraction) { 36, -12 };
        EXPECT_EQ(reduce(a).num,1);
        EXPECT_EQ(reduce(a).den,2);
        EXPECT_EQ(reduce(b).num,-1);
        EXPECT_EQ(reduce(b).den,2);
        EXPECT_EQ(reduce(c).num,1);
        EXPECT_EQ(reduce(c).den,0);
        EXPECT_EQ(reduce(d).num,0);
        EXPECT_EQ(reduce(d).den,1);
        EXPECT_EQ(reduce(e).num,0);
        EXPECT_EQ(reduce(e).den,0);
        EXPECT_EQ(reduce(f).num,0);
        EXPECT_EQ(reduce(f).den,0);
        EXPECT_EQ(reduce(g).num,2);
        EXPECT_EQ(reduce(g).den,3);
        EXPECT_EQ(reduce(h).num,1);
        EXPECT_EQ(reduce(h).den,0);
        EXPECT_EQ(reduce(i).num,-3);
        EXPECT_EQ(reduce(i).den,1);
        EXPECT_EQ(reduce(j).num,-3);
        EXPECT_EQ(reduce(j).den,1);
    }

}
