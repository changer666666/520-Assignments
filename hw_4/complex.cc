#include <math.h>
#include "complex.h"
#include <float.h> /* defines DBL_EPSILON */

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

double Complex::getRe() const {
    return re;
}

double Complex::getIm() const {
    return im;
}

// void Complex::setRe(const double a) const {
//     re = a;
// }

// void Complex::setIm(const double a) const {
//     im = a;
// }

Complex Complex::conjugate() const {
    Complex res(getRe(), -getIm());
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
    Complex res(a.getRe() * b.getRe() - a.getIm() * b.getIm(), a.getRe() * b.getIm() + a.getIm() * b.getRe());
    return res;
}

Complex operator+(const Complex& a, const Complex& b) {
    Complex res(a.getRe() + b.getRe(), a.getIm() + b.getIm());
    return res;
}

bool operator==(const Complex& a, const Complex& b) {
    if (fabs(a.getRe() - b.getRe()) < DBL_EPSILON && fabs(a.getIm() - b.getIm()) < DBL_EPSILON) {
        return true;
    } 
    return false;
}