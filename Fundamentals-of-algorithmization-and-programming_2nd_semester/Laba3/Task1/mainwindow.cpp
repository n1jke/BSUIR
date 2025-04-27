#include "mainwindow.h"
#include <QIntValidator>
#include <QPushButton>
#include <QVBoxLayout>

const int kWindowLengh = 300;
const int kWindowHeight = 150;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    auto* layout = new QVBoxLayout(central_widget);

    inputLineEdit_ = new QLineEdit(this);
    inputLineEdit_->setValidator(new QIntValidator(0, INT_MAX, this));
    inputLineEdit_->setPlaceholderText("Input integer");

    auto* convert_button = new QPushButton("Convert", this);

    resultLabel_ = new QLabel("Result", this);

    layout->addWidget(inputLineEdit_);
    layout->addWidget(convert_button);
    layout->addWidget(resultLabel_);

    connect(convert_button, &QPushButton::clicked, this,
            &MainWindow::convertToBinary);

    setMinimumSize(kWindowLengh, kWindowHeight);
}

MainWindow::~MainWindow() {}

QString MainWindow::decimalToBinary(int n) {


    if (n == 0) {
        return "0";
    }


    if (n == 1) {
        return "1";
    }

    return decimalToBinary(n / 2) + QString::number(n % 2);
}

void MainWindow::convertToBinary() {
    QString input = inputLineEdit_->text();
    if (input.isEmpty()) {
        resultLabel_->setText("Input integer");
        return;
    }

    bool ok;
    int number = input.toInt(&ok);


    if (!ok) {
        resultLabel_->setText("Input error");
        return;
    }

    QString binary = decimalToBinary(number);
    resultLabel_->setText("Binary representation: " + binary);
}
