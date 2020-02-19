#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include "derivative.h"


using namespace elma;

void Derivative::start() {
    _last = 0;
    _current = 0;
    _hasOne = false;
    _hasTwo = false;
    _deri = 0;
}

void Derivative::update() {
    if ( channel("link").nonempty() ) {
        if (_hasOne) {
            _last = _current;    
            _hasTwo = true;
        }
        _current = channel("link").latest();
        _hasOne = true;
        _deri = (_current - _last) / delta();
        
        std::cout << _deri << " \n";
    }
}

double Derivative::value() {
    if (_hasTwo == false) return 0;
    return _deri;
}



