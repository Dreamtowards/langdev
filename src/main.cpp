#include <iostream>
#include <fstream>

#include "lexer/lexer.h"
#include "util/util.h"
#include "parser/parserls.h"
#include "parser/parser_expr.h"

using namespace std;

int main() {

    ifstream fs("../main.g");
    string s = util::to_string(fs);

    auto* lex = new lexer();
    lex->read(s);

    operator_::init_operators();

    auto* expression = pass();
    {
        auto* p_literal_number = pass()->c_number();
        auto* p_literal_string = pass()->c_string();
        auto* p_variable_reference = pass()->c_name();
        auto* p_function_call = pass()->c_name()->c_id("(")->c_id(")");

        vector<parser*> l = util::aslist<parser*>(3,
                                                  p_literal_number,
                                                  p_literal_string,
                                                  p_variable_reference);
        auto* p_primary = pass()->c_or(l);

        auto* p_factor = pass();
        l = util::aslist<parser*>(3,
                                  p_primary,
                                  pass()->c_id("(")->add_component(expression)->c_id(")"),
                                  pass()->c_id("-")->add_component(p_factor));
        p_factor->c_or(l);

        expression->add_component(new parser_expr(p_factor));
    }


//    parserls p_primary_neg_factor;
//    p_primary_neg_number.comp_id("-");
//    p_primary_neg_number.comp_number();


    vector<ast*> rs = expression->read(lex);
    for (ast* ast : rs) {
        cout << "AST: " << ast->to_string() << endl;
    }

//    delete lex;

    return 0;
}
