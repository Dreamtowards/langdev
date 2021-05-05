//
// Created by Dreamtowards on 2021/4/30.
//

#include <string>
#include <vector>
#include <sstream>

#include "token.h"
#include "lexer.h"

using namespace std;


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
static string readBorder(string s, int* idx) {
    int i = *idx;
    char ch = s.at(i);
    if (_curris("||",s,i) || _curris("&&",s,i) ||
        _curris("==",s,i) || _curris("!=",s,i) ||
        _curris("<=",s,i) || _curris(">=",s,i) ||
        _curris("<<",s,i) || _curris(">>",s,i)) {
        (*idx) += 2;
        return s.substr(i, 2);
    } else if (isBorder(ch)) {
        (*idx)++;
        return s.substr(i, 1);
    } else {
        throw_with_nested("illegal border");
    }
}


void lexer::read(string s) {
    int idx = 0;
    while (skipBlanks(s, &idx) < s.length()) {
        char ch = s.at(idx);
        string text;
        int type;
        if (_curris("//",s,idx)) {         // COMMENT line
            int end = s.find('\n', idx);
            idx = end == -1 ? s.length() : end;
            continue;
        } else if (_curris("/*",s,idx)) {  // COMMENT block
            idx = s.find("*/",idx) +2;
            continue;
        } else if (isNumber(ch)) {                // NUMBER
            text = readNumber(s, &idx);
            type = token::TOKEN_NUMBER;
        } else if (ch == '"' || ch == '\'') {     // STRING
            text = readQuote(s, &idx);
            type = token::TOKEN_STRING;
        } else if (isName(ch, true)) {      // NAME
            text = readName(s, &idx);
            type = token::TOKEN_IDENTIFIER;
        } else if (isBorder(ch)) {               // BORDER
            text = readBorder(s, &idx);
            type = token::TOKEN_IDENTIFIER;
        } else {
            throw std::runtime_error("Unsupported token format.");
        }

        m_tokens.emplace_back(text, type);
    }
}