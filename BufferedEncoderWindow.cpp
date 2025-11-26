#include "BufferedEncoderWindow.h"
#include "Stream.h"             // здесь лежат StringReadOnlyStream / StringWriteOnlyStream
#include "BufferedCharEncoder.h" // здесь твой класс кодировщика

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

BufferedEncoderWindow::BufferedEncoderWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    auto *inputLabel = new QLabel("Исходная строка:", central);
    inputEdit = new QTextEdit(central);

    auto *bufferLayout = new QHBoxLayout();
    auto *bufferLabel = new QLabel("Размер буфера:", central);
    bufferSizeSpin = new QSpinBox(central);
    bufferSizeSpin->setMinimum(1);
    bufferSizeSpin->setMaximum(1'000'000);
    bufferSizeSpin->setValue(4);

    bufferLayout->addWidget(bufferLabel);
    bufferLayout->addWidget(bufferSizeSpin);

    encodeButton = new QPushButton("Закодировать", central);
    connect(encodeButton, &QPushButton::clicked,
            this, &BufferedEncoderWindow::onEncodeClicked);

    auto *outputLabel = new QLabel("Результат кодирования:", central);
    outputEdit = new QTextEdit(central);
    outputEdit->setReadOnly(true);

    mainLayout->addWidget(inputLabel);
    mainLayout->addWidget(inputEdit);
    mainLayout->addLayout(bufferLayout);
    mainLayout->addWidget(encodeButton);
    mainLayout->addWidget(outputLabel);
    mainLayout->addWidget(outputEdit);

    setCentralWidget(central);
    setWindowTitle("Buffered Char Encoder");
    resize(600, 400);
}

void BufferedEncoderWindow::onEncodeClicked()
{
    QString inputText = inputEdit->toPlainText();
    int bufferSize = bufferSizeSpin->value();

    std::string inputStd = inputText.toStdString();

    StringReadOnlyStream in(inputStd);
    StringWriteOnlyStream out;

    try {
        BufferedCharEncoder encoder(bufferSize);
        encoder.Encode(in, out);

        std::string encoded = out.GetResult();
        outputEdit->setPlainText(QString::fromStdString(encoded));
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Ошибка", QString::fromUtf8(ex.what()));
    }
}