#include <iostream>
#include <fstream>

#include "lexer/lexer.h"
#include "util/ioutil.h"
#include "parser/parserls.h"

using namespace std;

int main() {

    ifstream fs("../main.g");
    string s = ioutil::toString(fs);

    auto* lex = new lexer();
    lex->read(s);

    parserls p_number_literal;     p_number_literal.c_number();
    parserls p_string_literal;     p_string_literal.c_string();
    parserls p_variable_reference; p_variable_reference.c_name();

//    parserls p_primary;
//    p_primary.c_or();

//    parserls p_primary_neg_factor;
//    p_primary_neg_number.comp_id("-");
//    p_primary_neg_number.comp_number();


    vector<ast*> rs = p_number_literal.read(lex);
    for (ast* ast : rs) {
        cout << "AST: " << ast->to_string() << endl;
    }

//    delete lex;

    return 0;
}
