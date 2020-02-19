#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H

#include "elma/elma.h"

using namespace elma;

class Integrator : public Process {

    // This process keeps track of the minimum and maximum values
    // that it has seen on a channel called link.

    public:

    // The constructor calls the parent constructor, and initializes
    // a boolean, _no_data, which keeps track of whether this process
    // has seen any data.
    Integrator(std::string name) : Process(name) {}
    void init() {}
    void start();
    void update();   // This method is implemented in extrema.cc
    void stop() {}  
    double value();

    private:
    double _sum;
};  

#endif