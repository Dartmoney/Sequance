//
// Created by imako on 06.11.2025.
//

#ifndef LABA3_LAZY_TEST_H
#define LABA3_LAZY_TEST_H
#include <gtest/gtest.h>
#include "Dynamic_array.hpp"
#include "Error.hpp"
#include "lazy_sequence.h"
#include "Error.hpp"
#include "ReadOnlyStream.h"
#include "WriteOnlyStream.h"


static LazySequence<int> makeFiniteSeq(int n) {
    std::function<int(int)> gen = [](int i) {
        return i + 1;
    };
    return LazySequence<int>(gen, n);
}

// Бесконечная последовательность a[i] = 2*i  → [0,2,4,6,...]
// (если у тебя есть статический метод Infinite)
static LazySequence<int> makeInfiniteSeq() {
    std::function<int(int)> gen = [](int i) {
        return 2 * i;
    };
    return LazySequence<int>::Infinite(gen);
}

// ---------- ТЕСТЫ ДЛЯ КОНЕЧНОЙ ПОСЛЕДОВАТЕЛЬНОСТИ ----------

TEST(LazySequenceTest, GetFiniteBasic) {
    auto seq = makeFiniteSeq(5); // логически: [1,2,3,4,5]

    EXPECT_EQ(seq.GetLength(), 5);
    EXPECT_EQ(seq.GetFirst(), 1);
    EXPECT_EQ(seq.GetLast(), 5);

    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(4), 5);

    // оператор []
    EXPECT_EQ(seq[2], 3);
}

TEST(LazySequenceTest, GetFiniteOutOfRange) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    EXPECT_THROW(seq.Get(-1), IndexOutOfRange);
    EXPECT_THROW(seq.Get(3), IndexOutOfRange);
    EXPECT_THROW(seq[-1], IndexOutOfRange);
    EXPECT_THROW(seq[3], IndexOutOfRange);
}

TEST(LazySequenceTest, AppendFinite) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    seq.Append(10); // логически: [1,2,3,10]

    EXPECT_EQ(seq.GetLength(), 4);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
    EXPECT_EQ(seq.Get(3), 10);
    EXPECT_EQ(seq.GetLast(), 10);
}

TEST(LazySequenceTest, PrependFinite) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    seq.Prepend(100); // [100,1,2,3]

    EXPECT_EQ(seq.GetLength(), 4);
    EXPECT_EQ(seq.Get(0), 100);
    EXPECT_EQ(seq.Get(1), 1);
    EXPECT_EQ(seq.Get(2), 2);
    EXPECT_EQ(seq.Get(3), 3);
    EXPECT_EQ(seq.GetFirst(), 100);
}

TEST(LazySequenceTest, MultiplePrependAndAppend) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    seq.Prepend(100);        // [100,1,2,3]
    seq.Prepend(200);        // [200,100,1,2,3]
    seq.Append(10);          // [200,100,1,2,3,10]
    seq.Append(20);          // [200,100,1,2,3,10,20]

    EXPECT_EQ(seq.GetLength(), 7);
    EXPECT_EQ(seq.Get(0), 200);
    EXPECT_EQ(seq.Get(1), 100);
    EXPECT_EQ(seq.Get(2), 1);
    EXPECT_EQ(seq.Get(3), 2);
    EXPECT_EQ(seq.Get(4), 3);
    EXPECT_EQ(seq.Get(5), 10);
    EXPECT_EQ(seq.Get(6), 20);
}

TEST(LazySequenceTest, InsertAtMiddle) {
    auto seq = makeFiniteSeq(5); // [1,2,3,4,5]

    seq.InsertAt(100, 2); // [1,2,100,3,4,5]

    EXPECT_EQ(seq.GetLength(), 6);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 100);
    EXPECT_EQ(seq.Get(3), 3);
    EXPECT_EQ(seq.Get(4), 4);
    EXPECT_EQ(seq.Get(5), 5);
}

TEST(LazySequenceTest, InsertAtBeginning) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    seq.InsertAt(100, 0); // [100,1,2,3]

    EXPECT_EQ(seq.GetLength(), 4);
    EXPECT_EQ(seq.Get(0), 100);
    EXPECT_EQ(seq.Get(1), 1);
    EXPECT_EQ(seq.Get(2), 2);
    EXPECT_EQ(seq.Get(3), 3);
}

