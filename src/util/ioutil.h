//
// Created by Dreamtowards on 2021/4/29.
//

#ifndef LANGDEV_IOUTIL_H
#define LANGDEV_IOUTIL_H

#include <string>
#include <sstream>

using namespace std;

class ioutil {

public:
    static string toString(istream& in) {
        stringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

};

#endif //LANGDEV_IOUTIL_H
