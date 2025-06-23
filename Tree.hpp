//
// Created by islam on 23.05.2025.
//

#ifndef LABA3_TREE_HPP
#define LABA3_TREE_HPP

#include <iostream>
#include <complex>
#pragma once

#include <functional>
#include "TreeNode.hpp"
#include "Dynamic_array.hpp"
#include <vector>
#include <queue>
#include <stdexcept>
#include <fstream>
#include <string>
template<typename T>
class Tree {
public:
    Tree();

    bool isEmpty() const;

    void insertNewNode(const T &value);

    TreeNode<T> *search(const T &key);
    TreeNode<T>* getRoot() const {
        return rootPtr;
    }
    void saveToHTML(const std::string& filename) const;
    void clear();
    Dynamic_array<T> preOrderPrint() const;   // КЛП
    Dynamic_array<T> inOrderPrint() const;    // ЛКП
    Dynamic_array<T> postOrderPrint() const;  // ЛПК
    Dynamic_array<T> rootRightLeftPrint() const; // КПЛ
    Dynamic_array<T> rightRootLeftPrint() const; // ПКЛ
    Dynamic_array<T> rightLeftRootPrint() const; // ПЛК
    template<typename U>
    Tree<U> map(std::function<U(const T &)> f) const;
    int countNodes(TreeNode<T>* node) const;
    Tree<T> where(std::function<bool(const T &)> pred) const;
    int calculateHeight(TreeNode<T>* node) const;
    void balance() {
        std::vector<T> nodes;
        inOrderCollect(rootPtr, nodes);
        clear(rootPtr);
        rootPtr = buildBalancedTree(nodes, 0, nodes.size() - 1);
    }

    void inOrderCollect(TreeNode<T>* node, std::vector<T>& nodes) {
        if (!node) return;
        inOrderCollect(node->left, nodes);
        nodes.push_back(node->data);
        inOrderCollect(node->right, nodes);
    }

    TreeNode<T>* buildBalancedTree(const std::vector<T>& nodes, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end) / 2;
        TreeNode<T>* newNode = new TreeNode<T>{nodes[mid]};
        newNode->left = buildBalancedTree(nodes, start, mid - 1);
        newNode->right = buildBalancedTree(nodes, mid + 1, end);
        return newNode;
    }
    std::string serialize() const {
        std::ostringstream oss;
        serializeHelper(rootPtr, oss);
        return oss.str();
    }

    void serializeHelper(TreeNode<T>* node, std::ostringstream& oss) const {
        if (!node) {
            oss << "# ";
            return;
        }
        oss << node->data << " ";
        serializeHelper(node->left, oss);
        serializeHelper(node->right, oss);
    }
    void deserialize(const std::string& data) {
        std::istringstream iss(data);
        clear(rootPtr);
        rootPtr = deserializeHelper(iss);
    }

    TreeNode<T>* deserializeHelper(std::istringstream& iss) {
        std::string val;
        iss >> val;
        if (val == "#") return nullptr;

        std::istringstream converter(val);
        T value;
        converter >> value;

        TreeNode<T>* node = new TreeNode<T>{value};
        node->left = deserializeHelper(iss);
        node->right = deserializeHelper(iss);
        return node;
    }
    bool containsSubtree(const Tree<T>& subtree) const {
        return isSubtree(rootPtr, subtree.rootPtr);
    }

    bool isSubtree(TreeNode<T>* node, TreeNode<T>* sub) const {
        if (!sub) return true;
        if (!node) return false;
        if (areIdentical(node, sub)) return true;
        return isSubtree(node->left, sub) || isSubtree(node->right, sub);
    }

    bool areIdentical(TreeNode<T>* a, TreeNode<T>* b) const {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return a->data == b->data &&
               areIdentical(a->left, b->left) &&
               areIdentical(a->right, b->right);
    }
