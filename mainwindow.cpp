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
}