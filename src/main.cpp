#include <iostream>
#include <fstream>

#include "lexer/lexer.h"
#include "util/ioutil.h"
#include "parser/parserls.h"

using namespace std;


int main() {

    ifstream fs("../main.g");
    string s = ioutil::toString(fs);

    lexer *lex = new lexer();
    lex->read(s);

//    for (const token& t : lex->m_tokens) {
//        cout <<"TOKEN["<<t.m_type<<"]: "<< t.m_text << endl;
//    }

    parserls psr;
    psr.add_number();

    cout << "Comps: " << psr.m_components.size() << endl;

    vector<ast*> r = psr.read(lex);
    cout << "Reads: " << r.size() << endl;
    cout << r.at(0)->to_string() << endl;


//    delete lex;

    return 0;
}
