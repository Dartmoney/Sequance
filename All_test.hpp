//
// Created by islam on 24.04.2025.
//

#ifndef LABA_2_ALL_TEST_HPP
#define LABA_2_ALL_TEST_HPP

#include <gtest/gtest.h>
#include "Linked_List.hpp"
#include "Dynamic_array.hpp"
#include "Matrix.hpp"
#include "Tree.hpp"
#include <vector>

class Dynamic_arrayTest : public testing::Test {
protected:
    Dynamic_arrayTest() {
        int s[5] = {1, 2, 3, 4, 5};
        string k[5] = {"peppe", "banana", "kaka", "poki", "doki"};
        for (int i = 0; i < 5; i++) {
            da1.push_back(s[i]);
            da2.push_back(k[i]);
        }


    }

    Dynamic_array<int> da0;
    Dynamic_array<int> da1;
    Dynamic_array<string> da2;
};

TEST_F(Dynamic_arrayTest, IndexOutOfRangeWork) {
    EXPECT_THROW(da0.Set(2, 1), IndexOutOfRange);
    EXPECT_THROW(da0[4], IndexOutOfRange);
    EXPECT_THROW(da0[-2], IndexOutOfRange);
}

TEST_F(Dynamic_arrayTest, Opwork) {
    EXPECT_EQ(da1[1], 2);
    EXPECT_EQ(da2[1], "banana");

}

TEST_F(Dynamic_arrayTest, SetWork) {
    da1.Set(1, 4);
    da2.Set(1, "yababadju");
    EXPECT_EQ(da1[1], 4);
    EXPECT_EQ(da2[1], "yababadju");
}

TEST_F(Dynamic_arrayTest, SizeWork) {
    EXPECT_EQ(da1.size(), 5);
    EXPECT_EQ(da2.size(), 5);
}

TEST_F(Dynamic_arrayTest, CopyWork) {
    Dynamic_array<int> da3(da1);
    EXPECT_EQ(da3[0], da1[0]);
    EXPECT_EQ(da3[1], da1[1]);
    EXPECT_EQ(da3[2], da1[2]);
}

class Linked_ListTest : public testing::Test {
protected:
    Linked_ListTest() {
        ls1.insertBegin(1);
        ls1.insertEnd(2);
        ls1.insertEnd(3);
        ls2.insertBegin("banan");
        ls2.insertEnd("perdaus");
        ls2.insertEnd("vonuchkin");
    }

    List<int> ls0;
    List<int> ls1;
    List<string> ls2;
};


TEST_F(Linked_ListTest, IndexOutOfRangeWork) {
    EXPECT_THROW(ls0.GetFirst(), IndexOutOfRange);
    EXPECT_THROW(ls0.Get(2), IndexOutOfRange);
    EXPECT_THROW(ls0.GetLast(), IndexOutOfRange);
}

TEST_F(Linked_ListTest, GetWork) {
    EXPECT_EQ(ls1.GetFirst(), 1);
    EXPECT_EQ(ls2.GetFirst(), "banan");
    EXPECT_EQ(ls1.Get(1), 2);
    EXPECT_EQ(ls2.Get(1), "perdaus");
    EXPECT_EQ(ls1.GetLast(), 3);
    EXPECT_EQ(ls2.GetLast(), "vonuchkin");
}

TEST_F(Linked_ListTest, ReturnFunWork) {
    EXPECT_EQ(ls1.isEmpty(), 0);
    EXPECT_EQ(ls0.isEmpty(), 1);
    EXPECT_EQ(ls1.GetLength(), 3);
    EXPECT_EQ(ls2.GetLength(), 3);
}

TEST_F(Linked_ListTest, VoidFuncWork) {
    ls1.insertEnd(10);
    ls2.insertEnd("GG");
    EXPECT_EQ(ls1.GetLast(), 10);
    EXPECT_EQ(ls2.GetLast(), "GG");
    ls1.insertBegin(80);
    ls2.insertBegin("SUPER");
    EXPECT_EQ(ls1.GetFirst(), 80);
    EXPECT_EQ(ls2.GetFirst(), "SUPER");
    ls1.InsertAt(100, 0);
    ls2.InsertAt("100", 0);
    EXPECT_EQ(ls1.GetFirst(), 100);
    EXPECT_EQ(ls2.GetFirst(), "100");
}


class MatrixTest : public testing::Test {
protected:
    MatrixTest() {
        m3.resize(5);
        m4.resize(5);
        for (int i = 0; i < 25; i++) {
            m3.InsertAt(i, i);
            m4.InsertAt(i, i);
        }
        m = Matrix<int>(3);
        for (int i = 0; i < 9; ++i) {
            m.InsertAt(i, i);
        }
        m2 = Matrix<int>(3);

        for (int i = 0; i < 9; ++i) {
            m2.InsertAt(5, i);
        }
    }
    Matrix<int> m;
    Matrix<int> m2;
    Matrix<int> m3;
    Matrix<int> m4;
    Matrix<int> m5;
};

