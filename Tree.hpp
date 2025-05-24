//
// Created by islam on 23.05.2025.
//

#ifndef LABA3_TREE_HPP
#define LABA3_TREE_HPP

#include <iostream>

#pragma once

#include <functional>
#include "TreeNode.hpp"
#include "Dynamic_array.hpp"
#include <vector>
#include <queue>
#include <stdexcept>

template<typename T>
class Tree {
public:
    Tree();

    bool isEmpty() const;

    void insertNewNode(const T &value);

    TreeNode<T> *search(const T &key);

    Dynamic_array<T> preOrderPrint() const;   // КЛП
    Dynamic_array<T> inOrderPrint() const;    // ЛКП
    Dynamic_array<T> postOrderPrint() const;  // ЛПК
    Dynamic_array<T> rootRightLeftPrint() const; // КПЛ
    Dynamic_array<T> rightRootLeftPrint() const; // ПКЛ
    Dynamic_array<T> rightLeftRootPrint() const; // ПЛК
    template<typename U>
    Tree<U> map(std::function<U(const T &)> f) const;

    Tree<T> where(std::function<bool(const T &)> pred) const;

private:
    TreeNode<T> *rootPtr;

    void rootRightLeftCollect(TreeNode<T> *, Dynamic_array<T> &) const;

    void rightRootLeftCollect(TreeNode<T> *, Dynamic_array<T> &) const;

    void rightLeftRootCollect(TreeNode<T> *, Dynamic_array<T> &) const;

    void insertNewNodeUtility(TreeNode<T> **node, const T &value);

    TreeNode<T> *searchUtility(TreeNode<T> *node, const T &key) const;

    void preOrderCollect(TreeNode<T> *node, Dynamic_array<T> &out) const;

    void inOrderCollect(TreeNode<T> *node, Dynamic_array<T> &out) const;

    void postOrderCollect(TreeNode<T> *node, Dynamic_array<T> &out) const;

    template<typename U>
    void mapUtility(TreeNode<T> *, Tree<U> &, std::function<U(const T &)>) const;

    void whereUtility(TreeNode<T> *, Tree<T> &, std::function<bool(const T &)>) const;
};

template<typename T>
Tree<T>::Tree() : rootPtr(nullptr) {}

template<typename T>
bool Tree<T>::isEmpty() const {
    return rootPtr == nullptr;
}

template<typename T>
void Tree<T>::insertNewNode(const T &value) {
    insertNewNodeUtility(&rootPtr, value);
}

template<typename T>
Dynamic_array<T> Tree<T>::rootRightLeftPrint() const {
    Dynamic_array<T> result;
    rootRightLeftCollect(rootPtr, result);
    return result;
}

template<typename T>
void Tree<T>::rootRightLeftCollect(TreeNode<T> *node, Dynamic_array<T> &out) const {
    if (!node) return;
    out.push_back(node->data);
    rootRightLeftCollect(node->rightPtr, out);
    rootRightLeftCollect(node->leftPtr, out);
}

template<typename T>
Dynamic_array<T> Tree<T>::rightRootLeftPrint() const {
    Dynamic_array<T> result;
    rightRootLeftCollect(rootPtr, result);
    return result;
}

template<typename T>
void Tree<T>::rightRootLeftCollect(TreeNode<T> *node, Dynamic_array<T> &out) const {
    if (!node) return;
    rightRootLeftCollect(node->rightPtr, out);
    out.push_back(node->data);
    rightRootLeftCollect(node->leftPtr, out);
}

template<typename T>
Dynamic_array<T> Tree<T>::rightLeftRootPrint() const {
    Dynamic_array<T> result;
    rightLeftRootCollect(rootPtr, result);
    return result;
}

template<typename T>
void Tree<T>::rightLeftRootCollect(TreeNode<T> *node, Dynamic_array<T> &out) const {
    if (!node) return;
    rightLeftRootCollect(node->rightPtr, out);
    rightLeftRootCollect(node->leftPtr, out);
    out.push_back(node->data);
}

