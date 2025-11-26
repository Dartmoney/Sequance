//
// Created by imako on 24.11.2025.
//

#ifndef LABA3_STREAMSTATSWINDOW_H
#define LABA3_STREAMSTATSWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

#include "StreamStatistics.h"   // наш класс статистики

class StreamStatsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StreamStatsWindow(QWidget *parent = nullptr);

private slots:
    void onCalculateClicked();

private:
    QWidget *central;
    QLineEdit *inputEdit;
    QPushButton *calcButton;

    QLabel *countLabel;
    QLabel *sumLabel;
    QLabel *meanLabel;
    QLabel *minLabel;
    QLabel *maxLabel;
};
#endif //LABA3_STREAMSTATSWINDOW_H