private:
    void generateSubtreeHTML(TreeNode<T>* node, std::ofstream& out) const;
    TreeNode<T> *rootPtr;
    void clearUtility(TreeNode<T>* node);

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

    string generateHTML() const;

    string generateSubtreeHTML(TreeNode<T> *node) const;
};
template<typename T>
void Tree<T>::clear() {
    clearUtility(rootPtr);
    rootPtr = nullptr;
}

template<typename T>
void Tree<T>::saveToHTML(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    out << R"(
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF-8">
        <title>Binary Tree Visualization</title>
        <style>
            * {
                margin: 0;
                padding: 0;
                box-sizing: border-box;
            }
            body {
                background: #f8f9fa;
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                padding: 20px;
            }
            .tree-title {
                text-align: center;
                color: #2c3e50;
                margin: 20px 0 40px;
                font-size: 32px;
                font-weight: 600;
                text-shadow: 1px 1px 2px rgba(0,0,0,0.1);
            }
            .tree-container {
                display: flex;
                justify-content: center;
                min-height: 100vh;
            }
            .tree-node {
                display: flex;
                flex-direction: column;
                align-items: center;
                position: relative;
                margin: 0 25px;
            }
            .node-value {
                width: 50px;
                height: 50px;
                line-height: 50px;
                border: 3px solid #3498db;
                border-radius: 50%;
                background: linear-gradient(145deg, #ffffff, #f0f0f0);
                text-align: center;
                position: relative;
                z-index: 2;
                box-shadow: 0 4px 8px rgba(0,0,0,0.1);
                font-weight: bold;
                color: #2c3e50;
                font-size: 18px;
                transition: all 0.3s ease;
            }
            .node-value:hover {
                transform: scale(1.1);
                background: linear-gradient(145deg, #3498db, #2980b9);
                color: white;
                box-shadow: 0 6px 12px rgba(0,0,0,0.15);
            }
            .node-children {
                display: flex;
                justify-content: center;
                position: relative;
                padding-top: 70px;
            }
            .child {
                position: relative;
                margin: 0 15px;
            }
            .child::before {
                content: '';
                position: absolute;
                top: -50px;
                left: 50%;
                width: 3px;
                height: 50px;
                background: #3498db;
                transform: translateX(-50%);
            }
            .child.left {
                margin-right: 50px;
            }
            .child.left::before {
                transform: translateX(-50%) rotate(-35deg);
                width: 4px;
                height: 55px;
                top: -55px;
                left: calc(50% + 25px);
            }
            .child.right {
                margin-left: 50px;
            }
            .child.right::before {
                transform: translateX(-50%) rotate(35deg);
                width: 4px;
                height: 55px;
                top: -55px;
                left: calc(50% - 25px);
            }
            .no-children .child {
                display: none;
            }
            .controls {
                text-align: center;
                margin: 30px 0;
            }
            .tree-info {
                background: #e3f2fd;
                border-radius: 10px;
                padding: 15px;
                margin: 20px auto;
                max-width: 600px;
                box-shadow: 0 2px 4px rgba(0,0,0,0.05);
            }
            .tree-info h3 {
                color: #2c3e50;
                margin-bottom: 10px;
                text-align: center;
            }
            .tree-stats {
                display: flex;
                justify-content: center;
                gap: 20px;
                flex-wrap: wrap;
            }
            .stat-item {
                background: white;
                padding: 10px 15px;
                border-radius: 8px;
                box-shadow: 0 2px 4px rgba(0,0,0,0.08);
            }
        </style>
    </head>
    <body>
        <h1 class="tree-title">Binary Search Tree Visualization</h1>

        <div class="tree-info">
            <h3>Tree Information</h3>
            <div class="tree-stats">
                <div class="stat-item">Total nodes: )" << countNodes(rootPtr) << R"(</div>
                <div class="stat-item">Tree height: )" << calculateHeight(rootPtr) << R"(</div>
                <div class="stat-item">Root value: )" << (rootPtr ? std::to_string(rootPtr->data) : "N/A") << R"(</div>
            </div>
        </div>

        <div class="tree-container">
    )";

    if (rootPtr) {
        generateSubtreeHTML(rootPtr, out);
    } else {
        out << "<h2 style='text-align:center;color:#7f8c8d;margin-top:50px;'>🌳 Tree is empty 🌳</h2>";
    }

    out << R"(
        </div>

        <div class="controls">
            <button onclick='window.location.reload()' style="
    background: #3498db;
    color: white;
    border: none;
    padding: 12px 24px;
    border-radius: 30px;
    font-size: 16px;
    cursor: pointer;
    transition: all 0.3s ease;
    box-shadow: 0 4px 8px rgba(0,0,0,0.1);
    ">
    Refresh View
            </button>
              </div>

                <script>
                document.querySelectorAll('.node-value').forEach(node => {
                        node.addEventListener('click', function() {
                const value = this.textContent;
                alert('Clicked node: ' + value);
            });
                });
    </script>
      </body>
        </html>
    )";

    out.close();
}