TEST(LazySequenceTest, InsertAtEnd) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    seq.InsertAt(100, 3); // [1,2,3,100]

    EXPECT_EQ(seq.GetLength(), 4);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
    EXPECT_EQ(seq.Get(3), 100);
}

TEST(LazySequenceTest, InsertAtOutOfRangeThrows) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    EXPECT_THROW(seq.InsertAt(100, -1), IndexOutOfRange);
    EXPECT_THROW(seq.InsertAt(100, 4), IndexOutOfRange);
}

// ---------- Subsequence ----------

TEST(LazySequenceTest, GetSubsequenceFinite) {
    auto seq = makeFiniteSeq(5); // [1,2,3,4,5]

    Sequence<int>* sub = seq.GetSubsequence(1, 3); // ожидаем [2,3,4]

    EXPECT_EQ(sub->GetLength(), 3);
    EXPECT_EQ(sub->Get(0), 2);
    EXPECT_EQ(sub->Get(1), 3);
    EXPECT_EQ(sub->Get(2), 4);

    delete sub;
}

TEST(LazySequenceTest, GetSubsequenceOutOfRange) {
    auto seq = makeFiniteSeq(5); // [1,2,3,4,5]

    EXPECT_THROW(seq.GetSubsequence(-1, 2), IndexOutOfRange);
    EXPECT_THROW(seq.GetSubsequence(2, 10), IndexOutOfRange);
    EXPECT_THROW(seq.GetSubsequence(3, 2), IndexOutOfRange); // start > end
}

// ---------- Concat / AppendImmut ----------

TEST(LazySequenceTest, ConcatFinite) {
    auto seq1 = makeFiniteSeq(3); // [1,2,3]
    auto seq2 = makeFiniteSeq(2); // [1,2]

    Sequence<int>* concat = seq1.Concat(&seq2); // [1,2,3,1,2]

    EXPECT_EQ(concat->GetLength(), 5);
    EXPECT_EQ(concat->Get(0), 1);
    EXPECT_EQ(concat->Get(1), 2);
    EXPECT_EQ(concat->Get(2), 3);
    EXPECT_EQ(concat->Get(3), 1);
    EXPECT_EQ(concat->Get(4), 2);

    delete concat;
}

TEST(LazySequenceTest, AppendImmutFinite) {
    auto seq = makeFiniteSeq(3); // [1,2,3]

    Sequence<int>* extended = seq.AppendImmut(10); // [1,2,3,10]

    EXPECT_EQ(extended->GetLength(), 4);
    EXPECT_EQ(extended->Get(0), 1);
    EXPECT_EQ(extended->Get(1), 2);
    EXPECT_EQ(extended->Get(2), 3);
    EXPECT_EQ(extended->Get(3), 10);

    // исходный seq не изменяется
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(2), 3);

    delete extended;
}

// ---------- Map / Reduce (для конечной) ----------

TEST(LazySequenceTest, MapFinite) {
    auto seq = makeFiniteSeq(4); // [1,2,3,4]

    auto mapped = dynamic_cast<LazySequence<int>*>(seq.Map<int>(
        [](int x){ return x * 10; }
    ));

    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped->GetLength(), 4);
    EXPECT_EQ(mapped->Get(0), 10);
    EXPECT_EQ(mapped->Get(1), 20);
    EXPECT_EQ(mapped->Get(2), 30);
    EXPECT_EQ(mapped->Get(3), 40);

    delete mapped;
}

TEST(LazySequenceTest, ReduceFinite) {
    auto seq = makeFiniteSeq(4); // [1,2,3,4]

    int sum = seq.Reduce<int>(
        [](int acc, int x){ return acc + x; },
        0
    );

    EXPECT_EQ(sum, 10); // 1+2+3+4
}

// ---------- БЕСКОНЕЧНАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ ----------

TEST(LazySequenceInfiniteTest, GetSomeElements) {
    auto seq = makeInfiniteSeq(); // [0,2,4,6,8,...]

    // GetLength должен кидать исключение
    EXPECT_THROW(seq.GetLength(), std::logic_error);

    EXPECT_EQ(seq.Get(0), 0);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 4);
    EXPECT_EQ(seq.Get(10), 20);
}

