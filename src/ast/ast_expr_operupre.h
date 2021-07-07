//
// Created by Dreamtowards on 2021/7/3.
//

#ifndef LANGDEV_AST_EXPR_OPERUPRE_H
#define LANGDEV_AST_EXPR_OPERUPRE_H

#include <vector>
#include <string>

#include "ast.h"
#include "ast_token.h"

class ast_expr_operupre : public ast {

public:
    std::string m_oper;
    ast* m_expr;

    explicit ast_expr_operupre(const std::vector<ast*>& ls) :
        m_oper(dynamic_cast<ast_token*>(ls.at(0))->m_token->m_text),
        m_expr(ls.at(1)) {}

    std::string to_string() override {
        return "("+m_oper+m_expr->to_string()+")";
    }
};

#endif //LANGDEV_AST_EXPR_OPERUPRE_H
