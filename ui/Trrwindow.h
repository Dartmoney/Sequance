/********************************************************************************
** Form generated from reading UI file 'Treewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TRRWINDOW_H
#define TRRWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLineEdit *lineEditInput;
    QPushButton *pushButtonInsert;
    QPushButton *pushButtonRemove;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonTraversal;
    QLabel *labelOutput;
    QPushButton *pushButtonGraphic;
    QWidget *webWidget;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(621, 455);
        lineEditInput = new QLineEdit(Form);
        lineEditInput->setObjectName("lineEditInput");
        lineEditInput->setGeometry(QRect(50, 20, 113, 21));
        pushButtonInsert = new QPushButton(Form);
        pushButtonInsert->setObjectName("pushButtonInsert");
        pushButtonInsert->setGeometry(QRect(50, 50, 111, 21));
        pushButtonRemove = new QPushButton(Form);
        pushButtonRemove->setObjectName("pushButtonRemove");
        pushButtonRemove->setGeometry(QRect(50, 80, 111, 24));
        pushButtonSearch = new QPushButton(Form);
        pushButtonSearch->setObjectName("pushButtonSearch");
        pushButtonSearch->setGeometry(QRect(50, 110, 111, 24));
        pushButtonClear = new QPushButton(Form);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(50, 140, 111, 24));
        pushButtonTraversal = new QPushButton(Form);
        pushButtonTraversal->setObjectName("pushButtonTraversal");
        pushButtonTraversal->setGeometry(QRect(50, 170, 111, 24));
        labelOutput = new QLabel(Form);
        labelOutput->setObjectName("labelOutput");
        labelOutput->setGeometry(QRect(20, 230, 131, 191));
        pushButtonGraphic = new QPushButton(Form);
        pushButtonGraphic->setObjectName("pushButtonGraphic");
        pushButtonGraphic->setGeometry(QRect(50, 200, 111, 24));
        webWidget = new QWidget(Form);
        webWidget->setObjectName("webWidget");
        webWidget->setGeometry(QRect(210, 20, 391, 421));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButtonInsert->setText(QCoreApplication::translate("Form", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButtonRemove->setText(QCoreApplication::translate("Form", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButtonSearch->setText(QCoreApplication::translate("Form", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("Form", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        pushButtonTraversal->setText(QCoreApplication::translate("Form", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \320\276\320\261\321\205\320\276\320\264", nullptr));
        labelOutput->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        pushButtonGraphic->setText(QCoreApplication::translate("Form", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\204\321\203\320\275\320\272\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TRRWINDOW_H
