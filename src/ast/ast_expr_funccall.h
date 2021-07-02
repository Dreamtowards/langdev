//
// Created by Dreamtowards on 2021/7/2.
//

#ifndef LANGDEV_AST_EXPR_FUNCCALL_H
#define LANGDEV_AST_EXPR_FUNCCALL_H

#include "ast.h"
#include "astls.h"

class ast_expr_funccall : public ast {

public:
    ast* func_ptr;
    astls* func_params;

    explicit ast_expr_funccall(const std::vector<ast*>& ls) :
        func_ptr(ls.at(0)),
        func_params(dynamic_cast<astls*>(ls.at(1))) {}


    std::string to_string() override {
        return "ast_funccall{"+func_ptr->to_string()+"("+func_params->to_string()+")}";
    }
};

#endif //LANGDEV_AST_EXPR_FUNCCALL_H
