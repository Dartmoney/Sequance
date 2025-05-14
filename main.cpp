#include <QApplication>
#include <QPushButton>
#include "mainwindow.hpp"
#include "Dynamic_array.hpp"
#include "Linked_List.hpp"
//#include "All_test.hpp"
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
}
