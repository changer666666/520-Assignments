#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include <random_process.h>

void RandomProcess::update() {
    double num = fRand(0, 1);
    channel("link").send(num);
    std::cout << num << " \n";
}

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


