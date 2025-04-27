#include "mainwindow.h"
#include <QIntValidator>
#include <QPushButton>
#include <QVBoxLayout>

const int kWindowLenght = 400;
const int kWindowHeight = 300;
const int kSix = 6;
const int kFifteen = 15;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    auto* layout = new QVBoxLayout(central_widget);

    inputLineEdit_ = new QLineEdit(this);
    inputLineEdit_->setValidator(new QIntValidator(1, kFifteen, this));
    inputLineEdit_->setPlaceholderText("Enter disk counts(1-15)");

    auto* solve_button = new QPushButton("Solve", this);

    resultTextEdit_ = new QTextEdit(this);
    resultTextEdit_->setReadOnly(true);
    resultTextEdit_->setText("Steps will here:");

    layout->addWidget(inputLineEdit_);
    layout->addWidget(solve_button);
    layout->addWidget(resultTextEdit_);

    connect(solve_button, &QPushButton::clicked, this, &MainWindow::solveHanoi);

    setMinimumSize(kWindowLenght, kWindowHeight);
}

MainWindow::~MainWindow() {}


void MainWindow::hanoiRecursion(int count, int prevPeg, int newPeg,
                                QString& steps) {


    if (count <= 0) {
        return;
    }


    if (count == 1) {
        steps += QString("Move disk from %1 to %2.\n").arg(prevPeg).arg(newPeg);
        return;
    }

    int un_used_peg = kSix - prevPeg - newPeg;
    hanoiRecursion(count - 1, prevPeg, un_used_peg, steps);
    steps += QString("Move disk from %1 to %2.\n").arg(prevPeg).arg(newPeg);
    hanoiRecursion(count - 1, un_used_peg, newPeg, steps);
}


void MainWindow::solveHanoi() {
    QString input = inputLineEdit_->text().trimmed();

    if (input.isEmpty()) {
        resultTextEdit_->setText("Enter disk count: ");
        return;
    }

    bool ok;
    int n = input.toInt(&ok);


    if (!ok || n <= 0) {
        resultTextEdit_->setText("Need positive integer)");
        return;
    }

    QString steps;
    hanoiRecursion(n, 1, 3, steps);
    resultTextEdit_->setText(steps);
}
