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
#include "Stream.h"
#include "BufferedCharEncoder.h"
#include "StreamStatistics.h"
static LazySequence<int> makeFiniteSeq(int n) {
    std::function<int(int)> gen = [](int i) {
        return i + 1;
    };
    return LazySequence<int>(gen, n);
}

static LazySequence<int> makeInfiniteSeq() {
    std::function<int(int)> gen = [](int i) {
        return 2 * i;
    };
    return LazySequence<int>::Infinite(gen);
}


TEST(LazySequenceTest, GetFiniteBasic) {
    auto seq = makeFiniteSeq(5);

    EXPECT_EQ(seq.GetLength(), 5);
    EXPECT_EQ(seq.GetFirst(), 1);
    EXPECT_EQ(seq.GetLast(), 5);

    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(4), 5);

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

    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(2), 3);

    delete extended;
}


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


TEST(LazySequenceInfiniteTest, GetSomeElements) {
    auto seq = makeInfiniteSeq(); // [0,2,4,6,8,...]

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
template <typename T>
class SimpleSequence : public Sequence<T> {
private:
    Dynamic_array<T> data;

public:
    SimpleSequence() = default;

    explicit SimpleSequence(const Dynamic_array<T>& arr) : data(arr) {}

    void PushBack(const T& value) {
        data.push_back(value);
    }

    // --- Реализация виртуальных методов ---

    T GetFirst() const override {
        if (GetLength() == 0) throw IndexOutOfRange();
        return data[0];
    }

    T GetLast() const override {
        int len = GetLength();
        if (len == 0) throw IndexOutOfRange();
        return data[len - 1];
    }

    T Get(int index) const override {
        return data[index];
    }

    Sequence<T>* GetSubsequence(int start, int end) const override {
        if (start < 0 || end < start || end >= GetLength())
            throw IndexOutOfRange();

        auto* result = new SimpleSequence<T>();
        for (int i = start; i <= end; ++i) {
            result->PushBack(data[i]);
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
        if (index < 0 || index > GetLength())
            throw IndexOutOfRange();

        Dynamic_array<T> tmp;
        tmp.resize(data.size() + 1);
        for (int i = 0, j = 0; i < tmp.size(); ++i) {
            if (i == index) {
                tmp[i] = item;
            } else {
                tmp[i] = data[j++];
            }
        }
        data = tmp;
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* other) override {
        int len = other->GetLength();
        for (int i = 0; i < len; ++i) {
            data.push_back(other->Get(i));
        }
        return this;
    }

    Sequence<T>* AppendImmut(T item) override {
        auto* copy = new SimpleSequence<T>(*this);
        copy->Append(item);
        return copy;
    }

    T& operator[](int index) override {
        return data[index];
    }

    const T& operator[](int index) const override {
        return data[index];
    }
};

// ======================= ТЕСТЫ ДЛЯ ReadOnlyStream =======================

TEST(ReadOnlyStreamTest, ReadFromSequenceBasic) {
    // Подготовим последовательность  {10, 20, 30}
    Dynamic_array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    auto* seq = new SimpleSequence<int>(arr);

    ReadOnlyStream<int> stream(seq);   // используется твой конструктор из Sequence*
    stream.Open();

    EXPECT_FALSE(stream.IsEndOfStream());
    EXPECT_EQ(stream.GetPosition(), 0u);

    int a = stream.Read();
    EXPECT_EQ(a, 10);
    EXPECT_EQ(stream.GetPosition(), 1u);
    EXPECT_FALSE(stream.IsEndOfStream());

    int b = stream.Read();
    EXPECT_EQ(b, 20);
    EXPECT_EQ(stream.GetPosition(), 2u);

    int c = stream.Read();
    EXPECT_EQ(c, 30);
    EXPECT_EQ(stream.GetPosition(), 3u);
    EXPECT_TRUE(stream.IsEndOfStream());

    // Попытка прочитать за концом должна кидать EndOfStream
    EXPECT_THROW(stream.Read(), EndOfStream);

    stream.Close();
    delete seq;   // ReadOnlyStream читает, но не владеет
}

TEST(ReadOnlyStreamTest, SeekInsideSequence) {
    Dynamic_array<int> arr;
    for (int i = 0; i < 5; ++i) arr.push_back(i * 10); // 0 10 20 30 40
    auto* seq = new SimpleSequence<int>(arr);

    ReadOnlyStream<int> stream(seq);
    stream.Open();

    ASSERT_TRUE(stream.IsCanSeek());

    // Перейдём сразу на позицию 2 (элемент 20)
    size_t pos = stream.Seek(2);
    EXPECT_EQ(pos, 2u);
    EXPECT_EQ(stream.GetPosition(), 2u);

    int v = stream.Read();  // должен быть 20
    EXPECT_EQ(v, 20);
    EXPECT_EQ(stream.GetPosition(), 3u);

    // Перейдём обратно на позицию 1
    if (stream.IsCanGoBack()) {
        size_t pos2 = stream.Seek(1);
        EXPECT_EQ(pos2, 1u);
        int v2 = stream.Read();   // должен быть 10
        EXPECT_EQ(v2, 10);
    }

    stream.Close();
    delete seq;
}

// ======================= ТЕСТЫ ДЛЯ WriteOnlyStream =======================

TEST(WriteOnlyStreamTest, WriteToSequenceBasic) {
    auto* seq = new SimpleSequence<int>();

    WriteOnlyStream<int> stream(seq);   // конструктор из Sequence*
    stream.Open();

    EXPECT_EQ(stream.GetPosition(), 0u);

    size_t p1 = stream.Write(5);
    EXPECT_EQ(p1, 1u);
    EXPECT_EQ(stream.GetPosition(), 1u);

    size_t p2 = stream.Write(10);
    EXPECT_EQ(p2, 2u);
    EXPECT_EQ(stream.GetPosition(), 2u);

    size_t p3 = stream.Write(15);
    EXPECT_EQ(p3, 3u);
    EXPECT_EQ(stream.GetPosition(), 3u);

    stream.Close();

    // Проверяем, что данные реально записались в последовательность
    EXPECT_EQ(seq->GetLength(), 3);
    EXPECT_EQ(seq->Get(0), 5);
    EXPECT_EQ(seq->Get(1), 10);
    EXPECT_EQ(seq->Get(2), 15);

    delete seq;
}


TEST(BufferedCharEncoderTests, EncodeSimpleString) {
    std::string input = "aaabbccccdd";
    std::string expected = "a3b2c4d2";

    StringReadOnlyStream in(input);
    StringWriteOnlyStream out;

    in.Open();
    out.Open();

    BufferedCharEncoder encoder(4);
    encoder.Encode(in, out);

    out.Close();
    in.Close();

    std::string encoded = out.GetResult();
    EXPECT_EQ(encoded, expected);
}


TEST(BufferedCharEncoderTests, EncodeSingleChar) {
    std::string input = "aaaaa";
    std::string expected = "a5";

    StringReadOnlyStream in(input);
    StringWriteOnlyStream out;

    in.Open();
    out.Open();

    BufferedCharEncoder encoder(2);
    encoder.Encode(in, out);

    out.Close();
    in.Close();

    EXPECT_EQ(out.GetResult(), expected);
}


TEST(BufferedCharEncoderTests, EncodeEmptyString) {
    std::string input;
    std::string expected;

    StringReadOnlyStream in(input);
    StringWriteOnlyStream out;

    in.Open();
    out.Open();

    BufferedCharEncoder encoder(8);
    encoder.Encode(in, out);

    out.Close();
    in.Close();

    EXPECT_EQ(out.GetResult(), expected);
}


TEST(BufferedCharEncoderTests, BufferBoundary) {
    std::string input = "aaaaa";
    std::string expected = "a5";

    StringReadOnlyStream in(input);
    StringWriteOnlyStream out;

    in.Open();
    out.Open();

    BufferedCharEncoder encoder(3);
    encoder.Encode(in, out);

    out.Close();
    in.Close();

    EXPECT_EQ(out.GetResult(), expected);
}

static int IntFromString(const std::string& s) {
    return std::stoi(s);
}

TEST(StringStreamStatisticsTest, EmptyString) {
    std::string data = "";
    StringStreamStatistics stats(data);

    stats.ConsumeAll();

    EXPECT_EQ(stats.GetCount(), 0);
    EXPECT_EQ(stats.GetSum(), 0);

    EXPECT_THROW(stats.GetMean(), std::logic_error);
    EXPECT_THROW(stats.GetMin(), std::logic_error);
    EXPECT_THROW(stats.GetMax(), std::logic_error);
}

TEST(StringStreamStatisticsTest, SingleChar) {
    std::string data = "A";
    StringStreamStatistics stats(data);

    stats.ConsumeAll();

    EXPECT_EQ(stats.GetCount(), 1);
    EXPECT_EQ(stats.GetSum(), 65);
    EXPECT_DOUBLE_EQ((double)stats.GetMean(), 65.0);
    EXPECT_EQ(stats.GetMin(), 'A');
    EXPECT_EQ(stats.GetMax(), 'A');
}

TEST(StringStreamStatisticsTest, SeveralChars) {
    std::string data = "abcde";
    StringStreamStatistics stats(data);

    stats.ConsumeAll();

    EXPECT_EQ(stats.GetCount(), 5);
    EXPECT_EQ(stats.GetSum(), 97 + 98 + 99 + 100 + 101);
    EXPECT_DOUBLE_EQ((double)stats.GetMean(), (97 + 98 + 99 + 100 + 101) / 5.0);
    EXPECT_EQ(stats.GetMin(), 'a');
    EXPECT_EQ(stats.GetMax(), 'e');
}

TEST(StringStreamStatisticsTest, ManualAddValue) {
    std::string dummy = "";
    StringStreamStatistics stats(dummy);

    stats.AddValue('b');
    stats.AddValue('A');
    stats.AddValue('z');

    EXPECT_EQ(stats.GetCount(), 3u);
    EXPECT_EQ(stats.GetMin(), 'A');
    EXPECT_EQ(stats.GetMax(), 'z');
}


int test(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif //LABA3_LAZY_TEST_H