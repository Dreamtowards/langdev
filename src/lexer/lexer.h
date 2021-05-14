//
// Created by Dreamtowards on 2021/4/29.
//

#ifndef LANGDEV_LEXER_H
#define LANGDEV_LEXER_H

#include <string>
#include <vector>
#include <iostream>

#include "token.h"

using namespace std;


class lexer {

public:
    int m_index;
    vector<token*> m_tokens;

    ~lexer() {
        std::cout << "Deconstruct lexer" << std::endl;
    }

    void read(string s);

    token* next() {
        return m_tokens.at(m_index++);
    }

    token* peek() {
        if (m_index == m_tokens.size())
            return nullptr;
        return m_tokens.at(m_index);
    }

    void dbg_print_tokens() {
        for (const token* t : m_tokens) {
            cout <<"TOKEN["<<t->m_type<<"]: "<< t->m_text << endl;
        }
    }

};


#endif //LANGDEV_LEXER_H
