#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include "filter.h"


using namespace elma;
using std::vector;

void Filter::start() {
    _sum = 0.0;
    _ave = 0.0;
}

void Filter::update() {
    if ( channel("link").nonempty() ) {
        double num = channel("link").latest();

        if (_nums.size() >= 10) {
            _sum -= _nums.back();
            _nums.pop_back();
        }
        _nums.push_front(num);
        _sum += num;
        _ave = _sum / _nums.size();
        
        std::cout << _ave << "," << _nums.size() << " \n";
    }
}

double Filter::value() {
    return _ave;
}



