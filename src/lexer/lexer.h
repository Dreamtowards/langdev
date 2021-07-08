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


class lexer {

public:
    int m_index;
    std::vector<token*> m_tokens;

    ~lexer() {
        std::cout << "Deconstruct lexer" << std::endl;
    }

    void read(const std::string& s) {
        int len = s.length();
        int idx = 0;
        while (skip_blanks(s, idx) < len) {
            char ch = s.at(idx);
            std::string text;
            int type;
            if (_curris("//",s,idx)) {          // COMMENT line
                int end = s.find('\n', idx);
                idx = end == -1 ? len : end;
                continue;
            } else if (_curris("/*",s,idx)) {   // COMMENT block
                idx = s.find("*/",idx) +2;
                continue;
            } else if (is_number(ch)) {                // NUMBER
                text = read_number(s, idx);
                type = token::TYPE_NUMBER;
            } else if (ch == '"' || ch == '\'') {      // STRING
                text = read_quote(s, idx);
                type = token::TYPE_STRING;
            } else if (is_name_char(ch, true)) {   // NAME
                text = read_name(s, idx);
                type = token::TYPE_NAME;
            } else if (is_border_char(ch)) {           // BORDER
                text = read_border(s, idx);
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
            std::cout <<"TOKEN["<<t->m_type<<"]: "<< t->m_text << std::endl;
        }
    }

private:

    static int skip_blanks(const std::string& s, int& idx) {
        while (idx < s.length()) {
            if (s.at(idx) > ' ')
                break;
            (idx)++;
        }
        return idx;
    }

    static bool is_number(char ch) {
        return ch >= '0' && ch <= '9';
    }
    static std::string read_number(const std::string& s, int& idx) {
        bool haspoint = false;
        int start = idx;
        while (idx < s.length()) {
            char ch = s.at(idx);
            if (ch == '.' && !haspoint) {
                haspoint = true;
            } else if (!is_number(ch)) {
                break;
            }
            idx++;
        }
        return s.substr(start, idx-start);
    }

    static std::string read_quote(const std::string& s, int& idx) {
        char quote = s.at(idx);
        idx++;
        std::stringstream ss;
        while (idx < s.length()) {
            char ch = s.at(idx);
            if (ch == quote) {
                idx++;
                break;
            } else if (ch == '\\') {
                char ch1 = s.at(idx+1);
                if (ch1 == '\\')      ss << '\\';
                else if (ch1 == '\'') ss << '\'';
                else if (ch1 == '"')  ss << '"';
                else if (ch1 == 'n')  ss << '\n';
                idx += 2;
            } else {
                ss << ch;
                idx++;
            }
        }
        return ss.str();
    }

    static bool is_name_char(char ch, bool first) {
        if (!first && is_number(ch))
            return true;
        return (ch >= 'a' && ch <= 'z') ||
               (ch >= 'A' && ch <= 'Z') ||
               ch == '_';
    }
    static std::string read_name(const std::string& s, int& idx) {
        int start = idx;
        while (idx < s.length()) {
            char ch = s.at(idx);
            if (!is_name_char(ch, idx == start)) {
                break;
            }
            idx++;
        }
        return s.substr(start, idx-start);
    }

    static bool is_border_char(char ch) {
        return (ch >= '!' && ch <= '/') ||
               (ch >= ':' && ch <= '@') ||
               (ch >= '[' && ch <= '`') ||
               (ch >= '(' && ch <= '~');
    }
    static std::string read_border(const std::string& s, int& idx) {
        int i = idx;
        char ch = s.at(i);
        // Bad!
        if (_curris(">>>",s,i)) {
            idx += 3;
            return s.substr(i, 3);
        }
        if (_curris("++",s,i) || _curris("--",s,i) ||
            _curris("&&",s,i) || _curris("||",s,i) ||
            _curris("<<",s,i) || _curris(">>",s,i) ||
            _curris("<=",s,i) || _curris(">=",s,i) ||
            _curris("==",s,i) || _curris("!=",s,i)) {
            idx += 2;
            return s.substr(i, 2);
        } else if (is_border_char(ch)) {
            idx++;
            return s.substr(i, 1);
        } else {
            throw std::runtime_error("illegal border");
        }
    }

    static inline bool _curris(const std::string& search, const std::string& s, int idx) {
        return s.find(search, idx) == idx;
    }
};


#endif //LANGDEV_LEXER_H
