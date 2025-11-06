#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include "lazy_sequence.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGenerateClicked();
    void onNextClicked();

private:
    QLineEdit *inputFormula;
    QLineEdit *inputLength;
    QPushButton *generateBtn;
    QPushButton *nextBtn;
    QListWidget *listWidget;

    std::unique_ptr<LazySequence<int>> sequence;
    int currentIndex = 0;

    std::function<int(int)> parseFormula(const QString &expr);
};

#endif // MAINWINDOW1_H
