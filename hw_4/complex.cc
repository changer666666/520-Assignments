#include <math.h>
#include "complex.h"
#include <float.h> /* defines DBL_EPSILON */

double Complex::magnitude() const {

    return sqrt(real * real + imaginary * imaginary);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

double Complex::re() const {
    return real;
}

double Complex::im() const {
    return imaginary;
}

// void Complex::setRe(const double a) const {
//     re = a;
// }

// void Complex::setIm(const double a) const {
//     im = a;
// }

Complex Complex::conjugate() const {
    Complex res(re(), -im());
    return res;
}

// Complex Complex::Complex(double x, double y) {
//     this.re = x;
//     this.im = y;
// }

// Complex Complex::Complex(double a) {
//     this.re = a;
//     this.im = 0;
// }

//(a+bi)(c+di)=(ac-bd)+(ad+bc)i
Complex operator*(const Complex& a, const Complex& b) {
    Complex res(a.re() * b.re() - a.im() * b.im(), a.re() * b.im() + a.im() * b.re());
    return res;
}

Complex Complex::operator+(const Complex& other) {
    Complex res(re() + other.re(), im() + other.im());
    return res;
}

bool operator==(const Complex& a, const Complex& b) {
    if (fabs(a.re() - b.re()) < DBL_EPSILON && fabs(a.im() - b.im()) < DBL_EPSILON) {
        return true;
    } 
    return false;
}