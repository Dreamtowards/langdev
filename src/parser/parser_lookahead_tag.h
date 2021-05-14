//
// Created by Dreamtowards on 2021/5/7.
//

#ifndef LANGDEV_PARSER_LOOKAHEAD_TAG_H
#define LANGDEV_PARSER_LOOKAHEAD_TAG_H

#include "parser.h"

class parser_lookahead_tag : public parser {

private:
    parser_lookahead_tag() = default;

public:
    static parser* instance() {
        static parser* _inst;
        if (_inst == nullptr)
            _inst = new parser_lookahead_tag();
        return _inst;
    }

    vector<ast*> read(lexer* lex) override {
        return {};
    }

    bool match(lexer* lex) override {
        return true;
    }

};

#endif //LANGDEV_PARSER_LOOKAHEAD_TAG_H
