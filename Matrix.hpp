//
// Created by islam on 08.05.2025.
//

#ifndef UNTITLED4_MATRIX_HPP
#define UNTITLED4_MATRIX_HPP

#include <iostream>
#include "Sequance.hpp"
#include "Dynamic_array.hpp"
#include "Error.hpp"

using namespace std;

template<typename T>
class Matrix : public Sequence<T> {
private:
    Dynamic_array<T> *array;
    int size;

public:

    Matrix() : array(new Dynamic_array<T>()), size(0) {}

    explicit Matrix(int n) : array(new Dynamic_array<T>(n * n)), size(n) {}

    Matrix(T *items, int count, int n) : array(new Dynamic_array<T>(items, count, n * n)), size(n) {}


    Matrix(const Matrix &other)
            : array(new Dynamic_array<T>(*other.array)), size(other.size) {}


    ~Matrix() override { delete array; }


    void resize(int n) {
        size = n;
        array->resize(n * n);
    }


    T GetFirst() const override {
        if (array->size() == 0)
            throw IndexOutOfRange();
        return (*array)[0];
    }

    T GetLast() const override {
        if (array->size() == 0)
            throw IndexOutOfRange();
        return (*array)[array->size() - 1];
    }

    T Get(int index) const override {
        if (index < 0 || index >= array->size())
            throw IndexOutOfRange();
        return (*array)[index];
    }

    Sequence<T> *GetSubsequence(int start, int end) const override {
        if (start < 0 || end >= array->size() || start > end)
            throw IndexOutOfRange();
        int len = end - start + 1;
        T *subArr = new T[len];
        for (int i = 0; i < len; ++i)
            subArr[i] = (*array)[start + i];
        return new Matrix<T>(subArr, len, size);
    }

    int GetLength() const override {
        return array->size();
    }

    Sequence<T> *Append(T item) override {
        array->push_back(item);
        return this;
    }

    Sequence<T> *Prepend(T item) override {
        Dynamic_array<T> *newArr = new Dynamic_array<T>();
        newArr->push_back(item);
        for (int i = 0; i < array->size(); ++i)
            newArr->push_back((*array)[i]);
        delete array;
        array = newArr;
        return this;
    }

    Sequence<T> *InsertAt(T item, int index) override {
        if (index < 0 || index > array->size())
            throw IndexOutOfRange();
        array->Set(item, index);
        return this;
    }

    Sequence<T> *Concat(Sequence<T> *other) override {
        for (int i = 0; i < other->GetLength(); ++i)
            array->push_back((*other)[i]);
        return this;
    }

    Sequence<T> *AppendImmut(T item) override {
        Matrix<T> *copy = new Matrix<T>(*this);
        copy->Append(item);
        return copy;
    }

    T &operator[](int index) override {
        if (index < 0 || index >= array->size())
            throw IndexOutOfRange();
        return (*array)[index];
    }

    const T &operator[](int index) const override {
        if (index < 0 || index >= array->size())
            throw IndexOutOfRange();
        return (*array)[index];
    }
    Matrix& operator=(const Matrix& other) {
        if (this == &other)
            return *this;  // защита от самоприсваивания

        delete array;  // освобождаем старую память
        array = new Dynamic_array<T>(*other.array);  // глубокое копирование
        size = other.size;
        return *this;
    }
    // Операции над матрицами
    Matrix operator+(const Matrix &obj) const {
        if (obj.size != size)
            throw IndexOutOfRange();
        Matrix result(size);
        for (int i = 0; i < size * size; ++i) {
            result[i] = (*array)[i] + (*obj.array)[i];
        }
        return result;
    }

    Matrix operator*(T scalar) const {
        Matrix result(size);
        for (int i = 0; i < size * size; ++i)
        {
            result[i] = ((*array)[i] * scalar);
        }

        return result;
    }

    int norm() const {
        int maxi = 0;
        for (int row = 0; row < size; ++row) {
            int sum = 0;
            for (int col = 0; col < size; ++col)
                sum += (*array)[row * size + col];
            if (sum > maxi) maxi = sum;
        }
        return maxi;
    }

    void elementary(int from, int what, int scalar = 1, bool column = false) {
        if (from < 0 || from >= size || what < 0 || what >= size)
            throw IndexOutOfRange();
        if (column) {
            for (int i = 0; i < size; ++i) {
                int idx = i * size;
                (*array)[idx + from] += (*array)[idx + what] * scalar;
            }
        } else {
            int base = from * size;

            int add = what * size;
            for (int i = 0; i < size; ++i)
                (*array)[base + i] += (*array)[add + i] * scalar;
        }
    }
};


#endif //UNTITLED4_MATRIX_HPP
