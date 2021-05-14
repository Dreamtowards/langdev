//
// Created by Dreamtowards on 2021/5/7.
//

#ifndef LANGDEV_PARSER_OR_H
#define LANGDEV_PARSER_OR_H

#include "parser.h"

class parser_or : public parser {

public:
    vector<parser*> m_options;

    parser_or(const vector<parser*>& v) : m_options(v) { }

    vector<ast*> read(lexer* lex) override {
        parser* p = choose(lex);
        if (!p)
            throw runtime_error("Bad or. no valid option.");
        return p->read(lex);
    }

    bool match(lexer* lex) override {
        return choose(lex) != nullptr;
    }

    parser* choose(lexer* lex) {
        for (parser* p : m_options) {
            if (p->match(lex))
                return p;
            // cout << "Bad option." << endl;
        }
        return nullptr;
    }

};


#endif //LANGDEV_PARSER_OR_H
