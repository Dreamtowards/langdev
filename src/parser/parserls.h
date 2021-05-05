//
// Created by Dreamtowards on 2021/5/5.
//

#ifndef LANGDEV_PARSERLS_H
#define LANGDEV_PARSERLS_H

#include <utility>
#include <vector>

#include "../lexer/lexer.h"
#include "../ast/ast.h"

#include "parser.h"
#include "parser_token.h"


class parserls : parser {

public:
    vector<parser*> m_components;

    /**
     *  AST Create function. create ast when parser.read().
     *  null: pass through reads.  nonnull: create one ast from reads.
     */
    ast* (*m_createfunc)(vector<ast*>) = nullptr;

    vector<ast*> read(lexer* lexer) override {
        vector<ast*> ls;
        for (parser* p : m_components) {
            vector<ast*> rs = p->read(lexer);
            ls.insert(ls.end(), rs.begin(), rs.end());
        }
        if (m_createfunc != nullptr) {
            // create AST.
            ast* r = (*m_createfunc)(ls);
            vector<ast*> wr(1, r);
            return wr;
        } else {
            // pass through.
            return ls;
        }
    }

    /**
     * useful for ast-createfunc-nonnull. directly get that one result.
     */
    ast* readone(lexer* lexer) {
        vector<ast*> ls = read(lexer);
        assert(ls.size() == 1);
        return ls.at(0);
    }

    bool match(lexer* lexer) override {
        return false;
    }

    void add_component(parser* psr) {
        m_components.push_back(psr);
    }

    static ast* comp_asttoken_createfunc_number(token t) {

    }
    static const char* comp_token_validator_number(token t) {
        if (t.m_type != token::TOKEN_NUMBER)
            return "Required Number Type.";
        return nullptr;
    }
    void add_number() {
        parser_token* p = new parser_token();
//        p->createfunc = &comp_asttoken_createfunc_number;
        p->validator  = &comp_token_validator_number;
        add_component(p);
    }

};


#endif //LANGDEV_PARSERLS_H
