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

    auto* p_expr = pass();
    {
        auto* p_literal_number = pass()->c_number();
        auto* p_literal_string = pass()->c_string();
        auto* p_variable_reference = pass()->c_name();
        auto* p_function_call = pass()->c_name()->c_id("(")->c_id(")");

        auto* p_primary = pass()->c_or(3,
                                       p_literal_number,
                                       p_literal_string,
                                       p_variable_reference);

        auto* p_factor = pass();
        p_factor->c_or(3,
                       p_primary,
                       pass()->c_id("(")->add_component(p_expr)->c_id(")"),
                       pass()->c_id("-")->add_component(p_factor));

        p_expr->add_component(new parser_expr(p_factor));
    }

//lex->dbg_print_tokens();

    vector<ast*> rs = p_expr->read(lex);
    for (ast* ast : rs) {
        cout << "AST: " << ast->to_string() << endl;
    }

//    delete lex;

    return 0;
}
