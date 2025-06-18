//
// Created by islam on 01.05.2025.
//
#include "mainwindow.hpp"
#include <QMessageBox>
#include "Linked_List.hpp"
#include "Dynamic_array.hpp"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupConnections();
}

void MainWindow::Arrabutclic() {
    QString multiline = ui->textAllinput->toPlainText();
    printf("Add");
    ari.push_back(multiline.toStdString());
//    ui->PrintText->setText(multiline);
}

void MainWindow::Listbutclic() {
    QString multiline = ui->textAllinput->toPlainText();
    lsi.insertEnd(multiline.toStdString());
}

void MainWindow::printlistbutclic() {
    if (not lsi.isEmpty()) {
        QString minor;
        for (int i = 0; i < lsi.GetLength(); i++) {
            QString min = QString::fromStdString(lsi.Get(i));
            minor.push_back(min);
        }
        ui->PrintText->setText(minor);
    }
}

void MainWindow::on_toPage2Button_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_toPage1Button_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::SumBut1clic() {
    mel1[0] = ui->Mat_1_2num0->value();
    mel1[1] = ui->Mat_1_2num1->value();
    mel1[2] = ui->Mat_1_2num2->value();
    mel1[3] = ui->Mat_1_2num3->value();
    mel2[0] = ui->Mat_2_2num0->value();
    mel2[1] = ui->Mat_2_2num1->value();
    mel2[2] = ui->Mat_2_2num3->value();
    mel2[3] = ui->Mat_2_2num3_2->value();
    mel1 = mel1 + mel2;
    ui->Mat_1_2num0->setValue(mel1[0]);
    ui->Mat_1_2num1->setValue(mel1[1]);
    ui->Mat_1_2num2->setValue(mel1[2]);
    ui->Mat_1_2num3->setValue(mel1[3]);
}

void MainWindow::DifBut1clic() {
    mel1[0] = ui->Mat_1_2num0->value();
    mel1[1] = ui->Mat_1_2num1->value();
    mel1[2] = ui->Mat_1_2num2->value();
    mel1[3] = ui->Mat_1_2num3->value();
    mel2[0] = ui->Mat_2_2num0->value();
    mel2[1] = ui->Mat_2_2num1->value();
    mel2[2] = ui->Mat_2_2num3->value();
    mel2[3] = ui->Mat_2_2num3_2->value();
    mel2 = mel2 * -1;
    mel1 = mel1 + mel2;
    ui->Mat_1_2num0->setValue(mel1[0]);
    ui->Mat_1_2num1->setValue(mel1[1]);
    ui->Mat_1_2num2->setValue(mel1[2]);
    ui->Mat_1_2num3->setValue(mel1[3]);
}

void MainWindow::multBut1clic() {
    mel1[0] = ui->Mat_1_2num0->value();
    mel1[1] = ui->Mat_1_2num1->value();
    mel1[2] = ui->Mat_1_2num2->value();
    mel1[3] = ui->Mat_1_2num3->value();
    double k = ui->scalar1->value();
    mel1 = mel1 * k;
    ui->Mat_1_2num0->setValue(mel1[0]);
    ui->Mat_1_2num1->setValue(mel1[1]);
    ui->Mat_1_2num2->setValue(mel1[2]);
    ui->Mat_1_2num3->setValue(mel1[3]);
}

void MainWindow::normBut1clic() {
    mel1[0] = ui->Mat_1_2num0->value();
    mel1[1] = ui->Mat_1_2num1->value();
    mel1[2] = ui->Mat_1_2num2->value();
    mel1[3] = ui->Mat_1_2num3->value();
    double k = mel1.norm();
    ui->scalar1->setValue(k);
}

void MainWindow::SumBut2clic() {
    bol1[0] = ui->Mat_1_3num0->value();
    bol1[1] = ui->Mat_1_3num1->value();
    bol1[2] = ui->Mat_1_3num2->value();
    bol1[3] = ui->Mat_1_3num3->value();
    bol1[4] = ui->Mat_1_3num4->value();
    bol1[5] = ui->Mat_1_3num5->value();
    bol1[6] = ui->Mat_1_3num6->value();
    bol1[7] = ui->Mat_1_3num7->value();
    bol1[8] = ui->Mat_1_3num8->value();
    bol2[0] = ui->Mat_2_3num0->value();
    bol2[1] = ui->Mat_2_3num1->value();
    bol2[2] = ui->Mat_2_3num2->value();
    bol2[3] = ui->Mat_2_3num3->value();
    bol2[4] = ui->Mat_2_3num4->value();
    bol2[5] = ui->Mat_2_3num5->value();
    bol2[6] = ui->Mat_2_3num6->value();
    bol2[7] = ui->Mat_2_3num7->value();
    bol2[8] = ui->Mat_2_3num8->value();
    bol1 = bol1 + bol2;
    ui->Mat_1_3num0->setValue(bol1[0]);
    ui->Mat_1_3num1->setValue(bol1[1]);
    ui->Mat_1_3num2->setValue(bol1[2]);
    ui->Mat_1_3num3->setValue(bol1[3]);
    ui->Mat_1_3num4->setValue(bol1[4]);
    ui->Mat_1_3num5->setValue(bol1[5]);
    ui->Mat_1_3num6->setValue(bol1[6]);
    ui->Mat_1_3num7->setValue(bol1[7]);
    ui->Mat_1_3num8->setValue(bol1[8]);

}

