//
// Created by Dreamtowards on 2021/5/5.
//

#ifndef LANGDEV_PARSER_TOKEN_H
#define LANGDEV_PARSER_TOKEN_H

#include "../lexer/token.h"
#include "../ast/ast_token.h"

#include "parser.h"


class parser_token : public parser {

public:
    function<ast* (token*)>        createfunc = [](token* t) {return new ast_token(t);};  // nullable. null: ignore ast-result.
    function<const char* (token*)> validator  = [](token* t) {return nullptr;};

    void read(lexer* lexer, std::vector<ast*>& out) override {
        token* t = lexer->next();

        const char* err = validator(t);
        if (err)
            throw std::runtime_error(std::string("Bad token: ") + err);

        if (createfunc) {
            ast* r = createfunc(t);
            out.push_back(r);
        }
    }

    bool match(lexer* lex) override {
        token* t = lex->peek();
        const char* err = validator(t);
        return err == nullptr;
    }

};

#endif //LANGDEV_PARSER_TOKEN_H
