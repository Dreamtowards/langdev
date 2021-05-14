//
// Created by Dreamtowards on 2021/5/14.
//

#ifndef LANGDEV_AST_EXPR_H
#define LANGDEV_AST_EXPR_H

#include "ast.h"
#include "ast_token.h"

class ast_expr : public ast {

public:
    ast* m_left;
    ast* m_right;
    token* m_opr;

    ast_expr(ast* l, token* o, ast* r) : m_left(l), m_opr(o), m_right(r) {}

    string to_string() override {
        return "("+m_left->to_string()+" "+m_opr->m_text+" "+m_right->to_string()+")";
    }
};

#endif //LANGDEV_AST_EXPR_H
