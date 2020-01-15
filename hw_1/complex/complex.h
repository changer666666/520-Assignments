#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Complex object and method definitions
 *
 *  A Complex object is a struct with a real and a imaginary. 
 */
typedef struct {
    double real;
    double im;
} Complex;

// (x + yi) + (u + vi) = (x + u) + (y + v)i
Complex add ( Complex a, Complex b );

// (x - yi) -> (- x + yi)
Complex negate ( Complex a);

// (x + yi)(u + vi) = (xu - yv) + (xv + yu)i
Complex multiply ( Complex a, Complex b );

// (x + yi) ->sqrt(x * x + y * y)
double magnitude ( Complex a);

#endif