cmake_minimum_required(VERSION 3.17)
project(langdev)

set(CMAKE_CXX_STANDARD 14)

add_executable(langdev src/main.cpp src/lexer/lexer.h src/lexer/token.h src/util/util.h src/lexer/lexer.cpp src/ast/ast.h src/ast/ast_token.h src/parser/parser.h src/parser/parserls.h src/parser/parser_token.h src/parser/parser_or.h src/parser/parser_lookahead_tag.h src/parser/parser_expr.h src/ast/ast_expr.h)