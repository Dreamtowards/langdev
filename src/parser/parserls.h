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
#include "parser_repeat.h"
#include "parser_composer.h"
#include "../ast/ast_expr.h"

class parserls;
parserls* pass();

class parserls : public parser {

public:
    vector<parser*> m_components;

    bool m_use_lookahead = false;

    /**
     *  AST Create function. create ast when parser.read().
     *  null: pass through reads.  nonnull: create one ast from reads.
     */
    function<ast*(vector<ast*>)> m_createfunc = nullptr;

    void read(lexer* lexer, std::vector<ast*>& out) override {
        // organize struct or simply pass.
        std::vector<ast*> _struc;
        std::vector<ast*>& ls = m_createfunc ? _struc : out;

        for (parser* p : m_components) {
            p->read(lexer, ls);
        }
        if (m_createfunc) {
            // create AST.
            ast* r = m_createfunc(ls);
            out.push_back(r);
        }
    }

    bool match(lexer* lex) override {
        // empty parserls should be pass.
        // case: ornull.  pass().and(sth).or(suffix1, suffix2, pass() /*empty, no suffix.*/)
        if (m_components.empty())
            return true;
        // as lookahead-until does not needed, just test the first one.
        if (!m_use_lookahead)
            return m_components.at(0)->match(lex);

        // lookahead until
        int mark = lex->m_index;
        bool pass = true;
        std::vector<ast*> tmpls;
        for (parser* p : m_components) {
            if (p == parser_lookahead_tag::instance())
                break;
            try {
                p->read(lex, tmpls);
            } catch (std::runtime_error& ex) {
                pass = false;
                break;
            }
        }
        lex->m_index = mark;
        return pass;
    }

    parserls* andp(parser* p) {
        m_components.push_back(p);
        return this;
    }


    parserls* number() {
        auto* p = new parser_token();
        p->validator = [](token* t) -> const char* {
            if (!t->isNumber())
                return "Required Number Type.";
            return nullptr;
        };
        return andp(p);
    }
    parserls* string() {
        auto* p = new parser_token();
        p->validator = [](token* t) -> const char* {
            if (!t->isString())
                return "Required String Type.";
            return nullptr;
        };
        return andp(p);
    }
    parserls* name() {
        auto* p = new parser_token();
        p->validator = [](token* t) -> const char* {
            if (!t->isName())
                return "Required Name Type.";
            return nullptr;
        };
        return andp(p);
    }

    parserls* id(const std::string& id) {
        auto* p = new parser_token();
        p->validator = [id](token* t) -> const char* {
            if (!t->isIdentifier())
                return "Required Identifier Type.";
            if (t->m_text != id)
                return "Bad id. not as expected.";
            return nullptr;
        };
        p->createfunc = nullptr;  // Do not needs ast-result.
        return andp(p);
    }
    parserls* iden(const vector<std::string>& ids) {
        auto* p = new parser_token();
        p->validator = [ids](token* t) -> const char* {
            if (!t->isIdentifier())
                return "Required Identifier Type.";
            if (find(ids.begin(), ids.end(), t->m_text) == ids.end())
                return "Bad id. not as expects.";
            return nullptr;
        };
        return andp(p);
    }
    parserls* iden(std::initializer_list<std::string> l) {
        return iden(std::vector<std::string>(l));
    }




    parserls* or_p(const std::vector<parser*>& v) {
        auto* p = new parser_or(v);
        return andp(p);
    }

    parserls* or_p(const std::initializer_list<parser*>& ls) {
        return or_p(std::vector<parser*>(ls));
    }


    parserls* mark_lookahead() {
        m_use_lookahead = true;
        return andp(parser_lookahead_tag::instance());
    }

    parserls* repeat(parser* parser) {
        auto* p = new parser_repeat();
        p->m_parser = parser;
        return andp(p);
    }
    parserls* op(parser* parser) {
        auto* p = new parser_repeat();
        p->m_parser = parser;
        p->m_max_one = true;
        return andp(p);
    }



    parserls* composer(const function<void(std::vector<ast*>&)>& compfunc) {
        auto* p = new parser_composer();

        p->m_composer_func = compfunc;

        return andp(p);
    }
    // compose stack tops
    template<typename T>
    parserls* composesp(int n) {
        return composer([n](std::vector<ast*>& ls){
            vector<ast*> l;
            l.reserve(n);

            // move.
            l.insert(l.begin(), ls.end()-n, ls.end());
            ls.erase(ls.end()-n, ls.end());

            ast* r = new T(l);
            ls.push_back(r);
        });
    }



    parserls* _expr_bi_lr(parser* factor, std::initializer_list<std::string> oprs) {
        return andp(factor)->repeat(pass()->iden(oprs)->andp(factor)->composesp<ast_expr>(3));
    }





};

parserls* pass() {
    return new parserls();
}

template<typename T>
parserls* struc() {
    auto* p = new parserls();
    p->m_createfunc = [](const vector<ast*>& ls) -> ast* {
        return new T(ls);
    };
    return p;
}

#endif //LANGDEV_PARSERLS_H
