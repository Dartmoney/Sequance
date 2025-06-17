//
// Created by islam on 23.05.2025.
//

#ifndef LABA3_TREENODE_HPP
#define LABA3_TREENODE_HPP
template <typename T>
class Tree;

template <typename T>
class TreeNode
{
    friend class Tree<T>;

public:
    TreeNode(T);
    T getData(); //returns data stored in node
    TreeNode* leftPtr; //pointer to left child node of node
    TreeNode* rightPtr; //pointer to right child node of node
    T data;
private:
    TreeNode* parent;
};

template <typename T>
TreeNode<T>::TreeNode(T dataIn)
{
    data = dataIn;
    leftPtr = 0; //pointer to left and right child nodes are initilized to NULL
    rightPtr = 0;
    parent = 0;
}

template <typename T>
T TreeNode<T>::getData()
{
    return data;
}

#endif //LABA3_TREENODE_HPP
