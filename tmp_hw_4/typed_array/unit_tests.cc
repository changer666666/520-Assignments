#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }    

    TEST(TypedArray,PushAndPushFront) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);

        b.push(Point(21, 21, 21));
        EXPECT_EQ(b.get(21).x,21);

        b.push_front(Point(-1, -1, -1));
        EXPECT_EQ(b.get(0).x,-1);

        b.push_front(Point(-2, -2, -2));
        EXPECT_EQ(b.get(0).x,-2);

        b.set(0, Point(1,2,3));
        EXPECT_EQ(b.get(0).x,1);

        b.push_front(Point(-1, -1, -1));
        EXPECT_EQ(b.get(0).x,-1);
    }  

    TEST(TypedArray,PopAndPopFront) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);

        b.push(Point(21, 21, 21));
        EXPECT_EQ(b.pop().x,21);

        b.push_front(Point(-1, -1, -1));
        EXPECT_EQ(b.pop_front().x,-1);

        b.push_front(Point(-2, -2, -2));
        EXPECT_EQ(b.pop_front().x,-2);

        b.set(0, Point(1,2,3));
        EXPECT_EQ(b.pop_front().x,1);

        EXPECT_EQ(b.pop_front().x,2);
        EXPECT_EQ(b.pop_front().x,0);
        EXPECT_EQ(b.pop_front().x,0);
    }  

    TEST(TypedArray,PopAndPopFrontEmpty) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(3, Point(3,4,5));
        
        EXPECT_EQ(b.pop_front().x,1);

        EXPECT_EQ(b.pop_front().x,2);
        EXPECT_EQ(b.pop_front().x,0);
        EXPECT_EQ(b.pop_front().x,3);
        // EXPECT_EQ(b.pop().x,3);
    }  

    TEST(TypedArray,Concat) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(3, Point(3,4,5));
        TypedArray<Point> a1 = b.concat(b);
        EXPECT_EQ(a1.pop_front().x,1);
        EXPECT_EQ(a1.pop_front().x,2);
        EXPECT_EQ(a1.pop_front().x,0);
        EXPECT_EQ(a1.pop_front().x,3);
        EXPECT_EQ(a1.pop_front().x,1);
        EXPECT_EQ(a1.pop_front().x,2);
        EXPECT_EQ(a1.pop_front().x,0);
        EXPECT_EQ(a1.pop_front().x,3);

        TypedArray<Point> c;
        c.set(0, Point(1,2,3));
        c.set(1, Point(2,3,4));
        TypedArray<Point> a = b.concat(c);
        EXPECT_EQ(a.pop_front().x,1);
        EXPECT_EQ(a.pop_front().x,2);
        EXPECT_EQ(a.pop_front().x,0);
        EXPECT_EQ(a.pop_front().x,3);
        EXPECT_EQ(a.pop_front().x,1);
        EXPECT_EQ(a.pop_front().x,2);
    }  

    TEST(TypedArray,Reverse) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(3, Point(3,4,5));
        b.reverse();
        EXPECT_EQ(b.pop_front().x,3);
        EXPECT_EQ(b.pop_front().x,0);
        EXPECT_EQ(b.pop_front().x,2);
        EXPECT_EQ(b.pop_front().x,1);
    }  

    TEST(TypedArray,OperatorPlus) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(3, Point(3,4,5));
        TypedArray<Point> a1 = b + b;
        EXPECT_EQ(a1.pop_front().x,1);
        EXPECT_EQ(a1.pop_front().x,2);
        EXPECT_EQ(a1.pop_front().x,0);
        EXPECT_EQ(a1.pop_front().x,3);
        EXPECT_EQ(a1.pop_front().x,1);
        EXPECT_EQ(a1.pop_front().x,2);
        EXPECT_EQ(a1.pop_front().x,0);
        EXPECT_EQ(a1.pop_front().x,3);

        TypedArray<Point> c;
        c.set(0, Point(1,2,3));
        c.set(1, Point(2,3,4));
        TypedArray<Point> a = b + c;
        EXPECT_EQ(a.pop_front().x,1);
        EXPECT_EQ(a.pop_front().x,2);
        EXPECT_EQ(a.pop_front().x,0);
        EXPECT_EQ(a.pop_front().x,3);
        EXPECT_EQ(a.pop_front().x,1);
        EXPECT_EQ(a.pop_front().x,2);
    } 
}