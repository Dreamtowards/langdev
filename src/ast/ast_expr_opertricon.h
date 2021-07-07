//
// Created by Dreamtowards on 2021/7/3.
//

#ifndef LANGDEV_AST_EXPR_OPERTRICON_H
#define LANGDEV_AST_EXPR_OPERTRICON_H

#include <vector>

#include "ast.h"

// Operator Trinary Conditional
class ast_expr_opertricon : public ast {

public:
    ast* m_cond;
    ast* m_then;
    ast* m_else;

    explicit ast_expr_opertricon(const std::vector<ast*>& ls) : m_cond(ls.at(0)), m_then(ls.at(1)), m_else(ls.at(2)) {}

    std::string to_string() override {
        return "("+m_cond->to_string()+" ? "+m_then->to_string()+" : "+m_else->to_string()+")";
    }
};

#endif //LANGDEV_AST_EXPR_OPERTRICON_H
