#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include "stopwatch.h"

using namespace elma;
using namespace std::chrono;

void Stopwatch::start() {
    s = high_resolution_clock::now();
    status = 1;
}

void Stopwatch::stop() {
    if (status == 0) return;
    e = high_resolution_clock::now();
    period += e - s;
    status = 0;
}

void Stopwatch::reset() {
    period = seconds_type::zero();
}

double Stopwatch::get_minutes() {
    typedef std::chrono::duration<double,std::ratio<60,1>> minutes_type;
    return minutes_type(period).count();  
}

double Stopwatch::get_seconds() {
    return period.count();
}

double Stopwatch::get_milliseconds() {
    typedef std::chrono::duration<double,std::milli> milliseconds_type;
    return milliseconds_type(period).count();
}

double Stopwatch::get_nanoseconds() {
    typedef std::chrono::duration<double,std::nano> nanoseconds_type;
    return nanoseconds_type(period).count();
}