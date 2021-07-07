//
// Created by Dreamtowards on 2021/4/29.
//

#ifndef LANGDEV_LEXER_H
#define LANGDEV_LEXER_H

#include <string>
#include <vector>
#include <iostream>

#include <sstream>

#include "token.h"

using namespace std;


class lexer {

public:
    int m_index;
    vector<token*> m_tokens;

    ~lexer() {
        std::cout << "Deconstruct lexer" << std::endl;
    }

    void read(const std::string& s) {
        int len = s.length();
        int idx = 0;
        while (skipBlanks(s, &idx) < len) {
            char ch = s.at(idx);
            string text;
            int type;
            if (_curris("//",s,idx)) {         // COMMENT line
                int end = s.find('\n', idx);
                idx = end == -1 ? len : end;
                continue;
            } else if (_curris("/*",s,idx)) {  // COMMENT block
                idx = s.find("*/",idx) +2;
                continue;
            } else if (isNumber(ch)) {                // NUMBER
                text = readNumber(s, &idx);
                type = token::TYPE_NUMBER;
            } else if (ch == '"' || ch == '\'') {     // STRING
                text = readQuote(s, &idx);
                type = token::TYPE_STRING;
            } else if (isName(ch, true)) {      // NAME
                text = readName(s, &idx);
                type = token::TYPE_NAME;
            } else if (isBorder(ch)) {               // BORDER
                text = readBorder(s, &idx);
                type = token::TYPE_BORDER;
            } else {
                throw std::runtime_error("Unsupported token format.");
            }

            m_tokens.push_back(new token(text, type));
        }
    }

    token* next() {
        return m_tokens.at(m_index++);
    }

    token* peek() {
        if (m_index == m_tokens.size())
            return nullptr;
        return m_tokens.at(m_index);
    }

    void dbg_print_tokens() {
        for (const token* t : m_tokens) {
            cout <<"TOKEN["<<t->m_type<<"]: "<< t->m_text << endl;
        }
    }

private:


    static int skipBlanks(string s, int* idx) {
        while (*idx < s.length()) {
            if (s.at(*idx) > ' ')
                break;
            (*idx)++;
        }
        return *idx;
    }

    static bool isNumber(char ch) {
        return ch >= '0' && ch <= '9';
    }
    static string readNumber(string s, int* idx) {
        bool haspoint = false;
        int start = *idx;
        while (*idx < s.length()) {
            char ch = s.at(*idx);
            if (ch == '.' && !haspoint) {
                haspoint = true;
            } else if (!isNumber(ch)) {
                break;
            }
            (*idx)++;
        }
        return s.substr(start, *idx-start);
    }

    static string readQuote(string s, int* idx) {
        char quote = s.at(*idx);
        (*idx)++;
        std::stringstream ss;
        while (*idx < s.length()) {
            char ch = s.at(*idx);
            if (ch == quote) {
                (*idx)++;
                break;
            } else if (ch == '\\') {
                char ch1 = s.at(*idx+1);
                if (ch1 == '\\')      ss << '\\';
                else if (ch1 == '\'') ss << '\'';
                else if (ch1 == '"')  ss << '"';
                else if (ch1 == 'n')  ss << '\n';
                (*idx) += 2;
            } else {
                ss << ch;
                (*idx)++;
            }
        }
        return ss.str();
    }

    static bool isName(char ch, bool first) {
        if (!first && isNumber(ch))
            return true;
        return (ch >= 'a' && ch <= 'z') ||
               (ch >= 'A' && ch <= 'Z') ||
               ch == '_';
    }
    static string readName(string s, int* idx) {
        int start = *idx;
        while (*idx < s.length()) {
            char ch = s.at(*idx);
            if (!isName(ch, *idx == start)) {
                break;
            }
            (*idx)++;
        }
        return s.substr(start, *idx-start);
    }

    static bool isBorder(char ch) {
        return (ch >= '!' && ch <= '/') ||
               (ch >= ':' && ch <= '@') ||
               (ch >= '[' && ch <= '`') ||
               (ch >= '(' && ch <= '~');
    }
    static inline bool _curris(const string& search, const string& s, int idx) {
        return s.find(search, idx) == idx;
    }

    static std::string readBorder(std::string s, int* idx) {
        int i = *idx;
        char ch = s.at(i);
        // Bad!
        if (_curris(">>>",s,i)) {
            (*idx) += 2;
            return s.substr(i, 3);
        }
        if (_curris("++",s,i) || _curris("--",s,i) ||
            _curris("&&",s,i) || _curris("||",s,i) ||
            _curris("<<",s,i) || _curris(">>",s,i) ||
            _curris("<=",s,i) || _curris(">=",s,i) ||
            _curris("==",s,i) || _curris("!=",s,i)) {
            (*idx) += 2;
            return s.substr(i, 2);
        } else if (isBorder(ch)) {
            (*idx)++;
            return s.substr(i, 1);
        } else {
            throw_with_nested("illegal border");
        }
    }

};


#endif //LANGDEV_LEXER_H