TEST(LazySequenceInfiniteTest, PrependInfinite) {
    auto seq = makeInfiniteSeq(); // [0,2,4,6,8,...]

    seq.Prepend(100); // [100,0,2,4,6,8,...]

    EXPECT_EQ(seq.Get(0), 100);
    EXPECT_EQ(seq.Get(1), 0);
    EXPECT_EQ(seq.Get(2), 2);
    EXPECT_EQ(seq.Get(3), 4);
}

TEST(LazySequenceInfiniteTest, ReduceInfiniteShouldThrow) {
    auto seq = makeInfiniteSeq();

    EXPECT_THROW(
        seq.Reduce<int>(
            [](int acc, int x){ return acc + x; },
            0
        ),
        std::logic_error
    );
}

TEST(LazySequenceInfiniteTest, AppendInfiniteNotAllowed) {
    auto seq = makeInfiniteSeq();

    EXPECT_THROW(seq.Append(10), std::logic_error);
    EXPECT_THROW(seq.AppendImmut(10), std::logic_error);
    EXPECT_THROW(seq.Concat(&seq), std::logic_error);
}

template<typename T>
class ArraySequenceMock : public Sequence<T> {
private:
    Dynamic_array<T> data;

public:
    ArraySequenceMock() = default;

    ArraySequenceMock(T* items, int count) {
        data.resize(count);
        for (int i = 0; i < count; ++i) {
            data[i] = items[i];
        }
    }

    ~ArraySequenceMock() override = default;

    T GetFirst() const override {
        if (data.size() == 0) throw IndexOutOfRange();
        return data[0];
    }

    T GetLast() const override {
        if (data.size() == 0) throw IndexOutOfRange();
        return data[data.size() - 1];
    }

    T Get(int index) const override {
        return data[index];
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < startIndex || endIndex >= data.size())
            throw IndexOutOfRange();
        auto* result = new ArraySequenceMock<T>();
        result->data.resize(endIndex - startIndex + 1);
        for (int i = 0; i <= endIndex - startIndex; ++i) {
            result->data[i] = data[startIndex + i];
        }
        return result;
    }

    int GetLength() const override {
        return data.size();
    }

    Sequence<T>* Append(T item) override {
        data.push_back(item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        Dynamic_array<T> tmp;
        tmp.resize(data.size() + 1);
        tmp[0] = item;
        for (int i = 0; i < data.size(); ++i)
            tmp[i + 1] = data[i];
        data = tmp;
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if (index < 0 || index > data.size())
            throw IndexOutOfRange();
        Dynamic_array<T> tmp;
        tmp.resize(data.size() + 1);
        for (int i = 0, j = 0; i < tmp.size(); ++i) {
            if (i == index) tmp[i] = item;
            else tmp[i] = data[j++];
        }
        data = tmp;
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* other) override {
        int total = data.size() + other->GetLength();
        Dynamic_array<T> tmp;
        tmp.resize(total);
        int k = 0;
        for (int i = 0; i < data.size(); ++i) tmp[k++] = data[i];
        for (int i = 0; i < other->GetLength(); ++i) tmp[k++] = other->Get(i);
        data = tmp;
        return this;
    }

    Sequence<T>* AppendImmut(T item) override {
        auto* res = new ArraySequenceMock<T>();
        res->data.resize(data.size() + 1);
        for (int i = 0; i < data.size(); ++i) res->data[i] = data[i];
        res->data[data.size()] = item;
        return res;
    }

    template<typename U>
    Sequence<U>* Map(std::function<U(T)> func) const {
        auto* res = new ArraySequenceMock<U>();
        res->data.resize(data.size());
        for (int i = 0; i < data.size(); ++i)
            res->data[i] = func(data[i]);
        return res;
    }

    template<typename U>
    U Reduce(std::function<U(U, T)> func, U initial) const {
        U acc = initial;
        for (int i = 0; i < data.size(); ++i)
            acc = func(acc, data[i]);
        return acc;
    }

    T& operator[](int index) override {
        return data[index];
    }

    const T& operator[](int index) const override {
        return data[index];
    }
};

// ----------------- ТЕСТЫ ДЛЯ ReadOnlyStream С SEQUENCE -----------------

