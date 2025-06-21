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
#include "Tree_to_html.hpp"
#include <cstdlib>

TreeWindow::TreeWindow(QWidget *parent) : QMainWindow(parent), tree(), ui(new Ui::Form) {
    ui->setupUi(this);
    setupConnections();
}

void TreeWindow::Insertbutclic() {
    QString st = ui->lineEditInput->text();
    int s = st.toInt();
    tree.insertNewNode(s);
}

void TreeWindow::clearbutclic() {
    tree.clear();
}

void TreeWindow::searchbutclic() {
    QString st = ui->lineEditInput->text();
    TreeNode<int> *found = tree.search(st.toInt());
    if (found) {
        ui->labelOutput->setText("Найдено");
    } else {
        ui->labelOutput->setText("Не найдено");
    }
}

void TreeWindow::drawGraphic() {
    std::system("start C:/Users/islam/CLionProjects/untitled4/graphik.html");
}

void TreeWindow::drawTree() {
//    Dynamic_array<int> t;
//    t = tree.rootRightLeftPrint();
//    Tree<int> min;
//    for (int v = 0; v < t.size(); v++) {
//        printf("%d",t[v]);
//        min.insertNewNode(t[v]);
//    }

    tree.saveToHTML("C:/Users/islam/CLionProjects/untitled4/tr.html");
    std::system("start C:/Users/islam/CLionProjects/untitled4/tr.html");
}

//
//void TreeWindow::drawTree() {
//    if (!tree || tree->isEmpty()) return;
//    TreeNode<int> *root = tree->getRoot();
//    drawNode(root, 0, 0, 300);  // начальные координаты и горизонтальное смещение
//}
//
//void TreeWindow::drawNode(TreeNode<int> *node, int x, int y, int xOffset) {
//    if (!node) return;
//
//    int radius = 20;
//    int spacingY = 80;
//
//    // Нарисовать узел
//    QGraphicsEllipseItem *circle = scene->addEllipse(x - radius, y - radius, 2 * radius, 2 * radius,
//                                                     QPen(Qt::black), QBrush(Qt::white));
//    QGraphicsTextItem *text = scene->addText(QString::number(node->data));
//    text->setPos(x - 7, y - 10);
//
//    // Линии к детям
//    if (node->leftPtr) {
//        int childX = x - xOffset;
//        int childY = y + spacingY;
//        scene->addLine(x, y + radius, childX, childY - radius, QPen(Qt::black));
//        drawNode(node->leftPtr, childX, childY, xOffset / 2);
//    }
//    if (node->rightPtr) {
//        int childX = x + xOffset;
//        int childY = y + spacingY;
//        scene->addLine(x, y + radius, childX, childY - radius, QPen(Qt::black));
//        drawNode(node->rightPtr, childX, childY, xOffset / 2);
//    }
//}
//void TreeWindow::drawTree() {
////    ui->textBrowser->setSource(QUrl::fromLocalFile("C:/Users/islam/CLionProjects/untitled4/tr.html"));
////    ui->textBrowser->setOpenExternalLinks(true);
////    ui->textBrowser->show();
//
//}

void TreeWindow::setupConnections() {
//    connect(ui->pushButtonGraphic,
//            &QPushButton::clicked,
//            this,
//            &TreeWindow::drawTree);
    connect(ui->pushButtonInsert,
            &QPushButton::clicked,
            this,
            &TreeWindow::Insertbutclic);

    connect(ui->pushButtonClear,
            &QPushButton::clicked,
            this,
            &TreeWindow::clearbutclic);
    connect(ui->pushButtonSearch,
            &QPushButton::clicked,
            this,
            &TreeWindow::searchbutclic);
    connect(ui->pushButtonTraversal,
            &QPushButton::clicked,
            this,
            &TreeWindow::drawTree);
    connect(ui->pushButtonGraphic,
            &QPushButton::clicked,
            this,
            &TreeWindow::drawGraphic);
}