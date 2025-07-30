#ifndef HELPER_H
#define HELPER_H

#include <bits/stdc++.h>

using namespace std;

class Helper {
public:
    //convert string to lower case
    string toLower(const string& str) {
        string res = str;
        transform(res.begin(), res.end(), res.begin(), ::tolower);
        return res;
    }  
};

#endif