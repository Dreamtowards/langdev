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

    ast_token(token* token) : m_token(token) {};

    std::string to_string() override {
        return m_token->to_string();
    }

    static std::string cast_text(ast* a) {
        return dynamic_cast<ast_token*>(a)->m_token->m_text;
    }
};

#endif //LANGDEV_AST_TOKEN_H
