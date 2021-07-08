cmake_minimum_required(VERSION 3.17)
project(langdev)

set(CMAKE_CXX_STANDARD 14)

add_executable(langdev src/main.cpp src/lexer/lexer.h src/lexer/token.h src/util/util.h src/ast/ast.h src/ast/ast_token.h src/parser/parser.h src/parser/parserls.h src/parser/parser_token.h src/parser/parser_or.h src/parser/parser_lookahead_tag.h src/ast/ast_expr_operbi.h src/parser/parser_repeat.h src/parser/parser_composer.h src/ast/ast_expr_funccall.h src/ast/astls.h src/ast/ast_expr_operupost.h src/ast/ast_expr_opertricon.h src/ast/ast_expr_operupre.h src/interpreter/runtime.h)

#add_executable(langdev src_c/main.c)