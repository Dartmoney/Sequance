/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *PrintText;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *ButArray;
    QTextEdit *textAllinput;
    QPushButton *ButSeq;
    QLabel *label_2;
    QPushButton *Butprint;
    QPushButton *printlistbut;
    QPushButton *GetlsBut;
    QPushButton *GetarBut;
    QTextEdit *IndexText;
    QPushButton *toPage2Button;
    QWidget *page_2;
    QDoubleSpinBox *Mat_1_2num0;
    QDoubleSpinBox *Mat_1_2num2;
    QDoubleSpinBox *Mat_1_2num1;
    QDoubleSpinBox *Mat_1_2num3;
    QDoubleSpinBox *Mat_2_2num0;
    QDoubleSpinBox *Mat_2_2num3;
    QDoubleSpinBox *Mat_2_2num1;
    QDoubleSpinBox *Mat_2_2num3_2;
    QDoubleSpinBox *Mat_1_3num0;
    QDoubleSpinBox *Mat_1_3num3;
    QDoubleSpinBox *Mat_1_3num6;
    QDoubleSpinBox *Mat_1_3num1;
    QDoubleSpinBox *Mat_1_3num4;
    QDoubleSpinBox *Mat_1_3num7;
    QDoubleSpinBox *Mat_1_3num2;
    QDoubleSpinBox *Mat_1_3num5;
    QDoubleSpinBox *Mat_1_3num8;
    QDoubleSpinBox *Mat_2_3num0;
    QDoubleSpinBox *Mat_2_3num1;
    QDoubleSpinBox *Mat_2_3num2;
    QDoubleSpinBox *Mat_2_3num3;
    QDoubleSpinBox *Mat_2_3num4;
    QDoubleSpinBox *Mat_2_3num5;
    QDoubleSpinBox *Mat_2_3num6;
    QDoubleSpinBox *Mat_2_3num7;
    QDoubleSpinBox *Mat_2_3num8;
    QPushButton *SumBut1;
    QPushButton *DifBut1;
    QDoubleSpinBox *scalar1;
    QDoubleSpinBox *scalar2;
    QPushButton *MultBut1;
    QPushButton *MultBut2;
    QPushButton *SumBut2;
    QPushButton *DifBut2;
    QPushButton *NormBut1;
    QPushButton *NormBut2;
    QPushButton *toPage1Button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(968, 707);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(310, 120, 61, 20));
        PrintText = new QLabel(centralwidget);
        PrintText->setObjectName("PrintText");
        PrintText->setGeometry(QRect(190, 350, 311, 71));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 971, 681));
        page = new QWidget();
        page->setObjectName("page");
        ButArray = new QPushButton(page);
        ButArray->setObjectName("ButArray");
        ButArray->setGeometry(QRect(20, 10, 111, 41));
        textAllinput = new QTextEdit(page);
        textAllinput->setObjectName("textAllinput");
        textAllinput->setGeometry(QRect(40, 70, 411, 85));
        ButSeq = new QPushButton(page);
        ButSeq->setObjectName("ButSeq");
        ButSeq->setGeometry(QRect(350, 10, 121, 41));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(230, 200, 61, 20));
        Butprint = new QPushButton(page);
        Butprint->setObjectName("Butprint");
        Butprint->setGeometry(QRect(10, 190, 82, 29));
        printlistbut = new QPushButton(page);
        printlistbut->setObjectName("printlistbut");
        printlistbut->setGeometry(QRect(440, 200, 75, 24));
        GetlsBut = new QPushButton(page);
        GetlsBut->setObjectName("GetlsBut");
        GetlsBut->setGeometry(QRect(610, 130, 41, 29));
        GetarBut = new QPushButton(page);
        GetarBut->setObjectName("GetarBut");
        GetarBut->setGeometry(QRect(670, 130, 41, 31));
        IndexText = new QTextEdit(page);
        IndexText->setObjectName("IndexText");
        IndexText->setGeometry(QRect(610, 170, 104, 85));
        toPage2Button = new QPushButton(page);
        toPage2Button->setObjectName("toPage2Button");
        toPage2Button->setGeometry(QRect(550, 10, 31, 24));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        Mat_1_2num0 = new QDoubleSpinBox(page_2);
        Mat_1_2num0->setObjectName("Mat_1_2num0");
        Mat_1_2num0->setGeometry(QRect(40, 60, 31, 22));
        Mat_1_2num0->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_2num0->setMinimum(-10000.000000000000000);
        Mat_1_2num0->setMaximum(10000.000000000000000);
        Mat_1_2num2 = new QDoubleSpinBox(page_2);
        Mat_1_2num2->setObjectName("Mat_1_2num2");
        Mat_1_2num2->setGeometry(QRect(40, 90, 31, 22));
        Mat_1_2num2->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_2num2->setMinimum(-10000.000000000000000);
        Mat_1_2num2->setMaximum(10000.000000000000000);
        Mat_1_2num1 = new QDoubleSpinBox(page_2);
        Mat_1_2num1->setObjectName("Mat_1_2num1");
        Mat_1_2num1->setGeometry(QRect(90, 60, 31, 22));
        Mat_1_2num1->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_2num1->setMinimum(-10000.000000000000000);
        Mat_1_2num1->setMaximum(10000.000000000000000);
        Mat_1_2num3 = new QDoubleSpinBox(page_2);
        Mat_1_2num3->setObjectName("Mat_1_2num3");
        Mat_1_2num3->setGeometry(QRect(90, 90, 31, 22));
        Mat_1_2num3->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_2num3->setMinimum(-10000.000000000000000);
        Mat_1_2num3->setMaximum(10000.000000000000000);
        Mat_2_2num0 = new QDoubleSpinBox(page_2);
        Mat_2_2num0->setObjectName("Mat_2_2num0");
        Mat_2_2num0->setGeometry(QRect(180, 60, 31, 22));
        Mat_2_2num0->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_2num0->setMinimum(-10000.000000000000000);
        Mat_2_2num0->setMaximum(10000.000000000000000);
        Mat_2_2num3 = new QDoubleSpinBox(page_2);
        Mat_2_2num3->setObjectName("Mat_2_2num3");
        Mat_2_2num3->setGeometry(QRect(180, 90, 31, 22));
        Mat_2_2num3->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_2num3->setMinimum(-10000.000000000000000);
        Mat_2_2num3->setMaximum(10000.000000000000000);
        Mat_2_2num1 = new QDoubleSpinBox(page_2);
        Mat_2_2num1->setObjectName("Mat_2_2num1");
        Mat_2_2num1->setGeometry(QRect(220, 60, 31, 22));
        Mat_2_2num1->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_2num1->setMinimum(-10000.000000000000000);
        Mat_2_2num1->setMaximum(10000.000000000000000);
        Mat_2_2num3_2 = new QDoubleSpinBox(page_2);
        Mat_2_2num3_2->setObjectName("Mat_2_2num3_2");
        Mat_2_2num3_2->setGeometry(QRect(220, 90, 31, 22));
        Mat_2_2num3_2->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_2num3_2->setMinimum(-10000.000000000000000);
        Mat_2_2num3_2->setMaximum(10000.000000000000000);
        Mat_1_3num0 = new QDoubleSpinBox(page_2);
        Mat_1_3num0->setObjectName("Mat_1_3num0");
        Mat_1_3num0->setGeometry(QRect(10, 340, 31, 22));
        Mat_1_3num0->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num0->setMinimum(-10000.000000000000000);
        Mat_1_3num0->setMaximum(10000.000000000000000);
        Mat_1_3num3 = new QDoubleSpinBox(page_2);
        Mat_1_3num3->setObjectName("Mat_1_3num3");
        Mat_1_3num3->setGeometry(QRect(10, 370, 31, 22));
        Mat_1_3num3->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num3->setMinimum(-10000.000000000000000);
        Mat_1_3num3->setMaximum(10000.000000000000000);
        Mat_1_3num6 = new QDoubleSpinBox(page_2);
        Mat_1_3num6->setObjectName("Mat_1_3num6");
        Mat_1_3num6->setGeometry(QRect(10, 400, 31, 22));
        Mat_1_3num6->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num6->setMinimum(-10000.000000000000000);
        Mat_1_3num6->setMaximum(10000.000000000000000);
        Mat_1_3num1 = new QDoubleSpinBox(page_2);
        Mat_1_3num1->setObjectName("Mat_1_3num1");
        Mat_1_3num1->setGeometry(QRect(50, 340, 31, 22));
        Mat_1_3num1->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num1->setMinimum(-10000.000000000000000);
        Mat_1_3num1->setMaximum(10000.000000000000000);
        Mat_1_3num4 = new QDoubleSpinBox(page_2);
        Mat_1_3num4->setObjectName("Mat_1_3num4");
        Mat_1_3num4->setGeometry(QRect(50, 370, 31, 22));
        Mat_1_3num4->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num4->setMinimum(-10000.000000000000000);
        Mat_1_3num4->setMaximum(10000.000000000000000);
        Mat_1_3num7 = new QDoubleSpinBox(page_2);
        Mat_1_3num7->setObjectName("Mat_1_3num7");
        Mat_1_3num7->setGeometry(QRect(50, 400, 31, 22));
        Mat_1_3num7->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num7->setMinimum(-10000.000000000000000);
        Mat_1_3num7->setMaximum(10000.000000000000000);
        Mat_1_3num2 = new QDoubleSpinBox(page_2);
        Mat_1_3num2->setObjectName("Mat_1_3num2");
        Mat_1_3num2->setGeometry(QRect(90, 340, 31, 22));
        Mat_1_3num2->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num2->setMinimum(-10000.000000000000000);
        Mat_1_3num2->setMaximum(10000.000000000000000);
        Mat_1_3num5 = new QDoubleSpinBox(page_2);
        Mat_1_3num5->setObjectName("Mat_1_3num5");
        Mat_1_3num5->setGeometry(QRect(90, 370, 31, 22));
        Mat_1_3num5->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num5->setMinimum(-10000.000000000000000);
        Mat_1_3num5->setMaximum(10000.000000000000000);
        Mat_1_3num8 = new QDoubleSpinBox(page_2);
        Mat_1_3num8->setObjectName("Mat_1_3num8");
        Mat_1_3num8->setGeometry(QRect(90, 400, 31, 22));
        Mat_1_3num8->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_1_3num8->setMinimum(-10000.000000000000000);
        Mat_1_3num8->setMaximum(10000.000000000000000);
        Mat_2_3num0 = new QDoubleSpinBox(page_2);
        Mat_2_3num0->setObjectName("Mat_2_3num0");
        Mat_2_3num0->setGeometry(QRect(170, 340, 31, 22));
        Mat_2_3num0->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num0->setMinimum(-10000.000000000000000);
        Mat_2_3num0->setMaximum(10000.000000000000000);
        Mat_2_3num1 = new QDoubleSpinBox(page_2);
        Mat_2_3num1->setObjectName("Mat_2_3num1");
        Mat_2_3num1->setGeometry(QRect(210, 340, 31, 22));
        Mat_2_3num1->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num1->setMinimum(-10000.000000000000000);
        Mat_2_3num1->setMaximum(10000.000000000000000);
        Mat_2_3num2 = new QDoubleSpinBox(page_2);
        Mat_2_3num2->setObjectName("Mat_2_3num2");
        Mat_2_3num2->setGeometry(QRect(250, 340, 31, 22));
        Mat_2_3num2->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num2->setMinimum(-10000.000000000000000);
        Mat_2_3num2->setMaximum(10000.000000000000000);
        Mat_2_3num3 = new QDoubleSpinBox(page_2);
        Mat_2_3num3->setObjectName("Mat_2_3num3");
        Mat_2_3num3->setGeometry(QRect(170, 370, 31, 22));
        Mat_2_3num3->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num3->setMinimum(-10000.000000000000000);
        Mat_2_3num3->setMaximum(10000.000000000000000);
        Mat_2_3num4 = new QDoubleSpinBox(page_2);
        Mat_2_3num4->setObjectName("Mat_2_3num4");
        Mat_2_3num4->setGeometry(QRect(210, 370, 31, 22));
        Mat_2_3num4->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num4->setMinimum(-10000.000000000000000);
        Mat_2_3num4->setMaximum(10000.000000000000000);
        Mat_2_3num5 = new QDoubleSpinBox(page_2);
        Mat_2_3num5->setObjectName("Mat_2_3num5");
        Mat_2_3num5->setGeometry(QRect(250, 370, 31, 22));
        Mat_2_3num5->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num5->setMinimum(-10000.000000000000000);
        Mat_2_3num5->setMaximum(10000.000000000000000);
        Mat_2_3num6 = new QDoubleSpinBox(page_2);
        Mat_2_3num6->setObjectName("Mat_2_3num6");
        Mat_2_3num6->setGeometry(QRect(170, 400, 31, 22));
        Mat_2_3num6->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num6->setMinimum(-10000.000000000000000);
        Mat_2_3num6->setMaximum(10000.000000000000000);
        Mat_2_3num7 = new QDoubleSpinBox(page_2);
        Mat_2_3num7->setObjectName("Mat_2_3num7");
        Mat_2_3num7->setGeometry(QRect(210, 400, 31, 22));
        Mat_2_3num7->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num7->setMinimum(-10000.000000000000000);
        Mat_2_3num7->setMaximum(10000.000000000000000);
        Mat_2_3num8 = new QDoubleSpinBox(page_2);
        Mat_2_3num8->setObjectName("Mat_2_3num8");
        Mat_2_3num8->setGeometry(QRect(250, 400, 31, 22));
        Mat_2_3num8->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Mat_2_3num8->setMinimum(-10000.000000000000000);
        Mat_2_3num8->setMaximum(10000.000000000000000);
        SumBut1 = new QPushButton(page_2);
        SumBut1->setObjectName("SumBut1");
        SumBut1->setGeometry(QRect(130, 60, 31, 24));
        DifBut1 = new QPushButton(page_2);
        DifBut1->setObjectName("DifBut1");
        DifBut1->setGeometry(QRect(130, 90, 31, 24));
        scalar1 = new QDoubleSpinBox(page_2);
        scalar1->setObjectName("scalar1");
        scalar1->setGeometry(QRect(70, 140, 31, 22));
        scalar1->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        scalar1->setMinimum(-10000.000000000000000);
        scalar1->setMaximum(10000.000000000000000);
        scalar2 = new QDoubleSpinBox(page_2);
        scalar2->setObjectName("scalar2");
        scalar2->setGeometry(QRect(50, 460, 31, 22));
        scalar2->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        scalar2->setMinimum(-10000.000000000000000);
        scalar2->setMaximum(10000.000000000000000);
        MultBut1 = new QPushButton(page_2);
        MultBut1->setObjectName("MultBut1");
        MultBut1->setGeometry(QRect(70, 120, 21, 20));
        MultBut2 = new QPushButton(page_2);
        MultBut2->setObjectName("MultBut2");
        MultBut2->setGeometry(QRect(50, 430, 21, 21));
        SumBut2 = new QPushButton(page_2);
        SumBut2->setObjectName("SumBut2");
        SumBut2->setGeometry(QRect(130, 340, 31, 24));
        DifBut2 = new QPushButton(page_2);
        DifBut2->setObjectName("DifBut2");
        DifBut2->setGeometry(QRect(130, 390, 31, 24));
        NormBut1 = new QPushButton(page_2);
        NormBut1->setObjectName("NormBut1");
        NormBut1->setGeometry(QRect(20, 140, 41, 21));
        NormBut2 = new QPushButton(page_2);
        NormBut2->setObjectName("NormBut2");
        NormBut2->setGeometry(QRect(90, 460, 41, 24));
        toPage1Button = new QPushButton(page_2);
        toPage1Button->setObjectName("toPage1Button");
        toPage1Button->setGeometry(QRect(20, 0, 31, 24));
        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 968, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", nullptr));
        PrintText->setText(QString());
        ButArray->setText(QCoreApplication::translate("MainWindow", "ArraySequance", nullptr));
        ButSeq->setText(QCoreApplication::translate("MainWindow", "ListSequance", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\262\321\213\320\262\320\276\320\264l", nullptr));
        Butprint->setText(QCoreApplication::translate("MainWindow", "printar", nullptr));
        printlistbut->setText(QCoreApplication::translate("MainWindow", "printlist", nullptr));
        GetlsBut->setText(QCoreApplication::translate("MainWindow", "Getls", nullptr));
        GetarBut->setText(QCoreApplication::translate("MainWindow", "Getar", nullptr));
        toPage2Button->setText(QCoreApplication::translate("MainWindow", "->", nullptr));
        SumBut1->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        DifBut1->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        MultBut1->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        MultBut2->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        SumBut2->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        DifBut2->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        NormBut1->setText(QCoreApplication::translate("MainWindow", "norm", nullptr));
        NormBut2->setText(QCoreApplication::translate("MainWindow", "norm", nullptr));
        toPage1Button->setText(QCoreApplication::translate("MainWindow", "<-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
