//
// Created by islam on 01.05.2025.
//
#include "mainwindow.hpp"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupConnections();
}

void MainWindow::Arrabutclic() {
    QString multiline = ui->textAllinput->toPlainText();
    QList<QString> cd = multiline.split(" ");

    for (int i = 0; i < sizeof(cd); i++)
        ari.push_back(cd.value(i).toStdString());
//    ui->PrintText->setText(multiline);
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
}