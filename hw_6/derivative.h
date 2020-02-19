#ifndef _DERIVATIVE_H
#define _DERIVATIVE_H

#include "elma/elma.h"

using namespace elma;

class Derivative : public Process {

    // This process keeps track of the minimum and maximum values
    // that it has seen on a channel called link.

    public:

    // The constructor calls the parent constructor, and initializes
    // a boolean, _no_data, which keeps track of whether this process
    // has seen any data.
    Derivative(std::string name) : Process(name) {}
    void init() {}
    void start();
    void update();   // This method is implemented in extrema.cc
    void stop() {}  
    double value();

    private:
    double _last;
    double _current;
    bool _hasOne;
    bool _hasTwo;
    double _deri;
};  

#endif