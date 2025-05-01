#include <QApplication>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include <QWidget>
#include <QUiLoader>
#include "mainwindow.hpp"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
