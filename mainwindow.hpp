//
// Created by islam on 01.05.2025.
//

#ifndef UNTITLED4_MAINWINDOW_HPP
#define UNTITLED4_MAINWINDOW_HPP
#pragma once

#include <QMessageBox>
#include <QWidget>
#include "ui/ui_mainwindow.h"
#include "Linked_List.hpp"
#include "Dynamic_array.hpp"
#include "Matrix.hpp"
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override {
        delete ui; // Добавьте, если его нет
    }
private slots:
    void Arrabutclic();
    void Printbutclic();
    void Listbutclic();
    void printlistbutclic();
    void on_toPage2Button_clicked();
    void on_toPage1Button_clicked();
    void SumBut1clic();
    void DifBut1clic();
    void multBut1clic();
    void normBut1clic();
    void SumBut2clic();
    void DifBut2clic();
    void multBut2clic();
    void normBut2clic();
private:
    void setupConnections();
    Matrix<double> mel1 = Matrix<double>(2);
    Matrix<double> mel2 = Matrix<double>(2);
    Matrix<double> bol1 = Matrix<double>(3);
    Matrix<double> bol2 = Matrix<double>(3);
    Ui::MainWindow *ui;
    Dynamic_array<string> ari;
    List<string> lsi;
};


#endif //UNTITLED4_MAINWINDOW_HPP
