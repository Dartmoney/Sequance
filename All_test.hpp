//
// Created by islam on 24.04.2025.
//

#ifndef LABA_2_ALL_TEST_HPP
#define LABA_2_ALL_TEST_HPP

#include <gtest/gtest.h>
#include "Linked_List.hpp"
#include "Dynamic_array.hpp"
#include "Matrix.hpp"

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
    // Norm is max row sum
    // Rows: [0+1+2=3, 3+4+5=12, 6+7+8=21]
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
int test(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif //LABA_2_ALL_TEST_HPP
