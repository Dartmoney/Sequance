//
// Created by islam on 24.04.2025.
//

#ifndef ARRAYSEQUENCE_HPP
#define ARRAYSEQUENCE_HPP
#include <initializer_list>
#include <memory>

#include "Dynamic_array.hpp"
#include "Sequance.hpp"
#include "Error.hpp"
template <typename T>
class ArraySequence : public Sequence<T> {
private:
    std::unique_ptr<Dynamic_array<T>> array;

    explicit ArraySequence(std::unique_ptr<Dynamic_array<T>> data) : array(std::move(data)) {}

public:
    ArraySequence() : array(std::make_unique<Dynamic_array<T>>()) {}
    ArraySequence(T* items, int count) : array(std::make_unique<Dynamic_array<T>>(items, count)) {}
    ArraySequence(std::initializer_list<T> init) : array(std::make_unique<Dynamic_array<T>>(static_cast<int>(init.size()))) {
        int index = 0;
        for (const auto& value : init) {
            array->Set(index++, value);
        }
    }
    ArraySequence(const ArraySequence<T>& other) : array(std::make_unique<Dynamic_array<T>>(*other.array)) {}
    ArraySequence(ArraySequence<T>&& other) noexcept = default;
    ArraySequence<T>& operator=(const ArraySequence<T>& other) {
        if (this == &other) {
            return *this;
        }
        array = std::make_unique<Dynamic_array<T>>(*other.array);
        return *this;
    }
    ArraySequence<T>& operator=(ArraySequence<T>&& other) noexcept = default;
    ~ArraySequence() override = default;
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

    Sequence<T>* GetSubsequence(int start, int end) const override {
        if (start < 0 || end >= array->size() || start > end)
            throw IndexOutOfRange();
        auto subArray = std::make_unique<Dynamic_array<T>>(end - start + 1);
        for (int i = start; i <= end; ++i) {
            subArray->Set(i - start, (*array)[i]);
        }
        return new ArraySequence<T>(std::move(subArray));
    }
    int GetLength() const override { return array->size(); }
    Sequence<T>* Append(T item) override {
        array->push_back(item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        auto newArray = std::make_unique<Dynamic_array<T>>(array->size() + 1);
        newArray->Set(0, item);
        for (int i = 0; i < array->size(); i++) {
            newArray->Set(i + 1, (*array)[i]);
        }
        array = std::move(newArray);
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if (index < 0 || index > array->size())
            throw IndexOutOfRange();
        array->resize(array->size() + 1);
        for (int i = array->size() - 1; i > index; --i) {
            (*array)[i] = (*array)[i - 1];
        }
        (*array)[index] = item;
        return this;
    }
    Sequence<T>* AppendImmut(T item) override{
        auto copy = std::make_unique<ArraySequence<T>>(*this);
        copy->Append(item);
        return copy.release();
    }

    Sequence<T>* Concat(Sequence<T>* other) override {
        for (int i = 0; i < other->GetLength(); i++)
        {
            array->push_back(other->Get(i));
        }
        return this;
    }
    T& operator[](int index) override { return (*array)[index]; }
    const T& operator[](int index) const override { return (*array)[index]; }
};
#endif //ARRAYSEQUENCE_HPP
