#ifndef _RANDOM_PROCESS_H
#define _RANDOM_PROCESS_H

#include "elma/elma.h"

using namespace elma;

class RandomProcess : public Process {

    public:

    RandomProcess(std::string name) : Process(name) {}

    void init() {}
    void start() {}
    void update();   // This method is implemented in extrema.cc
    void stop() {}   
};  

double fRand(double, double);

#endif