template<typename T>
void Tree<T>::generateSubtreeHTML(TreeNode<T>* node, std::ofstream& out) const {
    if (!node) return;

    out << "<div class='tree-node'>";
    out << "<div class='node-value'>" << node->data << "</div>";

    out << "<div class='node-children ";
    if (!node->leftPtr && !node->rightPtr) {
        out << "no-children";
    }
    out << "'>";

    if (node->leftPtr) {
        out << "<div class='child left'>";
        generateSubtreeHTML(node->leftPtr, out);
        out << "</div>";
    }

    if (node->rightPtr) {
        out << "<div class='child right'>";
        generateSubtreeHTML(node->rightPtr, out);
        out << "</div>";
    }

    out << "</div></div>";
}

// Вспомогательные функции для статистики
template<typename T>
int Tree<T>::countNodes(TreeNode<T>* node) const {
    if (!node) return 0;
    return 1 + countNodes(node->leftPtr) + countNodes(node->rightPtr);
}

template<typename T>
int Tree<T>::calculateHeight(TreeNode<T>* node) const {
    if (!node) return 0;
    return 1 + std::max(calculateHeight(node->leftPtr),
                        calculateHeight(node->rightPtr));
}
template<typename T>
void Tree<T>::clearUtility(TreeNode<T>* node) {
    if (!node) return;
    clearUtility(node->leftPtr);
    clearUtility(node->rightPtr);
    delete node;
}
template<typename T>
Tree<T>::Tree()
{
    rootPtr = 0;
}

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
void Tree<T>::insertNewNodeUtility(TreeNode<T> **temp, const T &dataIn) {
    if(*temp == 0) //if node is null create a new node with input data
        *temp = new TreeNode<T>(dataIn);
    else {
        if (dataIn < (*temp)->data) //if input data is less than data in current node
            insertNewNodeUtility(&((*temp)->leftPtr),
                                 dataIn); //recursive function call with current node's left child as input leaf
        else {
            if (dataIn > (*temp)->data) //if input data is greater than data in current node
                insertNewNodeUtility(&((*temp)->rightPtr),
                                     dataIn); //recursive function call with current node's right child as input leaf
            else //if input data is equal to data in current node
                cout << dataIn << " is a duplicate value " << endl; //duplicate values ignored

        }
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
template<typename T>
class BinaryHeapPriorityQueue {
private:
    BinaryHeapPtr<T> heap;

public:
    void push(const T& value) {
        heap.insert(value);
    }

    const T& top() const {
        return heap.getMax();
    }

    void pop() {
        heap.extractMax();
    }

    bool empty() const {
        return heap.isEmpty();
    }

    size_t size() const {
        return heap.getSize();
    }
};


template<typename T>
class BSTPriorityQueue {
private:
    Tree<T> bst;

public:
    void push(const T& value) {
        bst.insertNewNode(value);
    }

    const T& top() const {
        TreeNode<T>* current = bst.getRoot();
        while (current && current->right) {
            current = current->right;
        }
        return current->data;
    }

    void pop() {
        bst.remove(top());
    }

    bool empty() const {
        return bst.getRoot() == nullptr;
    }

    size_t size() const {
        return bst.size();
    }
};
#endif //LABA3_TREE_HPP
