//
// Created by Dreamtowards on 2021/4/29.
//

#ifndef LANGDEV_UTIL_H
#define LANGDEV_UTIL_H

#include <string>
#include <sstream>

class util {

public:
    static std::string to_string(std::istream& in) {
        std::stringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

//    Deprecated.
//    template<typename T>
//    static std::vector<T> aslist(int num, ...) {
//        va_list va_ls;
//        va_start(va_ls, num);
//
//        std::vector<T> v;
//        for (int i = 0;i < num;i++) {
//            v.push_back(va_arg(va_ls, T));
//        }
//
//        va_end(va_ls);
//
//        return v;
//    }
};


#endif //LANGDEV_UTIL_H
