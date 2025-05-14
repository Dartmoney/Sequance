/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *ButArray;
    QPushButton *ButSeq;
    QTextEdit *textAllinput;
    QLabel *label;
    QLabel *label_2;
    QPushButton *Butprint;
    QTextEdit *IndexText;
    QPushButton *GetlsBut;
    QLabel *PrintText;
    QPushButton *GetFarBut;
    QPushButton *GetEarBut;
    QPushButton *printlistbut;
    QPushButton *GetarBut;
    QPushButton *GetFirst_lsBut;
    QPushButton *GetEndarBut;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(968, 707);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ButArray = new QPushButton(centralwidget);
        ButArray->setObjectName("ButArray");
        ButArray->setGeometry(QRect(50, 60, 111, 41));
        ButSeq = new QPushButton(centralwidget);
        ButSeq->setObjectName("ButSeq");
        ButSeq->setGeometry(QRect(540, 60, 121, 41));
        textAllinput = new QTextEdit(centralwidget);
        textAllinput->setObjectName("textAllinput");
        textAllinput->setGeometry(QRect(160, 150, 411, 85));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(310, 120, 61, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(330, 280, 61, 20));
        Butprint = new QPushButton(centralwidget);
        Butprint->setObjectName("Butprint");
        Butprint->setGeometry(QRect(160, 280, 82, 29));
        IndexText = new QTextEdit(centralwidget);
        IndexText->setObjectName("IndexText");
        IndexText->setGeometry(QRect(630, 370, 104, 85));
        GetlsBut = new QPushButton(centralwidget);
        GetlsBut->setObjectName("GetlsBut");
        GetlsBut->setGeometry(QRect(630, 330, 41, 29));
        PrintText = new QLabel(centralwidget);
        PrintText->setObjectName("PrintText");
        PrintText->setGeometry(QRect(190, 350, 311, 71));
        GetFarBut = new QPushButton(centralwidget);
        GetFarBut->setObjectName("GetFarBut");
        GetFarBut->setGeometry(QRect(20, 320, 71, 29));
        GetEarBut = new QPushButton(centralwidget);
        GetEarBut->setObjectName("GetEarBut");
        GetEarBut->setGeometry(QRect(20, 370, 71, 29));
        printlistbut = new QPushButton(centralwidget);
        printlistbut->setObjectName("printlistbut");
        printlistbut->setGeometry(QRect(460, 280, 75, 24));
        GetarBut = new QPushButton(centralwidget);
        GetarBut->setObjectName("GetarBut");
        GetarBut->setGeometry(QRect(680, 330, 41, 31));
        GetFirst_lsBut = new QPushButton(centralwidget);
        GetFirst_lsBut->setObjectName("GetFirst_lsBut");
        GetFirst_lsBut->setGeometry(QRect(110, 320, 71, 31));
        GetEndarBut = new QPushButton(centralwidget);
        GetEndarBut->setObjectName("GetEndarBut");
        GetEndarBut->setGeometry(QRect(110, 370, 71, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 968, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ButArray->setText(QCoreApplication::translate("MainWindow", "ArraySequance", nullptr));
        ButSeq->setText(QCoreApplication::translate("MainWindow", "ListSequance", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\262\321\213\320\262\320\276\320\264l", nullptr));
        Butprint->setText(QCoreApplication::translate("MainWindow", "printar", nullptr));
        GetlsBut->setText(QCoreApplication::translate("MainWindow", "Getls", nullptr));
        PrintText->setText(QString());
        GetFarBut->setText(QCoreApplication::translate("MainWindow", "GetFirst_ar", nullptr));
        GetEarBut->setText(QCoreApplication::translate("MainWindow", "GetEnd_ar", nullptr));
        printlistbut->setText(QCoreApplication::translate("MainWindow", "printlist", nullptr));
        GetarBut->setText(QCoreApplication::translate("MainWindow", "Getar", nullptr));
        GetFirst_lsBut->setText(QCoreApplication::translate("MainWindow", "GetFirst_ls", nullptr));
        GetEndarBut->setText(QCoreApplication::translate("MainWindow", "GetEnd_ar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
