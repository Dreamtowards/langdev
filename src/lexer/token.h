#include <utility>

//
// Created by Dreamtowards on 2021/4/29.
//

#ifndef LANGDEV_TOKEN_H
#define LANGDEV_TOKEN_H


class token {

public:
    static const int TYPE_NAME = 1;    // NAME IDENTIFIER
    static const int TYPE_BORDER = 2;  // BORDER IDENTIFIER
    static const int TYPE_NUMBER = 3;  // INT FLOAT   HEX OCT BIN.?
    static const int TYPE_STRING = 4;  // STRING CHAR.?

    std::string m_text;
    int m_type;

public:
    token(std::string textIn, int typeIn): m_text(textIn), m_type(typeIn) {};

    bool isName() const {
        return m_type == TYPE_NAME;
    }
    bool isBorder() const {
        return m_type == TYPE_BORDER;
    }
    bool isIdentifier() const {
        return isName() || isBorder();
    }
    bool isNumber() const {
        return m_type == TYPE_NUMBER;
    }
    bool isString() const {
        return m_type == TYPE_STRING;
    }



    std::string to_string() {
        return m_text;
    }

};

#endif //LANGDEV_TOKEN_H
