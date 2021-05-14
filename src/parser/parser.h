//
// Created by Dreamtowards on 2021/5/1.
//

#ifndef LANGDEV_PARSER_H
#define LANGDEV_PARSER_H

#include <vector>

#include "../lexer/lexer.h"
#include "../ast/ast.h"

using namespace std;

class parser {

public:

    virtual vector<ast*> read(lexer* lex) = 0;

    /**
     * directly pass the only-one result out.
     * used in e.g. parserls non-ast-createfunc directly pass and parser_expr pass factor-pass/expr-ast.
     */
    ast* readone(lexer* lex) {
        vector<ast*> ls = read(lex);
        assert(ls.size() == 1);
        return ls.at(0);
    }

    /**
     * After call of match(), the lexer-index should as same as before the call.
     */
    virtual bool match(lexer* lex) = 0;

};

#endif //LANGDEV_PARSER_H