TEST(ReadOnlyStreamSequenceTest, ReadSequentially) {
    int arr[] = {1, 2, 3, 4, 5};
    ArraySequenceMock<int> seq(arr, 5);

    ReadOnlyStream<int> stream(&seq);
    stream.Open();

    EXPECT_EQ(stream.IsEndOfStream(), false);
    EXPECT_EQ(stream.GetPosition(), 0u);

    EXPECT_EQ(stream.Read(), 1);
    EXPECT_EQ(stream.GetPosition(), 1u);

    EXPECT_EQ(stream.Read(), 2);
    EXPECT_EQ(stream.Read(), 3);
    EXPECT_EQ(stream.Read(), 4);
    EXPECT_EQ(stream.Read(), 5);
    EXPECT_EQ(stream.GetPosition(), 5u);

    EXPECT_THROW(stream.Read(), EndOfStream);
}

TEST(ReadOnlyStreamSequenceTest, SeekAndGoBack) {
    int arr[] = {10, 20, 30, 40};
    ArraySequenceMock<int> seq(arr, 4);

    ReadOnlyStream<int> stream(&seq);
    stream.Open();

    EXPECT_TRUE(stream.IsCanSeek());
    EXPECT_TRUE(stream.IsCanGoBack());

    // читаем первые два
    EXPECT_EQ(stream.Read(), 10);
    EXPECT_EQ(stream.Read(), 20);
    EXPECT_EQ(stream.GetPosition(), 2u);

    // прыгаем назад
    size_t newPos = stream.Seek(1);
    EXPECT_EQ(newPos, 1u);
    EXPECT_EQ(stream.GetPosition(), 1u);

    // снова читаем с 2-го элемента
    EXPECT_EQ(stream.Read(), 20);
    EXPECT_EQ(stream.Read(), 30);
    EXPECT_EQ(stream.Read(), 40);
    EXPECT_THROW(stream.Read(), EndOfStream);
}

// ----------------- ТЕСТЫ ДЛЯ WriteOnlyStream С SEQUENCE -----------------

TEST(WriteOnlyStreamSequenceTest, WriteToSequence) {
    ArraySequenceMock<int> seq;

    WriteOnlyStream<int> out(&seq);
    out.Open();

    EXPECT_EQ(out.GetPosition(), 0u);

    EXPECT_EQ(out.Write(100), 1u);
    EXPECT_EQ(out.Write(200), 2u);
    EXPECT_EQ(out.Write(300), 3u);

    out.Close();

    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(0), 100);
    EXPECT_EQ(seq.Get(1), 200);
    EXPECT_EQ(seq.Get(2), 300);
}

// ----------------- ТЕСТЫ ДЛЯ ReadOnlyStream С LazySequence -----------------

TEST(ReadOnlyStreamLazyTest, ReadFromLazyFinite) {
    // lazy: f(i) = i+1, length = 5 → [1,2,3,4,5]
    std::function<int(int)> gen = [](int i) { return i + 1; };
    LazySequence<int> lazy(gen, 5);

    ReadOnlyStream<int> stream(&lazy);
    stream.Open();

    EXPECT_FALSE(stream.IsEndOfStream());
    EXPECT_TRUE(stream.IsCanSeek()); // finite lazy

    EXPECT_EQ(stream.Read(), 1);
    EXPECT_EQ(stream.Read(), 2);
    EXPECT_EQ(stream.GetPosition(), 2u);

    size_t pos = stream.Seek(4);
    EXPECT_EQ(pos, 4u);
    EXPECT_EQ(stream.Read(), 5);
    EXPECT_THROW(stream.Read(), EndOfStream);
}

// ----------------- ТЕСТЫ ДЛЯ WriteOnlyStream С ФАЙЛОМ -----------------
// Если не хочешь возиться с файлами — этот блок можно закомментировать

TEST(WriteOnlyStreamFileTest, WriteIntsToFile) {
    // очень простой сериализатор: число -> строка
    Serializer<int> ser = [](const int& x) {
        return std::to_string(x);
    };

    const std::string filename = "test_output_stream.txt";

    {
        WriteOnlyStream<int> out(filename, ser);
        out.Open();
        out.Write(10);
        out.Write(20);
        out.Write(30);
        out.Close();
    }

    // Проверяем файл (не обязательно для зачёта, но полезно)
    std::ifstream in(filename);
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);
    EXPECT_EQ(line, "10");
    std::getline(in, line);
    EXPECT_EQ(line, "20");
    std::getline(in, line);
    EXPECT_EQ(line, "30");

    in.close();
}

int test(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif //LABA3_LAZY_TEST_H