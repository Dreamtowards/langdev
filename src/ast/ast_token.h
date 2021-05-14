//
// Created by Dreamtowards on 2021/5/1.
//

#ifndef LANGDEV_AST_TOKEN_H
#define LANGDEV_AST_TOKEN_H

#include "ast.h"
#include "../lexer/token.h"

class ast_token : public ast {

public:
    token* m_token;

    ast_token(token* tIn) : m_token(tIn) {};

    string to_string() override {
        return "'"+m_token->to_string()+"'";
    }

};

#endif //LANGDEV_AST_TOKEN_H
