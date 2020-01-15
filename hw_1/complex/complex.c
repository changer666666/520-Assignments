#include "complex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// (x + yi) + (u + vi) = (x + u) + (y + v)i
Complex add ( Complex a, Complex b ) {
    return (Complex) {a.real + b.real, a.im + b.im};
}

// (x - yi) -> (- x + yi)
Complex negate ( Complex a) {
    return (Complex) {-a.real, -a.im};
}

// (x + yi)(u + vi) = (xu - yv) + (xv + yu)i
Complex multiply ( Complex a, Complex b ) {
    return (Complex) { (a.real * b.real - a.im * b.im), (a.real * b.im + a.im * b.real) };
}

// (x + yi) ->sqrt(x * x + y * y)
double magnitude ( Complex a) {
    return sqrt(a.real * a.real + a.im * a.im);
}
