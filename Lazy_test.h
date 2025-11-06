//
// Created by imako on 06.11.2025.
//

#ifndef LABA3_LAZY_TEST_H
#define LABA3_LAZY_TEST_H
#include <gtest/gtest.h>
#include "Dynamic_array.hpp"
#include "Error.hpp"

TEST(DynamicArrayTest, DefaultConstructor) {
    Dynamic_array<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(DynamicArrayTest, SizeConstructor) {
    Dynamic_array<int> arr(5);
    EXPECT_EQ(arr.size(), 5);
    EXPECT_NO_THROW(arr[0]);
}

TEST(DynamicArrayTest, CopyConstructor) {
    Dynamic_array<int> arr1(3);
    arr1.Set(0, 10);
    arr1.Set(1, 20);
    arr1.Set(2, 30);

    Dynamic_array<int> arr2(arr1);
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr2[1], 20);
    EXPECT_EQ(arr2[2], 30);
}

TEST(DynamicArrayTest, PushBack) {
    Dynamic_array<int> arr;
    arr.push_back(42);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);

    arr.push_back(7);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 7);
}

TEST(DynamicArrayTest, ResizeIncrease) {
    Dynamic_array<int> arr(2);
    arr[0] = 1;
    arr[1] = 2;
    arr.resize(5);

    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(DynamicArrayTest, ResizeDecrease) {
    Dynamic_array<int> arr(5);
    for (int i = 0; i < 5; i++) arr.Set(i, i);
    arr.resize(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
}

TEST(DynamicArrayTest, SetAndGet) {
    Dynamic_array<int> arr(3);
    arr.Set(1, 99);
    EXPECT_EQ(arr[1], 99);

    arr[2] = 123;
    EXPECT_EQ(arr[2], 123);
}

TEST(DynamicArrayTest, IndexOutOfRange) {
    Dynamic_array<int> arr(2);
    EXPECT_THROW(arr[2], IndexOutOfRange);
    EXPECT_THROW(arr[-1], IndexOutOfRange);
}

TEST(DynamicArrayTest, FromArrayConstructor) {
    int items[] = {5, 10, 15};
    Dynamic_array<int> arr(items, 3);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 15);
}

#endif //LABA3_LAZY_TEST_H