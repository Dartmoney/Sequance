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

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:

    void Arrabutclic();
    void Printbutclic();
private:
    void setupConnections();

    Ui::MainWindow *ui;
    Dynamic_array<string> ari;
    list<string> lsi;
};


#endif //UNTITLED4_MAINWINDOW_HPP
