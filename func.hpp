//
// Created by islam on 21.06.2025.
//

#ifndef LABA3_FUNC_HPP
#define LABA3_FUNC_HPP
#pragma once
#include <iostream>

inline int inc1(int x) { return x + 1; }
inline int inc2(int x) { return x + 2; }
inline int inc3(int x) { return x + 3; }


struct FuncWrapper {
    int (*f)(int);
    int id;

    FuncWrapper() : f(nullptr), id(0) {}
    FuncWrapper(int (*func)(int), int identifier)
            : f(func), id(identifier) {}

    bool operator<(const FuncWrapper& o) const { return id < o.id; }
    bool operator==(const FuncWrapper& o) const { return id == o.id; }

    int apply(int x) const { return f ? f(x) : 0; }

    bool operator>(const FuncWrapper& o) const {
        return o < *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const FuncWrapper& w) {
        return os << "Func#" << w.id;
    }
};
#endif //LABA3_FUNC_HPP
