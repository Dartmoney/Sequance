//
// Created by islam on 16.06.2025.
//

#ifndef LABA3_TREEWINDOW_HPP
#define LABA3_TREEWINDOW_HPP
#pragma once
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QVBoxLayout>
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "ui/Trrwindow.h"

class TreeWindow : public QMainWindow {
Q_OBJECT

public:
    explicit TreeWindow(QWidget *parent = nullptr);
    ~TreeWindow() override {
        delete ui;
    }
    void Insertbutclic();
    void drawTree();
    void removebutclic();
    void searchbutclic();
    void clearbutclic();
private:
    void setupConnections();
    Tree<int> tree;

    QGraphicsScene* scene;
    QGraphicsView* view;
    Ui::Form *ui;
    void drawNode(TreeNode<int>* node, int x, int y, int xOffset);
};

#endif //LABA3_TREEWINDOW_HPP
