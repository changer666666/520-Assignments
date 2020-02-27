#ifndef _BETTERSTATEMACHINE_H
#define _BETTERSTATEMACHINE_H

#include "elma/elma.h"
#include <iostream>
#include <vector>
#include <string>

using namespace elma;
using namespace std;
using nlohmann::json; 


class BetterStateMachine : public StateMachine {
    
    public:
    BetterStateMachine(std::string name){
        _BSM_name = name;
    }

    json to_json() const {
        json res;

        vector<json> trans;
        vector<string> states;
        for (int i = 0; i < _transitions.size(); i++) {
            string from = _transitions[i].from().name();
            string to = _transitions[i].to().name();

            json tmp;
            tmp["from"] = from;
            tmp["to"] = to;
            tmp["when"] = _transitions[i].event_name();
            trans.push_back(tmp);

            if (!is_element_in_vector(states, from)) {
                states.push_back(from);
            }
            if (!is_element_in_vector(states, to)) {
                states.push_back(to);
            }
        }
        if (!is_element_in_vector(states, _initial->name())) {
                states.push_back(_initial->name());
            }
        res["name"] = _BSM_name;
        res["states"] = states;
        res["transitions"] = trans;
        // std::cout << res << "\n";
    }


    bool is_element_in_vector(vector<string> v, string element) const {
        vector<string>::iterator it;
        it = find(v.begin(), v.end(), element);
        if (it != v.end()){
            return true;
        }
        else{
            return false;
        }
    }

    string _BSM_name;
};




#endif