template<typename T>
void Tree<T>::insertNewNodeUtility(TreeNode<T> **node, const T &value) {
    if (*node == nullptr) {
        *node = new TreeNode<T>(value);
    } else if (value < (*node)->data) {
        insertNewNodeUtility(&((*node)->leftPtr), value);
    } else if (value > (*node)->data) {
        insertNewNodeUtility(&((*node)->rightPtr), value);
    } else {
        std::cout << value << " is a duplicate value\n";
    }
}

template<typename T>
TreeNode<T> *Tree<T>::search(const T &key) {
    return searchUtility(rootPtr, key);
}

template<typename T>
TreeNode<T> *Tree<T>::searchUtility(TreeNode<T> *node, const T &key) const {
    if (!node) return nullptr;
    if (key == node->data) return node;
    if (key < node->data)
        return searchUtility(node->leftPtr, key);
    else
        return searchUtility(node->rightPtr, key);
}

template<typename T>
Dynamic_array<T> Tree<T>::preOrderPrint() const {
    Dynamic_array<T> result;
    preOrderCollect(rootPtr, result);
    return result;
}

template<typename T>
void Tree<T>::preOrderCollect(TreeNode<T> *node, Dynamic_array<T> &out) const {
    if (!node) return;
    out.push_back(node->data);
    preOrderCollect(node->leftPtr, out);
    preOrderCollect(node->rightPtr, out);
}

template<typename T>
Dynamic_array<T> Tree<T>::inOrderPrint() const {
    Dynamic_array<T> result;
    inOrderCollect(rootPtr, result);
    return result;
}

template<typename T>
void Tree<T>::inOrderCollect(TreeNode<T> *node, Dynamic_array<T> &out) const {
    if (!node) return;
    inOrderCollect(node->leftPtr, out);
    out.push_back(node->data);
    inOrderCollect(node->rightPtr, out);
}

template<typename T>
Dynamic_array<T> Tree<T>::postOrderPrint() const {
    Dynamic_array<T> result;
    postOrderCollect(rootPtr, result);
    return result;
}

template<typename T>
void Tree<T>::postOrderCollect(TreeNode<T> *node, Dynamic_array<T> &out) const {
    if (!node) return;
    postOrderCollect(node->leftPtr, out);
    postOrderCollect(node->rightPtr, out);
    out.push_back(node->data);
}

template<typename T>
template<typename U>
Tree<U> Tree<T>::map(std::function<U(const T &)> f) const {
    Tree<U> result;
    mapUtility(rootPtr, result, f);
    return result;
}

template<typename T>
template<typename U>
void Tree<T>::mapUtility(TreeNode<T> *node, Tree<U> &out, std::function<U(const T &)> f) const {
    if (!node) return;
    out.insertNewNode(f(node->data));
    mapUtility(node->leftPtr, out, f);
    mapUtility(node->rightPtr, out, f);
}

template<typename T>
Tree<T> Tree<T>::where(std::function<bool(const T &)> pred) const {
    Tree<T> result;
    whereUtility(rootPtr, result, pred);
    return result;
}

template<typename T>
void Tree<T>::whereUtility(TreeNode<T> *node, Tree<T> &out, std::function<bool(const T &)> pred) const {
    if (!node) return;
    if (pred(node->data)) out.insertNewNode(node->data);
    whereUtility(node->leftPtr, out, pred);
    whereUtility(node->rightPtr, out, pred);
}


template<typename T>
class BinaryHeapArray {
public:
    BinaryHeapArray() {
        data.resize(1);
    }

    void insert(const T &x) {
        data.push_back(x);
        bubbleUp(data.size() - 1);
    }

    bool contains(const T &x) const {
        for (int i = 1; i < data.size(); ++i)
            if (data[i] == x) return true;
        return false;
    }

