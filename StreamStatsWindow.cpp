#include "StreamStatsWindow.h"

StreamStatsWindow::StreamStatsWindow(QWidget *parent)
        : QMainWindow(parent)
{
    central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout;

    inputEdit = new QLineEdit;
    inputEdit->setPlaceholderText("Введите строку для анализа...");

    calcButton = new QPushButton("Посчитать статистику");

    countLabel = new QLabel("Count: -");
    sumLabel   = new QLabel("Sum: -");
    meanLabel  = new QLabel("Mean: -");
    minLabel   = new QLabel("Min: -");
    maxLabel   = new QLabel("Max: -");

    auto *formLayout = new QFormLayout;
    formLayout->addRow("Кол-во символов:", countLabel);
    formLayout->addRow("Сумма кодов:",      sumLabel);
    formLayout->addRow("Среднее значение:", meanLabel);
    formLayout->addRow("Минимум:",          minLabel);
    formLayout->addRow("Максимум:",         maxLabel);

    mainLayout->addWidget(inputEdit);
    mainLayout->addWidget(calcButton);
    mainLayout->addLayout(formLayout);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    setWindowTitle("Статистика потока символов");

    connect(calcButton, &QPushButton::clicked,
            this, &StreamStatsWindow::onCalculateClicked);
}
void StreamStatsWindow::onCalculateClicked()
{
    QString text = inputEdit->text();
    std::string data = text.toStdString();

    StringStreamStatistics stats(data);
    stats.ConsumeAll();

    countLabel->setText(QString::number(
            static_cast<qint64>(stats.GetCount())
    ));

    sumLabel->setText(QString::number(
            static_cast<qint64>(stats.GetSum())
    ));

    if (stats.GetCount() == 0) {
        meanLabel->setText("-");
        minLabel->setText("-");
        maxLabel->setText("-");
        return;
    }

    long double mean = stats.GetMean();
    char minCh = stats.GetMin();
    char maxCh = stats.GetMax();

    // здесь явно приводим к double и задаём формат
    meanLabel->setText(QString::number(
            static_cast<double>(mean), 'f', 3
    ));

    minLabel->setText(QString("%1 (code %2)")
                              .arg(QChar(minCh))
                              .arg(static_cast<int>(
                                      static_cast<unsigned char>(minCh)
                              )));

    maxLabel->setText(QString("%1 (code %2)")
                              .arg(QChar(maxCh))
                              .arg(static_cast<int>(
                                      static_cast<unsigned char>(maxCh)
                              )));
}