#include "fraction.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce ( Fraction a ) {
  int num = a.num;
  int den = a.den;
  bool isNegtive = false;

  if (den == 0 && num == 0) return (Fraction) { num, den };
  if (den == 0) return (Fraction) { 1, den };
  if (num == 0) return (Fraction) { num, 1 };
  if ((num < 0 && den > 0) || (num > 0 && den < 0)) isNegtive = true;

  num = abs(num);
  den = abs(den);
  for (int  i = 2; i <= num && i <= den; i++) {
    if (num % i == 0 && den % i == 0) {
      num = num / i;
      den = den / i;
      i = 1;
    }
  }
  if (isNegtive) return (Fraction) { -num, den };
  return (Fraction) { num, den };
}