TEST_F(MatrixTest, sumtest) {
    m5 = m3 + m4;
    for (int i = 0; i < 25; i++) {
        EXPECT_EQ(m5[i], i * 2);
    }
}


TEST_F(MatrixTest, OperatorIndexing) {
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(m[i], i);
        EXPECT_EQ(m.Get(i), i);
    }
    EXPECT_THROW(m[-1], IndexOutOfRange);
    EXPECT_THROW(m[9], IndexOutOfRange);
}


TEST_F(MatrixTest, MultiplyScalar) {
    Matrix<int> prod = m * 2;
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(prod[i], i * 2);
    }
}

TEST_F(MatrixTest, Norm) {
    EXPECT_EQ(m.norm(), 21);
    EXPECT_EQ(m2.norm(), 5*3);
}
TEST_F(MatrixTest, multiplicationtest) {
    m5 = m4 * 3;
    for (int i = 0; i < 25; i++) {
        EXPECT_EQ(m5[i], i * 3);
    }
}

TEST_F(MatrixTest, elementarytest) {
    m4.elementary(0, 1);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(m4[i], i + i + 5);
    }
    m3.elementary(0,1,-1);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(m3[i], i - i - 5);
    }
}

class MinHeapTest : public ::testing::Test {
protected:
    BinaryHeapPtr<int> heap{BinaryHeapPtr<int>::Order::MIN};

    void SetUp() override {
        heap.insert(5);
        heap.insert(3);
        heap.insert(8);
        heap.insert(1);
        heap.insert(4);
    }
};

TEST_F(MinHeapTest, ContainsExisting) {
    EXPECT_TRUE(heap.contains(5));
    EXPECT_TRUE(heap.contains(1));
    EXPECT_TRUE(heap.contains(8));
}

TEST_F(MinHeapTest, ContainsNonExisting) {
    EXPECT_FALSE(heap.contains(0));
    EXPECT_FALSE(heap.contains(10));
}

TEST_F(MinHeapTest, ExtractRootSequence) {
    std::vector<int> expected = {1, 3, 4, 5, 8};
    for (int exp : expected) {
        EXPECT_EQ(heap.extractRoot(), exp);
    }
    EXPECT_THROW(heap.extractRoot(), std::out_of_range);
}

TEST_F(MinHeapTest, InsertDuplicates) {
    heap.insert(3);
    heap.insert(1);
    std::vector<int> extracted;
    while (true) {
        try {
            extracted.push_back(heap.extractRoot());
        } catch (const std::out_of_range&) {
            break;
        }
    }
    std::vector<int> expected = {1, 1, 3, 3, 4, 5, 8};
    EXPECT_EQ(extracted, expected);
}

TEST(BinaryHeapPtrMaxTest, MaxOrderBehavior) {
    BinaryHeapPtr<int> maxHeap{BinaryHeapPtr<int>::Order::MAX};
    maxHeap.insert(5);
    maxHeap.insert(2);
    maxHeap.insert(9);
    maxHeap.insert(1);

    EXPECT_TRUE(maxHeap.contains(9));
    EXPECT_TRUE(maxHeap.contains(1));
    EXPECT_FALSE(maxHeap.contains(3));

    EXPECT_EQ(maxHeap.extractRoot(), 9);
    EXPECT_EQ(maxHeap.extractRoot(), 5);
    EXPECT_EQ(maxHeap.extractRoot(), 2);
    EXPECT_EQ(maxHeap.extractRoot(), 1);
    EXPECT_THROW(maxHeap.extractRoot(), std::out_of_range);
}

TEST(BinaryHeapPtrEmptyTest, ContainsOnEmpty) {
    BinaryHeapPtr<int> emptyHeap;
    EXPECT_FALSE(emptyHeap.contains(42));
}

TEST(BinaryHeapPtrEmptyTest, ExtractOnEmptyThrows) {
    BinaryHeapPtr<int> emptyHeap;
    EXPECT_THROW(emptyHeap.extractRoot(), std::out_of_range);
}


class MinHeapArrayTest : public ::testing::Test {
protected:
    // тестируем BinaryHeapArray<int>
    BinaryHeapArray<int> heap;

    void SetUp() override {
        // наполним кучю значениями
        heap.insert(5);
        heap.insert(3);
        heap.insert(8);
        heap.insert(1);
        heap.insert(4);
    }
};

TEST_F(MinHeapArrayTest, ContainsExisting) {
    EXPECT_TRUE(heap.contains(5));
    EXPECT_TRUE(heap.contains(1));
    EXPECT_TRUE(heap.contains(8));
}

TEST_F(MinHeapArrayTest, ContainsNonExisting) {
    EXPECT_FALSE(heap.contains(0));
    EXPECT_FALSE(heap.contains(10));
}

TEST_F(MinHeapArrayTest, ExtractRootSequence) {
    // для min-heap извлечение корня даёт отсортированную по возрастанию последовательность
    std::vector<int> expected = {1, 3, 4, 5, 8};
    for (int exp : expected) {
        EXPECT_EQ(heap.extractRoot(), exp);
    }
    // после опустошения должна бросать исключение
    EXPECT_THROW(heap.extractRoot(), std::out_of_range);
}

