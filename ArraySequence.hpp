//
// Created by islam on 24.04.2025.
//

#ifndef ARRAYSEQUENCE_HPP
#define ARRAYSEQUENCE_HPP
#include "Dynamic_array.hpp"
#include "Sequance.hpp"
#include "Error.hpp"
template <typename T>
class ArraySequence : public Sequence<T> {
private:
    Dynamic_array<T>* array;
public:
    ArraySequence() : array(new Dynamic_array<T>()) {}
    ArraySequence(T* items, int count) : array(new Dynamic_array<T>(items, count)) {}
    ArraySequence(const ArraySequence<T>& other) : array(new Dynamic_array<T>(*other.array)) {}
    ~ArraySequence() override { delete array; }
    T GetFirst() const override {
        if (array->GetSize() == 0)
            throw IndexOutOfRange();
        return array->Get(0);
    }
    T GetLast() const override {
        if (array->GetSize() == 0)
            throw IndexOutOfRange();
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) const override {
        if (index < 0 || index >= array->GetSize())
            throw IndexOutOfRange();
        return array->Get(index);
    }

    Sequence<T>* GetSubsequence(int start, int end) const override {
        if (start < 0 || end >= array->GetSize() || start > end)
            throw IndexOutOfRange();
        T* subArray = new T[end - start + 1];
        for (int i = start; i <= end; ++i) subArray[i - start] = array->Get(i);
        return new ArraySequence<T>(subArray, end - start + 1);
    }
    int GetLength() const override { return array->GetSize(); }
    Sequence<T>* Append(T item) override {
        array->push_back(item);
    }

    Sequence<T>* Prepend(T item) override {
        Dynamic_array<T> minor;
        minor.push_back(item);
        for (int i = 0; i < array->size(); i++)
        {
            minor.push_back(array[i]);
        }
        array = minor;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        array->Set(index,item);
    }

    Sequence<T>* Concat(Sequence<T>* other) override {
        for (int i = 0; i < other->GetLength(); i++)
        {
            array->push_back(other->Get(i));
        }
    }
    T& operator[](int index) override { return (*array)[index]; }
    const T& operator[](int index) const override { return (*array)[index]; }
};
#endif //ARRAYSEQUENCE_HPP
