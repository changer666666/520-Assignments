#ifndef _FILTER_H
#define _FILTER_H

#include "elma/elma.h"

using namespace elma;

class Filter : public Process {

    // This process keeps track of the minimum and maximum values
    // that it has seen on a channel called link.

    public:

    // The constructor calls the parent constructor, and initializes
    // a boolean, _no_data, which keeps track of whether this process
    // has seen any data.
    Filter(std::string name) : Process(name) {}

    void init() {}
    void start();
    void update();   // This method is implemented in extrema.cc
    void stop() {}  
    double value();

    private:
    double _sum;
    double _ave;
    deque<double> _nums;
};  

#endif