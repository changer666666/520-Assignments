#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


void sort_by_magnitude(vector<double> &);

vector<int> primes(int n);

vector<tuple<int,int>> twins(vector<int> nums);

#endif