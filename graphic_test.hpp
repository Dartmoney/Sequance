//
// Created by islam on 18.06.2025.
//

#ifndef LABA3_GRAPHIC_TEST_HPP
#define LABA3_GRAPHIC_TEST_HPP
#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>
#include "Tree.hpp"

void benchmarkInsert() {
    std::ofstream out("benchmark.csv");
    out << "Count,TimeMicroseconds\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1'000'000);

    for (int n = 100; n <= 500000; n += 100) {
        Tree<int> tree;

        std::vector<int> values(n);
        for (int& v : values) v = distrib(gen);

        auto start = std::chrono::high_resolution_clock::now();
        for (int val : values) tree.insertNewNode(val);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        out << n << "," << duration << "\n";
    }

    out.close();
}
#endif //LABA3_GRAPHIC_TEST_HPP
