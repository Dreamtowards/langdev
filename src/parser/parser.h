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

    virtual vector<ast*> read(lexer* lexer) = 0;

    virtual bool match(lexer* lexer) = 0;

};

#endif //LANGDEV_PARSER_H
