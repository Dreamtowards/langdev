#include <iostream>
#include <fstream>
#include <string>

#include "lexer/lexer.h"
#include "parser/parserls.h"
#include "ast/ast_expr.h"

#include "util/util.h"
#include "ast/ast_expr_funccall.h"
#include "ast/astls.h"

int main() {


    ifstream fs("../main.g");
    string s = util::to_string(fs);

    auto* lex = new lexer();
    lex->read(s);


    auto* exprbase = pass();
    {
        auto* literal_number = pass()->number();
        auto* literal_string = pass()->string();
        auto* varname = pass()->name();

        auto* primary = pass()->or_p({
            literal_number,
            literal_string,
            varname});

        auto* expr_zero = pass()->or_p({
            pass()->id("(")->andp(exprbase)->id(")"),
            primary
        });

        auto* fn_arg_ls = struc<astls>()
                ->op(pass()->andp(exprbase)->repeat(pass()->id(",")->andp(exprbase)));

        auto* expr1 = pass()->andp(expr_zero)->repeat(pass()->or_p({
            pass()->iden({"."})->name()->composesp<ast_expr>(3),
            pass()->id("(")->andp(fn_arg_ls)->id(")")->composesp<ast_expr_funccall>(2)
        }));

        auto* expr4 = pass()->_expr_bi_lr(expr1, {"*", "/"});
        auto* expr5 = pass()->_expr_bi_lr(expr4, {"+", "-"});

        auto* expr8 = pass()->_expr_bi_lr(expr5, {"=="});

        auto* expr15 = pass();
        expr15->andp(expr8)->repeat(pass()->iden({"="})->andp(expr15));


        exprbase->andp(expr15);
    }

    ast* ast = exprbase->readone(lex);
    std::cout << "AST: " << ast->to_string() << std::endl;

    return 0;
}
