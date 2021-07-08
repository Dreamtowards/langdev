//
// Created by Dreamtowards on 2021/7/2.
//

#ifndef LANGDEV_PARSER_COMPOSER_H
#define LANGDEV_PARSER_COMPOSER_H

#include "parser.h"

class parser_composer : public parser {

public:
    std::function<void(std::vector<ast*>&)> m_composer_func;

    void read(lexer* lex, std::vector<ast*>& out) override {

        m_composer_func(out);

    }

    bool match(lexer *lex) override {
        return true;
    }
};

#endif //LANGDEV_PARSER_COMPOSER_H
