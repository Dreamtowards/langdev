//
// Created by Dreamtowards on 2021/5/14.
//

#ifndef LANGDEV_AST_EXPR_OPERBI_H
#define LANGDEV_AST_EXPR_OPERBI_H

#include "ast.h"
#include "ast_token.h"

class ast_expr_operbi : public ast {

public:
    ast* m_left;
    ast* m_right;
    std::string m_oper;

    ast_expr_operbi(ast* l, std::string& o, ast* r) : m_left(l), m_oper(o), m_right(r) {}

    explicit ast_expr_operbi(const std::vector<ast*>& ls) :
        m_left(ls.at(0)),
        m_oper(ast_token::cast_text(ls.at(1))),
        m_right(ls.at(2))
        {}

    std::string to_string() override {
        return "("+m_left->to_string()+" "+m_oper+" "+m_right->to_string()+")";
    }
};

#endif //LANGDEV_AST_EXPR_OPERBI_H
