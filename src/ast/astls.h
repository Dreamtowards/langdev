//
// Created by Dreamtowards on 2021/7/2.
//

#ifndef LANGDEV_ASTLS_H
#define LANGDEV_ASTLS_H

#include "ast.h"

class astls : public ast {

public:
    std::vector<ast*> m_ls;

    explicit astls(const std::vector<ast*>& ls) : m_ls(ls) {}

    std::string to_string() override {
        std::stringstream ss;
        ss << "[";
        bool fs = true;
        for (ast* e : m_ls) {
            if (fs) fs = false;
            else    ss << ", ";

            ss << e->to_string();
        }
        ss << "]";
        return ss.str();
    }
};

#endif //LANGDEV_ASTLS_H
