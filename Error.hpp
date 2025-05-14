//
// Created by islam on 24.04.2025.
//

#ifndef LABA_2_ERROR_HPP
#define LABA_2_ERROR_HPP
#include <stdexcept>

class IndexOutOfRange : public std::exception {
public:
    const char* what() const noexcept override {
        return "Index is out of range!";
    }
};

#endif //LABA_2_ERROR_HPP
