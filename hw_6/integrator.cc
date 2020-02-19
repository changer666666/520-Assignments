#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include "integrator.h"


using namespace elma;

void Integrator::start() {
    _sum = 0.0;
}

void Integrator::update() {
    if ( channel("link").nonempty() ) {
        double num = channel("link").latest();

        _sum += num * delta();
        
        std::cout << _sum << " \n";
    }
}

double Integrator::value() {
    return _sum;
}



