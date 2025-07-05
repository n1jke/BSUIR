#include "mainwindow.h"

const int sz = 17; /* better take simply number */

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      btn_solve_(nullptr),
      memo_(nullptr),


      solver_(sz) {
    SetupUi();
}

MainWindow::~MainWindow() {}

void MainWindow::SetupUi() {
    setWindowTitle("Hash Map with Deque");
    const int height = 600;
    const int lenght = 800;
    resize(lenght, height);

    QWidget* central_widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central_widget);

    btn_solve_ = new QPushButton("Solve", central_widget);
    memo_ = new QPlainTextEdit(central_widget);
    memo_->setReadOnly(true);

    layout->addWidget(btn_solve_);
    layout->addWidget(memo_);

    setCentralWidget(central_widget);

    connect(btn_solve_, &QPushButton::clicked, this,
            &MainWindow::OnSolveClicked);

    memo_->setPlainText("Click 'Solve' to start the hash map demo.");
}

void MainWindow::OnSolveClicked() {
    solver_.Solve(memo_);
}
