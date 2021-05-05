#include <utility>

//
// Created by Dreamtowards on 2021/4/29.
//

#ifndef LANGDEV_TOKEN_H
#define LANGDEV_TOKEN_H

using namespace std;

class token {

public:
    static const int TOKEN_IDENTIFIER = 1;   // BORDER NAME
    static const int TOKEN_NUMBER = 2;       // INT FLOAT   HEX OCT BIN.?
    static const int TOKEN_STRING = 3;       // STRING CHAR.?

    string m_text;
    int m_type;

public:
    token(string textIn, int typeIn): m_text(textIn), m_type(typeIn) {};

    string to_string() {
        return m_text;
    }

};

#endif //LANGDEV_TOKEN_H
