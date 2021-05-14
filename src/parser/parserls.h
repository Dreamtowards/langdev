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
#include "parser_or.h"
#include "parser_lookahead_tag.h"


class parserls : public parser {

public:
    vector<parser*> m_components;

    bool m_use_lookahead = false;

    /**
     *  AST Create function. create ast when parser.read().
     *  null: pass through reads.  nonnull: create one ast from reads.
     */
    function<ast*(vector<ast*>)> m_createfunc = nullptr;

    vector<ast*> read(lexer* lexer) override {
        vector<ast*> ls;
        for (parser* p : m_components) {
            vector<ast*> rs = p->read(lexer);
            ls.insert(ls.end(), rs.begin(), rs.end());
        }
        if (m_createfunc != nullptr) {
            // create AST.
            ast* r = m_createfunc(ls);
            vector<ast*> wr(1, r);
            return wr;
        } else {
            // pass through.
            return ls;
        }
    }

    bool match(lexer* lex) override {
        if (m_components.empty())
            return true;  // empty is allowed. (as want to create an empty AST.
        if (!m_use_lookahead)
            return m_components.at(0)->match(lex);  // as lookahead doesnt needed, just test the first.

        // lookahead until
        int mark = lex->m_index;
        bool pass = true;
        for (parser* p : m_components) {
            if (p == parser_lookahead_tag::instance())
                break;
            try {
                p->read(lex);
            } catch (runtime_error& ex) {
                pass = false;
                break;
            }
        }
        lex->m_index = mark;
        return pass;
    }

    parserls* add_component(parser* p) {
        m_components.push_back(p);
        return this;
    }


    parserls* c_number() {
        auto* p = new parser_token();
        p->validator = [](token* t) -> const char* {
            if (!t->isNumber())
                return "Required Number Type.";
            return nullptr;
        };
        return add_component(p);
    }

    parserls* c_id(const string& id) {
        auto* p = new parser_token();
        p->validator = [id](token* t) -> const char* {
            if (!t->isIdentifier())
                return "Required Identifier Type.";
            if (t->m_text != id)
                return "Bad id. not as expected.";
            return nullptr;
        };
        p->createfunc = nullptr;  // Do not needs ast-result.
        return add_component(p);
    }

    parserls* c_string() {
        auto* p = new parser_token();
        p->validator = [](token* t) -> const char* {
            if (!t->isString())
                return "Required String Type.";
            return nullptr;
        };
        return add_component(p);
    }

    parserls* c_name() {
        auto* p = new parser_token();
        p->validator = [](token* t) -> const char* {
            if (!t->isName())
                return "Required Name Type.";
            return nullptr;
        };
        return add_component(p);
    }


    parserls* c_or(const vector<parser*>& v) {
        auto* p = new parser_or(v);
        return add_component(p);
    }
    parserls* c_or(int num, ...) {
        va_list va_ls;
        va_start(va_ls, num);
        vector<parser*> v;
        for (int i = 0;i < num;i++) {
            v.push_back(va_arg(va_ls, parser*));
        }
        va_end(va_ls);
        return c_or(v);  // really add.
    }


    parserls* mark_lookahead() {
        m_use_lookahead = true;
        return add_component(parser_lookahead_tag::instance());
    }
};

parserls* pass() {
    return new parserls();
}
parserls* struc(function<ast*(vector<ast*>)>& createfunc) {
    auto* p = new parserls();
    p->m_createfunc = createfunc;
    return p;
}



#endif //LANGDEV_PARSERLS_H
