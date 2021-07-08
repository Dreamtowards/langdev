#include <iostream>
#include <fstream>
#include <string>

#include "lexer/lexer.h"
#include "parser/parserls.h"
#include "ast/ast_expr_operbi.h"

#include "util/util.h"
#include "ast/ast_expr_funccall.h"
#include "ast/astls.h"
#include "ast/ast_expr_operupost.h"
#include "ast/ast_expr_opertricon.h"
#include "ast/ast_expr_operupre.h"


int main() {

    std::ifstream fs("../main.g");
    std::string s = util::to_string(fs);

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

        // Parentheses
        auto* expr_zero = pass()->or_p({
            pass()->id("(")->andp(exprbase)->id(")"),
            primary
        });

        auto* _func_arg_ls = struc<astls>()->op(pass()->andp(exprbase)->repeat(pass()->id(",")->andp(exprbase)));

        // MemberAccess, FunctionCall
        auto* expr1 = pass()->andp(expr_zero)->repeat(pass()->or_p({
            pass()->iden({"."})->name()->composesp<ast_expr_operbi>(3),
            pass()->id("(")->andp(_func_arg_ls)->id(")")->composesp<ast_expr_funccall>(2)
        }));

        // Unary Post
        auto* expr2 = pass()->andp(expr1)->repeat(pass()->iden({"++", "--"})->composesp<ast_expr_operupost>(2));

        // Unary Pre
        auto* expr3 = pass();
              expr3->or_p({
                pass()->iden({"++", "--", "+", "-", "!", "~"})->andp(expr3)->composesp<ast_expr_operupre>(2),
                expr2});

        // Multiplication / Addition.
        auto* expr4 = pass()->_expr_bi_lr(expr3, {"*", "/"});
        auto* expr5 = pass()->_expr_bi_lr(expr4, {"+", "-"});
        auto* expr6 = pass()->_expr_bi_lr(expr5, {"<<", ">>", ">>>"});

        // Relations
        auto* expr7 = pass()->_expr_bi_lr(expr6, {"<", "<=", ">", ">=", "is"});
        auto* expr8 = pass()->_expr_bi_lr(expr7, {"==", "!="});

        // Bitwise Logical
        auto* expr9 = pass()->_expr_bi_lr(expr8, {"&"});
        auto* expr10 = pass()->_expr_bi_lr(expr9, {"^"});
        auto* expr11 = pass()->_expr_bi_lr(expr10, {"|"});

        // Logical
        auto* expr12 = pass()->_expr_bi_lr(expr11, {"&&"});
        auto* expr13 = pass()->_expr_bi_lr(expr12, {"||"});

        // Trinary Conditional, Lambda Expression.
        auto* expr14 = pass();
              expr14->andp(expr13)->op(pass()->id("?")->andp(expr14)->id(":")->andp(expr14)->composesp<ast_expr_opertricon>(3));

        // Assignments.
        auto* expr15 = pass();
              expr15->andp(expr14)->repeat(pass()->iden({"="})->andp(expr15));

        exprbase->andp(expr15);
    }

    try {
        ast* ast = exprbase->readone(lex);
        std::cout << "AST: " << ast->to_string() << std::endl;
        std::cout << std::endl;


//        std::cout << "EVAL: " << ast->eval() << std::endl;

    } catch (std::runtime_error& err) {
        std::cerr << "ERR: " << err.what() << std::endl;
        lex->m_index--;  // not actual right
        std::cerr << "LXR["<<lex->m_index<<"]: " << lex->peek()->m_text << std::endl;
    }

    return 0;
}
