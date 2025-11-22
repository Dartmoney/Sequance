#ifndef LAZY_SEQUENCE_HPP
#define LAZY_SEQUENCE_HPP

#include "Sequance.hpp"
#include "Dynamic_array.hpp"
#include "Error.hpp"
#include <functional>
#include <utility>
#include <stdexcept>

template <typename T>
class LazySequence : public Sequence<T> {
private:
    std::function<T(int)> generator;

    int baseLength;

    mutable Dynamic_array<T> cache;

    Dynamic_array<T> prepended;

    Dynamic_array<T> appended;

public:
    LazySequence(std::function<T(int)> func, int len)
        : generator(std::move(func)),
          baseLength(len),
          cache(),
          prepended(),
          appended()
    {
        if (len < 0) {
        }
    }

    static LazySequence<T> Infinite(std::function<T(int)> func) {
        LazySequence<T> seq(func, -1);
        return seq;
    }

    LazySequence(const LazySequence<T>& other)
        : generator(other.generator),
          baseLength(other.baseLength),
          cache(other.cache),
          prepended(other.prepended),
          appended(other.appended)
    {}

    ~LazySequence() override = default;

    int GetLength() const override {
        if (baseLength < 0) {
            throw std::logic_error("GetLength() is not defined for infinite LazySequence");
        }
        return prepended.size() + baseLength + appended.size();
    }

    int GetMaterializedBaseCount() const {
        return cache.size();
    }


    T GetFirst() const override {
        return Get(0);
    }

    T GetLast() const override {
        if (baseLength < 0) {
            throw std::logic_error("GetLast() is not defined for infinite LazySequence");
        }
        int len = GetLength();
        if (len == 0)
            throw IndexOutOfRange();
        return Get(len - 1);
    }

    T Get(int index) const override {
        if (index < 0) {
            throw IndexOutOfRange();
        }

        int prepSize = prepended.size();
        if (index < prepSize) {
            return prepended[index];
        }
        index -= prepSize;

        if (baseLength >= 0) {
            if (index < baseLength) {
                auto *self = const_cast<LazySequence<T>*>(this);
                while (self->cache.size() <= index) {
                    int i = self->cache.size();
                    self->cache.push_back(self->generator(i));
                }
                return self->cache[index];
            }

            index -= baseLength;
            if (index < 0 || index >= appended.size())
                throw IndexOutOfRange();
            return appended[index];
        } else {
            auto *self = const_cast<LazySequence<T>*>(this);
            while (self->cache.size() <= index) {
                int i = self->cache.size();
                self->cache.push_back(self->generator(i));
            }
            return self->cache[index];
        }
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < startIndex) {
            throw IndexOutOfRange();
        }

        if (baseLength >= 0) {
            if (endIndex >= GetLength())
                throw IndexOutOfRange();
        }

        auto self = this;
        auto subGen = [self, startIndex](int i) -> T {
            return self->Get(startIndex + i);
        };

        return new LazySequence<T>(subGen, endIndex - startIndex + 1);
    }


    Sequence<T>* Append(T item) override {
        if (baseLength < 0) {
            throw std::logic_error("Append() is not supported for infinite base LazySequence");
        }
        appended.push_back(item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        Dynamic_array<T> newPrep;
        newPrep.resize(prepended.size() + 1);
        newPrep[0] = item;
        for (int i = 0; i < prepended.size(); ++i)
            newPrep[i + 1] = prepended[i];
        prepended = newPrep;
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if (index < 0) {
            throw IndexOutOfRange();
        }

        int totalBefore;
        if (baseLength >= 0) {
            if (index > GetLength())
                throw IndexOutOfRange();
            totalBefore = GetLength();
        } else {
            totalBefore = std::max(index, prepended.size() + GetMaterializedBaseCount());
        }

        int logicalLen = (baseLength >= 0) ? GetLength()
                                           : (totalBefore + 1);
        Dynamic_array<T> tmp;
        tmp.resize(logicalLen + 1);

        for (int i = 0, j = 0; i < logicalLen + 1; ++i) {
            if (i == index) {
                tmp[i] = item;
            } else {
                tmp[i] = Get(j++);
            }
        }

        generator = [tmp](int i) -> T {
            return tmp[i];
        };
        baseLength = logicalLen + 1;
        cache = tmp;
        prepended.resize(0);
        appended.resize(0);

        return this;
    }

    Sequence<T>* Concat(Sequence<T>* other) override {
        if (baseLength < 0) {
            throw std::logic_error("Concat() is not supported for infinite base LazySequence");
        }

        int thisLen = GetLength();
        int otherLen = other->GetLength();
        auto self = this;

        auto concatGen = [self, other, thisLen](int i) -> T {
            if (i < thisLen)
                return self->Get(i);
            else
                return other->Get(i - thisLen);
        };

        return new LazySequence<T>(concatGen, thisLen + otherLen);
    }

    Sequence<T>* AppendImmut(T item) override {
        if (baseLength < 0) {
            throw std::logic_error("AppendImmut() is not supported for infinite base LazySequence");
        }

        int thisLen = GetLength();
        auto self = this;
        auto gen2 = [self, item, thisLen](int i) -> T {
            if (i < thisLen) return self->Get(i);
            if (i == thisLen) return item;
            throw IndexOutOfRange();
        };
        return new LazySequence<T>(gen2, thisLen + 1);
    }


    template <typename U>
    Sequence<U>* Map(std::function<U(T)> func) const {
        auto self = this;

        if (baseLength < 0) {
            auto mapGen = [self, func](int i) -> U {
                return func(self->Get(i));
            };
            return new LazySequence<U>(mapGen, -1);
        } else {
            auto mapGen = [self, func](int i) -> U {
                return func(self->Get(i));
            };
            return new LazySequence<U>(mapGen, this->GetLength());
        }
    }

    template <typename U>
    U Reduce(std::function<U(U, T)> func, U initial) const {
        if (baseLength < 0) {
            throw std::logic_error("Reduce() is not defined for infinite LazySequence without additional stopping condition");
        }
        U acc = initial;
        int len = GetLength();
        for (int i = 0; i < len; ++i)
            acc = func(acc, Get(i));
        return acc;
    }


    T& operator[](int index) override {
        if (index < 0) throw IndexOutOfRange();

        int prepSize = prepended.size();
        if (index < prepSize) {
            return prepended[index];
        }
        index -= prepSize;

        if (baseLength >= 0) {
            if (index < baseLength) {
                auto *self = const_cast<LazySequence<T>*>(this);
                while (self->cache.size() <= index) {
                    int i = self->cache.size();
                    self->cache.push_back(self->generator(i));
                }
                return self->cache[index];
            }
            index -= baseLength;
            if (index < 0 || index >= appended.size())
                throw IndexOutOfRange();
            return appended[index];
        } else {
            auto *self = const_cast<LazySequence<T>*>(this);
            while (self->cache.size() <= index) {
                int i = self->cache.size();
                self->cache.push_back(self->generator(i));
            }
            return self->cache[index];
        }
    }

    const T& operator[](int index) const override {
        return const_cast<LazySequence<T>*>(this)->operator[](index);
    }
};

#endif // LAZY_SEQUENCE_HPP
