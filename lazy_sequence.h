#ifndef LAZY_SEQUENCE_HPP
#define LAZY_SEQUENCE_HPP

#include "Sequance.hpp"
#include "Dynamic_array.hpp"
#include "Error.hpp"
#include <functional>

template <typename T>
class LazySequence : public Sequence<T> {
private:
    std::function<T(int)> generator;
    int length;
    mutable Dynamic_array<T> cache;  // хранит уже вычисленные элементы

public:
    LazySequence(std::function<T(int)> func, int len)
        : generator(std::move(func)), length(len), cache() {}

    ~LazySequence() override = default;

    T GetFirst() const override {
        if (length == 0) throw IndexOutOfRange();
        return Get(0);
    }

    T GetLast() const override {
        if (length == 0) throw IndexOutOfRange();
        return Get(length - 1);
    }

    T Get(int index) const override {
        if (index < 0 || index >= length)
            throw IndexOutOfRange();

        // ленивое вычисление
        while (cache.size() <= index) {
            cache.push_back(generator(cache.size()));
        }
        return cache[index];
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
            throw IndexOutOfRange();

        auto subFunc = [this, startIndex](int i) {
            return this->Get(startIndex + i);
        };
        return new LazySequence<T>(subFunc, endIndex - startIndex + 1);
    }

    int GetLength() const override {
        return length;
    }

    Sequence<T>* Append(T) override { return nullptr; } // неактуально для lazy
    Sequence<T>* Prepend(T) override { return nullptr; }
    Sequence<T>* InsertAt(T, int) override { return nullptr; }
    Sequence<T>* Concat(Sequence<T>*) override { return nullptr; }
    Sequence<T>* AppendImmut(T) override { return nullptr; }

    T& operator[](int index) override {
        static T tmp = Get(index);
        return tmp;
    }

    const T& operator[](int index) const override {
        static T tmp = Get(index);
        return tmp;
    }
};

#endif // LAZY_SEQUENCE_HPP