TEST_F(MinHeapArrayTest, InsertDuplicates) {
    // дублирование элементов допустимо
    heap.insert(3);
    heap.insert(1);

    std::vector<int> extracted;
    // извлечём все до исключения
    while (true) {
        try {
            extracted.push_back(heap.extractRoot());
        } catch (const std::out_of_range&) {
            break;
        }
    }

    // изначально {1,3,4,5,8}, затем дубли {1,3}
    std::vector<int> expected = {1, 1, 3, 3, 4, 5, 8};
    EXPECT_EQ(extracted, expected);
}

TEST(BinaryHeapArrayEmptyTest, ContainsOnEmpty) {
    BinaryHeapArray<int> emptyHeap;
    EXPECT_FALSE(emptyHeap.contains(42));
}

TEST(BinaryHeapArrayEmptyTest, ExtractOnEmptyThrows) {
    BinaryHeapArray<int> emptyHeap;
    EXPECT_THROW(emptyHeap.extractRoot(), std::out_of_range);
}

template <typename T>
std::vector<T> toStdVector(const Dynamic_array<T>& arr) {
    std::vector<T> v;
    for (int i = 0; i < arr.size(); ++i) {
        v.push_back(arr[i]);
    }
    return v;
}

class TreeTest : public ::testing::Test {
protected:
    Tree<int> tree;

    void SetUp() override {
        std::vector<int> vals = {5, 3, 7, 2, 4, 6, 8};
        for (int v : vals) {
            tree.insertNewNode(v);
        }
    }
};

TEST_F(TreeTest, IsEmptyOnNonEmpty) {
    EXPECT_FALSE(tree.isEmpty());
}

TEST(TreeEmptyTest, IsEmptyOnEmpty) {
    Tree<int> empty;
    EXPECT_TRUE(empty.isEmpty());
}

TEST_F(TreeTest, SearchExisting) {
    TreeNode<int>* n = tree.search(4);
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->getData(), 4);
}

TEST_F(TreeTest, SearchNonExisting) {
    EXPECT_EQ(tree.search(100), nullptr);
    EXPECT_EQ(tree.search(0), nullptr);
}

TEST_F(TreeTest, PreOrderTraversal) {
    // КЛП: 5,3,2,4,7,6,8
    auto arr = tree.preOrderPrint();
    std::vector<int> expected = {5,3,2,4,7,6,8};
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST_F(TreeTest, InOrderTraversal) {
    // ЛКП: 2,3,4,5,6,7,8
    auto arr = tree.inOrderPrint();
    std::vector<int> expected = {2,3,4,5,6,7,8};
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST_F(TreeTest, PostOrderTraversal) {
    // ЛПК: 2,4,3,6,8,7,5
    auto arr = tree.postOrderPrint();
    std::vector<int> expected = {2,4,3,6,8,7,5};
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST_F(TreeTest, RootRightLeftTraversal) {
    // КПЛ: root, right, left => 5,7,8,6,3,4,2
    auto arr = tree.rootRightLeftPrint();
    std::vector<int> expected = {5,7,8,6,3,4,2};
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST_F(TreeTest, RightRootLeftTraversal) {
    // ПКЛ: right, root, left => 8,7,6,5,4,3,2
    auto arr = tree.rightRootLeftPrint();
    std::vector<int> expected = {8,7,6,5,4,3,2};
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST_F(TreeTest, RightLeftRootTraversal) {
    // ПЛК: right, left, root => 8,6,7,4,2,3,5
    auto arr = tree.rightLeftRootPrint();
    std::vector<int> expected = {8,6,7,4,2,3,5};
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST_F(TreeTest, MapFunction) {
    // Умножаем на 10, проверяем in-order в новом дереве
    auto mapped = tree.map<int>([](const int& x){ return x * 10; });
    auto arr = mapped.inOrderPrint();
    std::vector<int> expected = {2,3,4,5,6,7,8};
    for (auto &v : expected) v *= 10;
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST_F(TreeTest, WhereFunction) {
    // Оставляем только чётные
    auto filtered = tree.where([](const int& x){ return x % 2 == 0; });
    auto arr = filtered.inOrderPrint();
    std::vector<int> expected = {2,4,6,8};
    EXPECT_EQ(toStdVector(arr), expected);
}

TEST(TreeEdgeTest, TraversalsOnEmpty) {
    Tree<int> empty;
    EXPECT_TRUE(toStdVector(empty.preOrderPrint()).empty());
    EXPECT_TRUE(toStdVector(empty.inOrderPrint()).empty());
    EXPECT_TRUE(toStdVector(empty.postOrderPrint()).empty());
    EXPECT_TRUE(toStdVector(empty.rootRightLeftPrint()).empty());
    EXPECT_TRUE(toStdVector(empty.rightRootLeftPrint()).empty());
    EXPECT_TRUE(toStdVector(empty.rightLeftRootPrint()).empty());
}


int test(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif //LABA_2_ALL_TEST_HPP
