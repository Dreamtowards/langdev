//
// Created by Dreamtowards on 2021/5/5.
//

#ifndef LANGDEV_PARSER_TOKEN_H
#define LANGDEV_PARSER_TOKEN_H

#include "../lexer/token.h"
#include "../ast/ast_token.h"

#include "parser.h"

using namespace std;

ast* default_asttoken_createfunc(token t) {
    return new ast_token(t);
}
const char* default_token_validator(token t) {
    return nullptr;
}


class parser_token : public parser {

public:
    ast*        (*createfunc)(token) = &default_asttoken_createfunc;
    const char* (*validator) (token) = &default_token_validator;

    vector<ast*> read(lexer* lexer) override {
        token t = lexer->next();
        const char* err = (*validator)(t);
        if (err)
            throw std::runtime_error(strstr("Bad token: ", err));

        ast* r = (*createfunc)(t);
        vector<ast*> l(1, r);
        return l;
    }

    bool match(lexer* lexer) override {
        token t = lexer->peek();
        const char* err = (*validator)(t);
        return err == nullptr;
    }

};

#endif //LANGDEV_PARSER_TOKEN_H
