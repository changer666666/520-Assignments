#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         

    TEST(DynamicArray, min) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 1);    
        DynamicArray_set(da, 1, 2);  
        DynamicArray_set(da, 2, 5);  
        DynamicArray_set(da, 3, 8);  
        DynamicArray_set(da, 4, 4);  
        DynamicArray_set(da, 5, 0);      
        DynamicArray_set(da, 6, 3);
        ASSERT_EQ(DynamicArray_min(da),0);
        DynamicArray_pop(da);
        DynamicArray_pop(da);
        ASSERT_EQ(DynamicArray_min(da),1);
        DynamicArray_pop_front(da);
        ASSERT_EQ(DynamicArray_min(da),2);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, max) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 8);    
        DynamicArray_set(da, 1, 2);  
        DynamicArray_set(da, 2, 5);  
        DynamicArray_set(da, 3, 6);  
        DynamicArray_set(da, 4, 4);  
        DynamicArray_set(da, 5, 7);      
        DynamicArray_set(da, 6, 3);
        ASSERT_EQ(DynamicArray_max(da),8);
        DynamicArray_pop_front(da);
        ASSERT_EQ(DynamicArray_max(da),7);
        DynamicArray_pop(da);
        DynamicArray_pop(da);
        ASSERT_EQ(DynamicArray_max(da),6);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, mean) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 8);    
        DynamicArray_set(da, 1, 2); 
        ASSERT_EQ(DynamicArray_mean(da),5); 
        DynamicArray_set(da, 2, 5);  
        ASSERT_EQ(DynamicArray_mean(da),5); 
        DynamicArray_set(da, 3, 6);  
        DynamicArray_set(da, 4, 4);  
        ASSERT_EQ(DynamicArray_mean(da),5); 
        DynamicArray_set(da, 5, 7);      
        DynamicArray_set(da, 6, 3);
        ASSERT_EQ(DynamicArray_mean(da),5); 
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, sum) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 8);    
        DynamicArray_set(da, 1, 2); 
        ASSERT_EQ(DynamicArray_sum(da),10); 
        DynamicArray_set(da, 2, 5);  
        ASSERT_EQ(DynamicArray_sum(da),15); 
        DynamicArray_set(da, 3, 6);  
        DynamicArray_set(da, 4, 4);  
        ASSERT_EQ(DynamicArray_sum(da),25); 
        DynamicArray_set(da, 5, 7);      
        DynamicArray_set(da, 6, 3);
        ASSERT_EQ(DynamicArray_sum(da),35); 
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, median) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 8);    
        DynamicArray_set(da, 1, 2); 
        ASSERT_EQ(DynamicArray_median(da),5); 
        DynamicArray_set(da, 2, 5);  
        ASSERT_EQ(DynamicArray_median(da),5);
        DynamicArray_set(da, 3, 6);  
        DynamicArray_set(da, 4, 4);  
        ASSERT_EQ(DynamicArray_median(da),5); 
        DynamicArray_set(da, 5, 7);      
        DynamicArray_set(da, 6, 3);
        ASSERT_EQ(DynamicArray_median(da),5);
        DynamicArray_destroy(da);
    }
    TEST(DynamicArray, median2) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 8);    
        DynamicArray_set(da, 1, 1); 
        ASSERT_NEAR(DynamicArray_median(da),4.5,0.0001); 
        DynamicArray_set(da, 2, 5);  
        ASSERT_EQ(DynamicArray_median(da),5);
        DynamicArray_set(da, 3, 6);  
        ASSERT_NEAR(DynamicArray_median(da),5.5,0.0001); 
        DynamicArray_destroy(da);
    }
    TEST(DynamicArray, lastAndFirst) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, 8);    
        DynamicArray_set(da, 1, 1); 
        ASSERT_EQ(DynamicArray_last(da),1); 
        ASSERT_EQ(DynamicArray_first(da),8); 
        DynamicArray_set(da, 2, 5);  
        ASSERT_EQ(DynamicArray_last(da),5); 
        DynamicArray_pop_front(da); 
        ASSERT_EQ(DynamicArray_first(da),1); 
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, copy) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 0, 8);    
        DynamicArray_set(da, 1, 1); 
        DynamicArray_set(da, 2, 5);  
        DynamicArray_set(da, 5, 7);      
        DynamicArray_set(da, 6, 3);

        DynamicArray * c = DynamicArray_copy(da);
        ASSERT_EQ(DynamicArray_size(c),7);
        ASSERT_EQ(DynamicArray_get(c, 0),8);
        ASSERT_EQ(DynamicArray_get(c, 1),1);
        ASSERT_EQ(DynamicArray_get(c, 2),5);
        ASSERT_EQ(DynamicArray_get(c, 5),7);
        ASSERT_EQ(DynamicArray_get(c, 6),3);
        DynamicArray_destroy(da);
        DynamicArray_destroy(c);
    }

    TEST(DynamnicArray,range) {
        DynamicArray * da = DynamicArray_range(0, 0.4, 0.1);
        ASSERT_NEAR(DynamicArray_get(da,0), 0.0000, 0.00001); 
        ASSERT_NEAR(DynamicArray_get(da,1), 0.1000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,2), 0.2000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,3), 0.3000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,4), 0.4000, 0.00001);

        DynamicArray_destroy(da);
    }

    TEST(DynamnicArray,rangeNeg) {
        DynamicArray * da = DynamicArray_range(5, 0, -1);
        ASSERT_NEAR(DynamicArray_get(da,0), 5, 0.00001); 
        ASSERT_NEAR(DynamicArray_get(da,1), 4, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,2), 3, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,3), 2, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,4), 1, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,5), 0, 0.00001);
        DynamicArray_destroy(da);
    }

    TEST(DynamnicArray,concat) {
        DynamicArray * a = DynamicArray_range(0, 0.2, 0.1);
        DynamicArray * b = DynamicArray_range(0.3, 0.4, 0.1);
        DynamicArray * da = DynamicArray_concat(a, b); /* yeilds [ 0, 0.1, ..., 2.0 ] */
        ASSERT_NEAR(DynamicArray_get(da,0), 0.0000, 0.00001); 
        ASSERT_NEAR(DynamicArray_get(da,1), 0.1000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,2), 0.2000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,3), 0.3000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,4), 0.4000, 0.00001);
        DynamicArray_destroy(da);
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamnicArray,takePosLess) {
        DynamicArray * a = DynamicArray_range(0, 0.2, 0.1);
        DynamicArray * da = DynamicArray_take(a, 2); /* yeilds [ 0, 0.1, ..., 2.0 ] */
        ASSERT_NEAR(DynamicArray_get(da,0), 0.0000, 0.00001); 
        ASSERT_NEAR(DynamicArray_get(da,1), 0.1000, 0.00001);
        DynamicArray_destroy(da);
        DynamicArray_destroy(a);
    }

    TEST(DynamnicArray,takePosMore) {
        DynamicArray * a = DynamicArray_range(0, 0.2, 0.1);
        DynamicArray * da = DynamicArray_take(a, 4); /* yeilds [ 0, 0.1, ..., 2.0 ] */
        ASSERT_NEAR(DynamicArray_get(da,0), 0.0000, 0.00001); 
        ASSERT_NEAR(DynamicArray_get(da,1), 0.1000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,2), 0.2000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,3), 0.0000, 0.00001);
        DynamicArray_destroy(da);
        DynamicArray_destroy(a);
    }

    TEST(DynamnicArray,takeNegLess) {
        DynamicArray * a = DynamicArray_range(0, 0.2, 0.1);
        DynamicArray * da = DynamicArray_take(a, -2); /* yeilds [ 0, 0.1, ..., 2.0 ] */
        ASSERT_NEAR(DynamicArray_get(da,0), 0.1000, 0.00001); 
        ASSERT_NEAR(DynamicArray_get(da,1), 0.2000, 0.00001);
        DynamicArray_destroy(da);
        DynamicArray_destroy(a);
    }

    TEST(DynamnicArray,takeNegMore) {
        DynamicArray * a = DynamicArray_range(0, 0.2, 0.1);
        DynamicArray * da = DynamicArray_take(a, -4); /* yeilds [ 0, 0.1, ..., 2.0 ] */
        ASSERT_NEAR(DynamicArray_get(da,0), 0.0000, 0.00001); 
        ASSERT_NEAR(DynamicArray_get(da,1), 0.0000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,2), 0.1000, 0.00001);
        ASSERT_NEAR(DynamicArray_get(da,3), 0.2000, 0.00001);
        DynamicArray_destroy(da);
        DynamicArray_destroy(a);
    }
}