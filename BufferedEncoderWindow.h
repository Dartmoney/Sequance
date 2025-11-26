//
// Created by imako on 24.11.2025.
//

#ifndef LABA3_BUFFEREDENCODERWINDOW_H
#define LABA3_BUFFEREDENCODERWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

class BufferedEncoderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BufferedEncoderWindow(QWidget *parent = nullptr);
    ~BufferedEncoderWindow() override = default;

private slots:
    void onEncodeClicked();

private:
    // Виджеты
    QTextEdit* inputEdit;        // исходные данные
    QSpinBox* bufferSizeSpin;    // размер буфера
    QTextEdit* outputEdit;       // результат кодирования
    QPushButton* encodeButton;   // кнопка
};

#endif //LABA3_BUFFEREDENCODERWINDOW_H