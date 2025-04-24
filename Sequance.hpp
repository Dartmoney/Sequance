//
// Created by islam on 24.04.2025.
//

#ifndef SEQUANCE_HPP
#define SEQUANCE_HPP
#include <functional>
#include <stdexcept>

template <typename T>
class Sequence {
public:
    virtual ~Sequence() = default;

    // Декомпозиция
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;

    // Операции
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) = 0;

    // Map-Reduce
    template <typename U>
    Sequence<U>* Map(std::function<U(T)> func) const;

    template <typename U>
    U Reduce(std::function<U(U, T)> func, U initial) const;

    // Перегрузка оператора []
    virtual T& operator[](int index) = 0;
    virtual const T& operator[](int index) const = 0;
};
#endif //SEQUANCE_HPP
