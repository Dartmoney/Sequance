//
// Created by islam on 16.06.2025.
//

#ifndef LABA3_TREEWINDOW_HPP
#define LABA3_TREEWINDOW_HPP
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QVBoxLayout>
#include "Tree.hpp"
#include "TreeNode.hpp"
class TreeWindow : public QMainWindow {
Q_OBJECT

public:
    explicit TreeWindow(QWidget *parent = nullptr);
    void Insertbutclic();
    void setTree(Tree<int> *newTree);
    void drawTree();
    void removebutclic();
    void searchbutclic();
    void clearbutclic();


private:
    Tree<int>* tree;
    QGraphicsScene* scene;
    QGraphicsView* view;

    void drawNode(TreeNode<int>* node, int x, int y, int xOffset);
};

#endif //LABA3_TREEWINDOW_HPP
