#include <exception>
#include "db.h"
#include <iostream>

using namespace std;

DB::DB() : _next_key(0) {}

DB &DB::insert(const string name, double mass, double distance) {
    for (auto [key, value] : _data) {
        if (get<0>(value) == name) {
            throw runtime_error("Name already exists");
        }
    }

    int key = _next_key++;
    _data[key] = make_tuple(name, mass, distance);
    return *this;

}

DB &DB::drop(int key) {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        _data.erase (e);
    }

    return *this;
}

DB::Row DB::to_row(int key, const DB::Value value) const {
    return make_tuple(key, get<0>(value), get<1>(value), get<2>(value));
}

DB::Row DB::find(int key) const {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        return to_row(key,e->second);
    } else {
        throw runtime_error("Could not find an entry with the given key");
    }

}

vector<DB::Row> DB::where(function<bool(const DB::Row)> f) const {

    vector<Row> rows;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( f(row) == true ) {
            rows.push_back(row);
        }
    }

    return rows;

}

DB::Row DB::find_by_name(const string name) const {
    Row res;
    for (auto [key, value] : _data) {      
        if (get<0>(value) == name) {
            res = to_row(key,value);
            return res;
        }
    }
    throw runtime_error("Could not find row by name" );
}

DB &DB::create_test_data(int n) {
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < n; i++) {
        //Names should be at least eight characters long. 
        string name;
        for (int j = 0; j < 9; ++j) {
            name += alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        //The mass should vary from 0.01 to 1000
        double mass = fRand(0.01, 1000);
        //The distance from 0.1 to 10,000,000.
        double dis = fRand(0.1, 10000000);

        insert(name, mass, dis);
    }
    return *this;
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int DB::size() const {
    return _data.size();
}

double DB::accumulate(function<double(const Row)> f) const {
    double res;
    for (auto [key, value] : _data) {
        res += f(to_row(key, value));
    }
    return res;
}

double DB::average_mass() const {
    double sum = 0;
    for (auto [key, value] : _data) {
        sum += get<1>(value);
    }
    return sum / size();
}

double DB::average_distance() const {
    double sum = 0;
    for (auto [key, value] : _data) {
        sum += get<2>(value);
    }
    return sum / size();
}