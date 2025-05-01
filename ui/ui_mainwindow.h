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
    QTextEdit *textinputend;
    QPushButton *ButInputEnd;
    QPushButton *Butprint;
    QTextEdit *IndexText;
    QPushButton *GetBut;
    QLabel *PrintText;
    QPushButton *GetFBut;
    QPushButton *GetEBut;
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
        textinputend = new QTextEdit(centralwidget);
        textinputend->setObjectName("textinputend");
        textinputend->setGeometry(QRect(630, 230, 104, 85));
        ButInputEnd = new QPushButton(centralwidget);
        ButInputEnd->setObjectName("ButInputEnd");
        ButInputEnd->setGeometry(QRect(640, 180, 82, 29));
        Butprint = new QPushButton(centralwidget);
        Butprint->setObjectName("Butprint");
        Butprint->setGeometry(QRect(160, 280, 82, 29));
        IndexText = new QTextEdit(centralwidget);
        IndexText->setObjectName("IndexText");
        IndexText->setGeometry(QRect(630, 370, 104, 85));
        GetBut = new QPushButton(centralwidget);
        GetBut->setObjectName("GetBut");
        GetBut->setGeometry(QRect(640, 330, 82, 29));
        PrintText = new QLabel(centralwidget);
        PrintText->setObjectName("PrintText");
        PrintText->setGeometry(QRect(190, 350, 311, 71));
        GetFBut = new QPushButton(centralwidget);
        GetFBut->setObjectName("GetFBut");
        GetFBut->setGeometry(QRect(20, 320, 82, 29));
        GetEBut = new QPushButton(centralwidget);
        GetEBut->setObjectName("GetEBut");
        GetEBut->setGeometry(QRect(20, 370, 82, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 968, 25));
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
        ButInputEnd->setText(QCoreApplication::translate("MainWindow", "input", nullptr));
        Butprint->setText(QCoreApplication::translate("MainWindow", "print", nullptr));
        GetBut->setText(QCoreApplication::translate("MainWindow", "Get", nullptr));
        PrintText->setText(QString());
        GetFBut->setText(QCoreApplication::translate("MainWindow", "GetFirst", nullptr));
        GetEBut->setText(QCoreApplication::translate("MainWindow", "GetEnd", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
