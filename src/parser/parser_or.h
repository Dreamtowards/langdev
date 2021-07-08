//
// Created by Dreamtowards on 2021/5/7.
//

#ifndef LANGDEV_PARSER_OR_H
#define LANGDEV_PARSER_OR_H

#include "parser.h"

class parser_or : public parser {

public:
    std::vector<parser*> m_options;

    explicit parser_or(const std::vector<parser*>& v) : m_options(v) { }

    void read(lexer* lex, std::vector<ast*>& out) override {
        parser* p = choose(lex);
        if (!p)
            throw std::runtime_error("Bad or. no valid option.");

        p->read(lex, out);
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
