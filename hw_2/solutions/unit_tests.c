#include "gtest/gtest.h"
#include "solutions.h"

namespace {
    TEST(HW2,RunningTotal) {
        ASSERT_EQ(running_total(1),  1);
        ASSERT_EQ(running_total(1),  2);
        ASSERT_EQ(running_total(5),  7);
        ASSERT_EQ(running_total(-3), 4);      
    }  

    TEST(HW2,ReverseInPlace) {
        int x[] = {10,20,30,40,50};
        reverse_in_place(x,5);
        ASSERT_EQ(x[0],50);
        ASSERT_EQ(x[1],40);       
        ASSERT_EQ(x[2],30);   
        ASSERT_EQ(x[3],20);   
        ASSERT_EQ(x[4],10);                            
    }   
    TEST(HW2,ReverseInPlace2) {
        int x[] = {10,20,30,40,50,60};
        reverse_in_place(x,6);
        ASSERT_EQ(x[0],60);
        ASSERT_EQ(x[1],50);
        ASSERT_EQ(x[2],40);       
        ASSERT_EQ(x[3],30);   
        ASSERT_EQ(x[4],20);   
        ASSERT_EQ(x[5],10);                            
    }  
    TEST(HW2,ReverseInPlace3) {
        int x[] = {10};
        reverse_in_place(x,1);
        ASSERT_EQ(x[0],10);                           
    }  
    TEST(HW2,ReverseInPlace4) {
        int x[] = {10,20};
        reverse_in_place(x,2);
        ASSERT_EQ(x[0],20);  
        ASSERT_EQ(x[1],10);                          
    }  

    TEST(HW2,Reverse) {
        int x[] = {10,20,30,40,50};
        int * y = reverse(x,5);
        ASSERT_EQ(y[0],50);
        ASSERT_EQ(y[1],40);       
        ASSERT_EQ(y[2],30);   
        ASSERT_EQ(y[3],20);   
        ASSERT_EQ(y[4],10);  
        free(y);
    }
    TEST(HW2,Reverse2) {
        int x[] = {10,20,30,40,50,60};
        int * y = reverse(x,6);
        ASSERT_EQ(y[0],60);
        ASSERT_EQ(y[1],50);
        ASSERT_EQ(y[2],40);       
        ASSERT_EQ(y[3],30);   
        ASSERT_EQ(y[4],20);   
        ASSERT_EQ(y[5],10);  
        free(y);
    }
    TEST(HW2,Reverse3) {
        int x[] = {10};
        int * y = reverse(x,1);  
        ASSERT_EQ(y[0],10);  
        free(y);
    }
    TEST(HW2,Reverse4) {
        int x[] = {10,20};
        int * y = reverse(x,2);  
        ASSERT_EQ(y[0],20); 
        ASSERT_EQ(y[1],10);  
        free(y);
    }

    TEST(HW2,NumInstances) {
        int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
        ASSERT_EQ(num_instances(a,10,1), 3);
    }

    TEST(HW2,NumInstances1) {
        int a[] = { 1 };
        ASSERT_EQ(num_instances(a,1,1), 1);
    }

    TEST(HW2,NumInstances2) {
        int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
        ASSERT_EQ(num_instances(a,10,7), 0);
    }
    
    TEST(HW2,NumInstances3) {
        int a[] = { 1, 1 };
        ASSERT_EQ(num_instances(a,2,2), 0);
    }

    Point negate(Point p) {
      return { -p.x, -p.y, -p.z };
    }
    TEST(HW2,PointMap) {
      Point a[] = { { 1,2,3 }, { 2,3,4 } };
      Point * b = map(a,2,negate);
      for(int i=0; i<2; i++) {
        ASSERT_EQ(b[i].x,-a[i].x);
        ASSERT_EQ(b[i].y,-a[i].y);
        ASSERT_EQ(b[i].z,-a[i].z);
      }
      free(b);
    }   

    Point negateSeg(Point p) {
      return { -p.x, p.y, -p.z };
    }    
    TEST(HW2,PointMap2) {
      Point a[] = { { 1,2,3 }, { 2,3,4 } };
      Point * b = map(a,2,negateSeg);
      for(int i=0; i<2; i++) {
        ASSERT_EQ(b[i].x,-a[i].x);
        ASSERT_EQ(b[i].y,a[i].y);
        ASSERT_EQ(b[i].z,-a[i].z);
      }
      free(b);
    }   
}