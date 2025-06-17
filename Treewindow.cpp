#include "TreeWindow.hpp"
#include <QVBoxLayout>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QString>
#include "TreeWindow.hpp"
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QPen>
#include "Tree.hpp"


TreeWindow::TreeWindow(QWidget *parent) : QMainWindow(parent), tree(nullptr) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    setWindowTitle("Binary Tree Viewer");
    resize(800, 600);
}

void TreeWindow::setTree(Tree<int> *newTree) {
    tree = newTree;
    scene->clear();
    if (tree && !tree->isEmpty()) {
        drawTree();
    }
}

void TreeWindow::drawTree() {
    if (!tree || tree->isEmpty()) return;
    TreeNode<int> *root = tree->getRoot();
    drawNode(root, 0, 0, 300);  // начальные координаты и горизонтальное смещение
}

void TreeWindow::drawNode(TreeNode<int> *node, int x, int y, int xOffset) {
    if (!node) return;

    int radius = 20;
    int spacingY = 80;

    // Нарисовать узел
    QGraphicsEllipseItem *circle = scene->addEllipse(x - radius, y - radius, 2 * radius, 2 * radius,
                                                     QPen(Qt::black), QBrush(Qt::white));
    QGraphicsTextItem *text = scene->addText(QString::number(node->data));
    text->setPos(x - 7, y - 10);

    // Линии к детям
    if (node->leftPtr) {
        int childX = x - xOffset;
        int childY = y + spacingY;
        scene->addLine(x, y + radius, childX, childY - radius, QPen(Qt::black));
        drawNode(node->leftPtr, childX, childY, xOffset / 2);
    }
    if (node->rightPtr) {
        int childX = x + xOffset;
        int childY = y + spacingY;
        scene->addLine(x, y + radius, childX, childY - radius, QPen(Qt::black));
        drawNode(node->rightPtr, childX, childY, xOffset / 2);
    }
}