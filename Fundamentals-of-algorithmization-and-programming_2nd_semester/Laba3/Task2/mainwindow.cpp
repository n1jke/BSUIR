#include "mainwindow.h"
#include <QIntValidator>
#include <QPushButton>
#include <QVBoxLayout>

const int kWindowLength = 300;
const int kWindowHeight = 200;
const int kMaxM = 3;
const int kMaxN = 10;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    auto* layout = new QVBoxLayout(central_widget);

    mLineEdit_ = new QLineEdit(this);
    mLineEdit_->setValidator(new QIntValidator(0, kMaxM, this));
    mLineEdit_->setPlaceholderText("Input m >= 0");

    nLineEdit_ = new QLineEdit(this);
    nLineEdit_->setValidator(new QIntValidator(0, kMaxN, this));
    nLineEdit_->setPlaceholderText("Input n >= 0");

    auto* calculate_button = new QPushButton("Find", this);

    resultLabel_ = new QLabel("Result", this);

    layout->addWidget(mLineEdit_);
    layout->addWidget(nLineEdit_);
    layout->addWidget(calculate_button);
    layout->addWidget(resultLabel_);

    connect(calculate_button, &QPushButton::clicked, this,
            &MainWindow::calculateAckermann);

    setMinimumSize(kWindowLength, kWindowHeight);
}

MainWindow::~MainWindow() {}

long long MainWindow::ackermannFunction(int m, int n) {


    if (m == 0) {
        return n + 1;
    }


    if (m > 3 && n > 1) {
        return -1;
    }


    if (n == 0) {
        return ackermannFunction(m - 1, 1);
    }
    return ackermannFunction(m - 1, ackermannFunction(m, n - 1));
}

void MainWindow::calculateAckermann() {
    QString m_text = mLineEdit_->text();
    QString n_text = nLineEdit_->text();

    if (m_text.isEmpty() || n_text.isEmpty()) {
        resultLabel_->setText("Input both m and n");
        return;
    }

    bool m_ok, n_ok;
    int m = m_text.toInt(&m_ok);
    int n = n_text.toInt(&n_ok);


    if (!m_ok || !n_ok || (m > 3 && n > 1)) {
        resultLabel_->setText(
            "Ohh recursion problem m > 3 or n > 10 exceeds)))");
        return;
    }

    long long result = ackermannFunction(m, n);
    resultLabel_->setText(QString("A(%1, %2) = %3").arg(m).arg(n).arg(result));
}