void MainWindow::DifBut2clic() {
    bol1[0] = ui->Mat_1_3num0->value();
    bol1[1] = ui->Mat_1_3num1->value();
    bol1[2] = ui->Mat_1_3num2->value();
    bol1[3] = ui->Mat_1_3num3->value();
    bol1[4] = ui->Mat_1_3num4->value();
    bol1[5] = ui->Mat_1_3num5->value();
    bol1[6] = ui->Mat_1_3num6->value();
    bol1[7] = ui->Mat_1_3num7->value();
    bol1[8] = ui->Mat_1_3num8->value();
    bol2[0] = ui->Mat_2_3num0->value();
    bol2[1] = ui->Mat_2_3num1->value();
    bol2[2] = ui->Mat_2_3num2->value();
    bol2[3] = ui->Mat_2_3num3->value();
    bol2[4] = ui->Mat_2_3num4->value();
    bol2[5] = ui->Mat_2_3num5->value();
    bol2[6] = ui->Mat_2_3num6->value();
    bol2[7] = ui->Mat_2_3num7->value();
    bol2[8] = ui->Mat_2_3num8->value();
    bol2 = bol2 * -1;
    bol1 = bol1 + bol2;
    ui->Mat_1_3num0->setValue(bol1[0]);
    ui->Mat_1_3num1->setValue(bol1[1]);
    ui->Mat_1_3num2->setValue(bol1[2]);
    ui->Mat_1_3num3->setValue(bol1[3]);
    ui->Mat_1_3num4->setValue(bol1[4]);
    ui->Mat_1_3num5->setValue(bol1[5]);
    ui->Mat_1_3num6->setValue(bol1[6]);
    ui->Mat_1_3num7->setValue(bol1[7]);
    ui->Mat_1_3num8->setValue(bol1[8]);
}

void MainWindow::multBut2clic() {
    bol1[0] = ui->Mat_1_3num0->value();
    bol1[1] = ui->Mat_1_3num1->value();
    bol1[2] = ui->Mat_1_3num2->value();
    bol1[3] = ui->Mat_1_3num3->value();
    bol1[4] = ui->Mat_1_3num4->value();
    bol1[5] = ui->Mat_1_3num5->value();
    bol1[6] = ui->Mat_1_3num6->value();
    bol1[7] = ui->Mat_1_3num7->value();
    bol1[8] = ui->Mat_1_3num8->value();
    double k = ui->scalar2->value();
    bol1 = bol1 * k;
    ui->Mat_1_3num0->setValue(bol1[0]);
    ui->Mat_1_3num1->setValue(bol1[1]);
    ui->Mat_1_3num2->setValue(bol1[2]);
    ui->Mat_1_3num3->setValue(bol1[3]);
    ui->Mat_1_3num4->setValue(bol1[4]);
    ui->Mat_1_3num5->setValue(bol1[5]);
    ui->Mat_1_3num6->setValue(bol1[6]);
    ui->Mat_1_3num7->setValue(bol1[7]);
    ui->Mat_1_3num8->setValue(bol1[8]);;
}

void MainWindow::normBut2clic() {
    bol1[0] = ui->Mat_1_3num0->value();
    bol1[1] = ui->Mat_1_3num1->value();
    bol1[2] = ui->Mat_1_3num2->value();
    bol1[3] = ui->Mat_1_3num3->value();
    bol1[4] = ui->Mat_1_3num4->value();
    bol1[5] = ui->Mat_1_3num5->value();
    bol1[6] = ui->Mat_1_3num6->value();
    bol1[7] = ui->Mat_1_3num7->value();
    bol1[8] = ui->Mat_1_3num8->value();
    double k = bol1.norm();
    ui->scalar2->setValue(k);
}

void MainWindow::Printbutclic() {
    if (ari.size()) {
        QString minor;
        for (int i = 0; i < ari.size(); i++) {
            QString min = QString::fromStdString(ari[i]);
            minor.push_back(min);

        }
        ui->PrintText->setText(minor);
    }
}

void MainWindow::pushbuttreeclic() {
    treeWindow.show();
}

void MainWindow::setupConnections() {
    connect(
            ui->ButArray,
            &QPushButton::clicked,
            this,
            &MainWindow::Arrabutclic
    );
    connect(
            ui->Butprint,
            &QPushButton::clicked,
            this,
            &MainWindow::Printbutclic);
    connect(
            ui->printlistbut,
            &QPushButton::clicked,
            this,
            &MainWindow::printlistbutclic
    );
    connect(
            ui->ButSeq,
            &QPushButton::clicked,
            this,
            &MainWindow::Listbutclic
    );
    connect(ui->SumBut1,
            &QPushButton::clicked,
            this,
            &MainWindow::SumBut1clic
    );
    connect(ui->DifBut1,
            &QPushButton::clicked,
            this,
            &MainWindow::DifBut1clic
    );
    connect(ui->MultBut1,
            &QPushButton::clicked,
            this,
            &MainWindow::multBut1clic
    );
    connect(ui->NormBut1,
            &QPushButton::clicked,
            this,
            &MainWindow::normBut1clic
    );
    connect(ui->SumBut2,
            &QPushButton::clicked,
            this,
            &MainWindow::SumBut2clic
    );
    connect(ui->DifBut2,
            &QPushButton::clicked,
            this,
            &MainWindow::DifBut2clic
    );
    connect(ui->MultBut2,
            &QPushButton::clicked,
            this,
            &MainWindow::multBut2clic
    );
    connect(ui->NormBut2,
            &QPushButton::clicked,
            this,
            &MainWindow::normBut2clic
    );
    connect(ui->pushButtonTree, &QPushButton::clicked, this, &MainWindow::pushbuttreeclic);
}