#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <float.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    // double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    // double value = DynamicArray_get(da, 0);
    double value = DynamicArray_first(da);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    // DynamicArray * result = DynamicArray_new();
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(result, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

double DynamicArray_min ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double minValue = DBL_MAX;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        if (da->buffer[da, index_to_offset(da, i)] < minValue) {
            minValue = da->buffer[da, index_to_offset(da, i)];
        }
    }
    return minValue;
}

double DynamicArray_max ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double maxValue = DBL_MIN;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        if (da->buffer[da, index_to_offset(da, i)] > maxValue) {
            maxValue = da->buffer[da, index_to_offset(da, i)];
        }
    }
    return maxValue;    
}
double DynamicArray_mean ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum = sum + da->buffer[da, index_to_offset(da, i)];
    }
    return (sum / DynamicArray_size(da));  
}

double DynamicArray_median ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    int n = DynamicArray_size(da);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (da->buffer[index_to_offset(da, i)] > da->buffer[index_to_offset(da, j)]) {
                double temp = da->buffer[index_to_offset(da, i)];
                da->buffer[index_to_offset(da, i)] = da->buffer[index_to_offset(da, j)];
                da->buffer[index_to_offset(da, j)] = temp;
            }
        }
    }
    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    double median = 0;
    if (n % 2 == 0) {
        median = (da->buffer[index_to_offset(da, (n - 1) / 2)] + da->buffer[index_to_offset(da, (n - 1) / 2 + 1)]) / 2;
    } else {
        median = da->buffer[index_to_offset(da, (n - 1) / 2)];
    }
    return median;
}

double DynamicArray_sum ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum = sum + da->buffer[da, index_to_offset(da, i)];
    }
    return sum;  
}

double DynamicArray_last ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    return DynamicArray_get(da, DynamicArray_size(da) - 1);
}

double DynamicArray_first ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    return DynamicArray_get(da, 0);
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ) {
    DynamicArray * res = DynamicArray_new();
    res->capacity = da->capacity;
    res->end = da->end;
    res->origin = da->origin;
    res->buffer = (double *) calloc ( res->capacity, sizeof(double) );
    for (int i = 0; i < DynamicArray_size(da); i++) {
        DynamicArray_set(res, i, da->buffer[index_to_offset(da, i)]);
    }
    return res;
}

DynamicArray * DynamicArray_range ( double a, double b, double step) {
    assert((b > a && step > 0) || (b < a && step < 0));

    DynamicArray * res = DynamicArray_new();

    if (b > a && step > 0) {
        double cumu = a;
        for (int i = 0; cumu <= b; cumu = cumu + step, i = i + 1) {
            DynamicArray_set(res, i, cumu);
        }
    } else if (b < a && step < 0) {
        double cumu = a;
        for (int i = 0; cumu >= b; cumu = cumu + step, i = i + 1) {
            DynamicArray_set(res, i, cumu);
        }
    } 

    return res;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ) {
    DynamicArray * res = DynamicArray_new();
    int index = 0;
    int i = 0, j = 0;
    while (i < DynamicArray_size(a) && j < DynamicArray_size(b)) {
        if (DynamicArray_get(a, i) <= DynamicArray_get(b, j)) {
            DynamicArray_set(res, index, DynamicArray_get(a, i));
            i++;
            index++;
        } else {
            DynamicArray_set(res, index, DynamicArray_get(b, j));
            j++;
            index++;
        }
    }
    while (i < DynamicArray_size(a)) {
        DynamicArray_set(res, index, DynamicArray_get(a, i));
        i++;
        index++;
    }
    while (j < DynamicArray_size(b)) {
        DynamicArray_set(res, index, DynamicArray_get(b, j));
        j++;
        index++;
    }
    return res;
}

DynamicArray * DynamicArray_take(const DynamicArray * da, int a) {
    DynamicArray * res = DynamicArray_new();
    if (a > 0) {
        int i = 0;
        for (; i < a && i < DynamicArray_size(da); i++) {
            DynamicArray_set(res, i, DynamicArray_get(da, i));
        }
        while (i < a) {
            DynamicArray_set(res, i, 0);
            i++;
        }
    } else if (a < 0) {
        int i = DynamicArray_size(da) - 1;
        int count = 0;
        a = -a;
        for (; i >= 0 && count < a; i--) {
            DynamicArray_push_front(res, DynamicArray_get(da, i));
            count++;
        }
        while (count < a) {
            DynamicArray_push_front(res, 0);
            count++;
        }
    }
    return res;
}