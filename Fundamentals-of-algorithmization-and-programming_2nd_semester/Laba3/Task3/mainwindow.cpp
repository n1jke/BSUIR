#include "mainwindow.h"
#include <QIntValidator>
#include <QPushButton>
#include <QVBoxLayout>

const int kWindowLenght = 300;
const int kWindowHeight = 150;
const int kTen = 10;
const int kMaxNumber = 999999999;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    auto* layout = new QVBoxLayout(central_widget);

    inputLineEdit_ = new QLineEdit(this);
    inputLineEdit_->setValidator(new QIntValidator(1, kMaxNumber, this));
    inputLineEdit_->setPlaceholderText("Enter integer without zeros");

    auto* reverse_button = new QPushButton("Reverse", this);

    resultLabel_ = new QLabel("Result here", this);

    layout->addWidget(inputLineEdit_);
    layout->addWidget(reverse_button);
    layout->addWidget(resultLabel_);

    connect(reverse_button, &QPushButton::clicked, this,
            &MainWindow::reverseNumberSlot);

    setMinimumSize(kWindowLenght, kWindowHeight);
}

MainWindow::~MainWindow() {}


int reverseInteger(int n, int result = 0) {
    if (n == 0) {
        return result;
    }
    return reverseInteger(n / kTen, (result * kTen) + (n % kTen));
}


bool MainWindow::containsZero(int n) {


    if (n == 0) {
        return false;
    }


    if (n % kTen == 0) {
        return true;
    }

    return containsZero(n / kTen);
}


void MainWindow::reverseNumberSlot() {
    QString input = inputLineEdit_->text().trimmed();

    if (input.isEmpty()) {
        resultLabel_->setText("Введите число");
        return;
    }

    bool ok;
    int n = input.toInt(&ok);


    if (!ok || n <= 0) {
        resultLabel_->setText("Нужно положительное число");
        return;
    }

    if (containsZero(n)) {
        resultLabel_->setText("Читайте условие лабы)");
        return;
    }

    int result = reverseInteger(n);
    resultLabel_->setText(QString("Результат: %1").arg(result));
}
