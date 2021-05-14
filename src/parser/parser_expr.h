//
// Created by Dreamtowards on 2021/5/7.
//

#ifndef LANGDEV_PARSER_EXPR_H
#define LANGDEV_PARSER_EXPR_H

#include <map>

#include "parser.h"
#include "../ast/ast_expr.h"

class operator_ {

public:
    int precedence;
    int associativity;

    static const int ASS_LEFT  = 0;  // Left to Right.
    static const int ASS_RIGHT = 1;  // Right to Left.

    static map<string, operator_*> operators;

    operator_() = default;

    operator_(int prec, int sd) : precedence(prec), associativity(sd) {}

    static void init_operators() {
        operators["="] = new operator_(1, ASS_RIGHT);
        operators["+"] = new operator_(2, ASS_LEFT);
        operators["-"] = new operator_(2, ASS_LEFT);
        operators["*"] = new operator_(3, ASS_LEFT);
        operators["/"] = new operator_(3, ASS_LEFT);
    }
};
map<string, operator_*> operator_::operators ;

class parser_expr : public parser {

public:
    parser* m_factor;

    explicit parser_expr(parser* p_f) : m_factor(p_f) {};

    vector<ast*> read(lexer* lex) override {
        ast* left = m_factor->readone(lex);
        operator_* opr;
        while ((opr=next_operator(lex)) != nullptr) {
            left = read_right_side(lex, left, opr->precedence);
        }
        vector<ast*> v(1, left);
        return v;
    }

    ast* read_right_side(lexer* lex, ast* left, int prec) const {
        token* opr = lex->next();
        ast* right = m_factor->readone(lex);
        operator_* next;
        while ((next=next_operator(lex)) != nullptr && is_right_higher_precedence(prec, next)) {
            right = read_right_side(lex, right, next->precedence);
        }
        return new ast_expr(left, opr, right);
    }

    static operator_* next_operator(lexer* lex) {
        token* t = lex->peek();
        if (!t) return nullptr;
        auto e = operator_::operators.find(t->m_text);
        if (e != operator_::operators.end()) {
            return e->second;
        }
        return nullptr;
    }

    static bool is_right_higher_precedence(int prev_prec, operator_* next) {
        if (next->associativity == operator_::ASS_RIGHT)
            return next->precedence >= prev_prec;
        else
            return next->precedence > prev_prec;
    }

    bool match(lexer* lex) override {
        return m_factor->match(lex);
    }
};

#endif //LANGDEV_PARSER_EXPR_H
