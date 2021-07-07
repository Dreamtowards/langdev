//
// Created by Dreamtowards on 2021/5/1.
//

#ifndef LANGDEV_AST_H
#define LANGDEV_AST_H

class ast {

public:
    virtual std::string to_string() {
        return "base_ast";

    }

    virtual void* eval(scope* sc) {
        throw std::runtime_error("Failed eval: unsupported");
    }
};

#endif //LANGDEV_AST_H
