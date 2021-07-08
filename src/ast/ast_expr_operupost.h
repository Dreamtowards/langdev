//
// Created by Dreamtowards on 2021/7/2.
//

#ifndef LANGDEV_AST_EXPR_OPERUPOST_H
#define LANGDEV_AST_EXPR_OPERUPOST_H

#include <vector>

#include "ast.h"
#include "ast_token.h"

// operator unary post.
class ast_expr_operupost : public ast {

public:
    ast* m_expr;
    std::string m_oper;

    explicit ast_expr_operupost(const std::vector<ast*>& ls) :
        m_expr(ls.at(0)),
        m_oper(ast_token::cast_text(ls.at(1))) {}

    std::string to_string() override {
        return "("+m_expr->to_string()+m_oper+")";
    }
};

#endif //LANGDEV_AST_EXPR_OPERUPOST_H
