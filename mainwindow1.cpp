#include "mainwindow1.h"
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QLabel *label = new QLabel("Enter f(i) and length:");
    inputFormula = new QLineEdit();
    inputFormula->setPlaceholderText("Example: i*i + 2");

    inputLength = new QLineEdit();
    inputLength->setPlaceholderText("Length (e.g. 10)");

    generateBtn = new QPushButton("Generate");
    nextBtn = new QPushButton("Evaluate next");
    nextBtn->setEnabled(false);

    listWidget = new QListWidget();

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(inputFormula);
    topLayout->addWidget(inputLength);
    topLayout->addWidget(generateBtn);

    mainLayout->addWidget(label);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(nextBtn);

    setCentralWidget(central);
    setWindowTitle("Lazy Sequence Viewer");

    connect(generateBtn, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
    connect(nextBtn, &QPushButton::clicked, this, &MainWindow::onNextClicked);
}

MainWindow::~MainWindow() {
}

std::function<int(int)> MainWindow::parseFormula(const QString &expr) {
    // простейший парсер арифметических выражений с i
    QString e = expr;
    return [e](int i) -> int {
        QString s = e;
        s.replace("i", QString::number(i));
        // !!! ОЧЕНЬ простая версия — использует встроенный JS движок через QJSEngine
        QJSEngine engine;
        QJSValue result = engine.evaluate(s);
        if (result.isError())
            throw std::runtime_error("Invalid expression");
        return result.toInt();
    };
}

void MainWindow::onGenerateClicked() {
    QString expr = inputFormula->text().trimmed();
    bool ok;
    int len = inputLength->text().toInt(&ok);

    if (!ok || len <= 0) {
        QMessageBox::warning(this, "Error", "Invalid length");
        return;
    }

    try {
        auto func = parseFormula(expr);
        sequence = std::make_unique<LazySequence<int> >(func, len);
        listWidget->clear();
        currentIndex = 0;
        nextBtn->setEnabled(true);
    } catch (...) {
        QMessageBox::critical(this, "Error", "Failed to parse formula");
    }
}

void MainWindow::onNextClicked() {
    if (!sequence) return;
    if (currentIndex >= sequence->GetLength()) {
        QMessageBox::information(this, "End", "All elements computed.");
        return;
    }

    try {
        int val = sequence->Get(currentIndex);
        listWidget->addItem(QString("f(%1) = %2").arg(currentIndex).arg(val));
        currentIndex++;
    } catch (...) {
        QMessageBox::critical(this, "Error", "Failed to evaluate element");
    }
}
