//
// Created by Dreamtowards on 2021/5/18.
//

#ifndef LANGDEV_PARSER_REPEAT_H
#define LANGDEV_PARSER_REPEAT_H

#include "parser.h"

class parser_repeat : public parser {

public:
    parser* m_parser;
    bool m_max_one = false;  // use for option.

    void read(lexer* lex, std::vector<ast*>& out) override {
        while (match(lex))
        {
            m_parser->read(lex, out);

            if (m_max_one)
                break;
        }
    }

    bool match(lexer* lex) override {
        return m_parser->match(lex);
    }

};

#endif //LANGDEV_PARSER_REPEAT_H