    T extractRoot() {
        if (data.size() <= 1)
            throw std::out_of_range("Heap is empty");
        T rootVal = data[1];
        data[1] = data[data.size()];
        data.resize(data.size() - 1);
        bubbleDown(1);
        return rootVal;
    }

private:
    Dynamic_array<T> data;

    void bubbleUp(int i) {
        while (i > 1) {
            int p = i / 2;
            if (data[i] < data[p]) {
                std::swap(data[i], data[p]);
                i = p;
            } else break;
        }
    }

    void bubbleDown(int i) {
        int n = data.size() - 1;
        while (true) {
            int l = 2 * i, r = 2 * i + 1, smallest = i;
            if (l <= n && data[l] < data[smallest]) smallest = l;
            if (r <= n && data[r] < data[smallest]) smallest = r;
            if (smallest != i) {
                std::swap(data[i], data[smallest]);
                i = smallest;
            } else break;
        }
    }
};

template<typename T>
struct HeapNode {
    T data;
    HeapNode *left;
    HeapNode *right;
    HeapNode *parent;

    HeapNode(const T &v)
            : data(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T>
class BinaryHeapPtr {
public:
    enum class Order {
        MIN, MAX
    };

    BinaryHeapPtr(Order o = Order::MIN)
            : root(nullptr), nodeCount(0), heapOrder(o) {}

    void insert(const T &value) {

        HeapNode<T> *newNode = new HeapNode<T>(value);
        ++nodeCount;

        if (!root) {
            root = newNode;
            return;
        }

        HeapNode<T> *parent = getNodeByIndex(nodeCount / 2);
        newNode->parent = parent;
        if (!(nodeCount & 1))
            parent->left = newNode;
        else
            parent->right = newNode;

        bubbleUp(newNode);
    }

    bool contains(const T &value) const {
        if (!root) return false;
        std::queue<HeapNode<T> *> q;
        q.push(root);
        while (!q.empty()) {
            auto *n = q.front();
            q.pop();
            if (n->data == value) return true;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        return false;
    }

    T extractRoot() {
        if (!root) throw std::out_of_range("Heap is empty");
        T ret = root->data;
        if (nodeCount == 1) {
            delete root;
            root = nullptr;
            nodeCount = 0;
            return ret;
        }

        HeapNode<T> *last = getNodeByIndex(nodeCount);
        root->data = last->data;

        if (last->parent->left == last) last->parent->left = nullptr;
        else last->parent->right = nullptr;
        delete last;
        --nodeCount;

        bubbleDown(root);
        return ret;
    }

private:
    HeapNode<T> *root;
    int nodeCount;
    Order heapOrder;

    void bubbleUp(HeapNode<T> *node) {
        while (node->parent) {
            bool violation = (heapOrder == Order::MIN)
                             ? (node->data < node->parent->data)
                             : (node->data > node->parent->data);
            if (!violation) break;
            std::swap(node->data, node->parent->data);
            node = node->parent;
        }
    }

    void bubbleDown(HeapNode<T> *node) {
        while (true) {
            HeapNode<T> *pick = nullptr;
            if (node->left) pick = node->left;
            if (node->right) {
                bool cmp = (heapOrder == Order::MIN)
                           ? (node->right->data < pick->data)
                           : (node->right->data > pick->data);
                if (pick == nullptr || cmp) pick = node->right;
            }
            if (!pick) break;

            bool violation = (heapOrder == Order::MIN)
                             ? (pick->data < node->data)
                             : (pick->data > node->data);
            if (!violation) break;

            std::swap(node->data, pick->data);
            node = pick;
        }
    }

    HeapNode<T> *getNodeByIndex(int idx) const {
        std::vector<bool> path;
        while (idx > 1) {
            path.push_back((idx & 1) != 0);
            idx >>= 1;
        }
        HeapNode<T> *cur = root;
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            if (!cur) return nullptr;
            cur = *it ? cur->right : cur->left;
        }
        return cur;
    }
};

#endif //LABA3_TREE_HPP
