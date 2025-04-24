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
    ArraySequence() : array(new DynamicArray<T>()) {}
    ArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}
    ArraySequence(const ArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}
    ~ArraySequence() override { delete array; }
    T GetFirst() const override {
        if (array->GetSize() == 0)
            throw IndexOutOfRange;
        return array->Get(0);
    }
    T GetLast() const override {
        if (array->GetSize() == 0)
            throw IndexOutOfRange;
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) const override {
        if (index < 0 || index >= array->GetSize())
            throw IndexOutOfRange;
        return array->Get(index);
    }

    Sequence<T>* GetSubsequence(int start, int end) const override {
        if (start < 0 || end >= array->GetSize() || start > end)
            throw IndexOutOfRange;
        T* subArray = new T[end - start + 1];
        for (int i = start; i <= end; ++i) subArray[i - start] = array->Get(i);
        return new ArraySequence<T>(subArray, end - start + 1);
    }
    int GetLength() const override { return array->GetSize(); }
    Sequence<T>* Append(T item) override {
        DynamicArray<T>* newArray = new DynamicArray<T>(*array);
        newArray->Resize(newArray->GetSize() + 1);
        newArray->Set(newArray->GetSize() - 1, item);
        return new ArraySequence<T>(*newArray);
    }

    Sequence<T>* Prepend(T item) override {
        DynamicArray<T>* newArray = new DynamicArray<T>(array->GetSize() + 1);
        newArray->Set(0, item);
        for (int i = 0; i < array->GetSize(); ++i) newArray->Set(i + 1, array->Get(i));
        return new ArraySequence<T>(*newArray);
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if (index < 0 || index > array->GetSize())
            throw IndexOutOfRange;
        DynamicArray<T>* newArray = new DynamicArray<T>(array->GetSize() + 1);
        return new ArraySequence<T>(*newArray);
    }

    Sequence<T>* Concat(Sequence<T>* other) override {
        ArraySequence<T>* result = new ArraySequence<T>(*this);
        for (int i = 0; i < other->GetLength(); ++i)
            result->Append(other->Get(i));
        return result;
    }
    T& operator[](int index) override { return (*array)[index]; }
    const T& operator[](int index) const override { return (*array)[index]; }
};
#endif //ARRAYSEQUENCE_HPP
