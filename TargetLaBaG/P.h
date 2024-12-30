#pragma once

#include <string>
#include <map>
using namespace std;

class P {
public:
    string code;
    int Score[3];
    map<string, int> Rate;

    P();
    P(string c, int s[3], map<string, int> r);

    bool operator==(const P& other) const;
    bool operator!=(const P& other) const;
};

