#include "mainwindow.h"
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <vector>
#include "ui_mainwindow.h"

const char* k_paragraph_file = "testinginput.txt";
const char* k_array_file = "testinginput_0.txt";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // find output QTextEdit
    text_edit_output_ = findChild<QTextEdit*>("textEditOutput");

    connect(findChild<QPushButton*>("btnEnterParagraph"), &QPushButton::clicked,
            this, &MainWindow::OnEnterParagraph);
    connect(findChild<QPushButton*>("btnReadParagraph"), &QPushButton::clicked,
            this, &MainWindow::OnReadParagraph);
    connect(findChild<QPushButton*>("btnEnterArray"), &QPushButton::clicked,
            this, &MainWindow::OnEnterArray);
    connect(findChild<QPushButton*>("btnExit"), &QPushButton::clicked, this,
            &MainWindow::OnExit);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::OnEnterParagraph() {
    bool ok = false;
    QString paragraph = QInputDialog::getMultiLineText(
        this, "Enter Paragraph", "Enter a paragraph (press OK to save):", "",
        &ok);
    if (!ok || paragraph.isEmpty()) {
        return;
    }

    QFile file(k_paragraph_file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |
                   QIODevice::Text)) {
        text_edit_output_->setText("Failed to open file for writing.");
        return;
    }
    QTextStream out(&file);
    out << paragraph;
    file.close();
    text_edit_output_->setText("Paragraph saved to testinginput.txt");
}

void MainWindow::OnReadParagraph() {
    QFile file(k_paragraph_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        text_edit_output_->setText("Failed to open file for reading.");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
    text_edit_output_->setText(text);
}

void MainWindow::OnEnterArray() {
    bool ok = false;
    const int k_five = 5;
    const int k_one_thousand = 1000;
    int size =
        QInputDialog::getInt(this, "Array Size", "Enter array size:", k_five, 1,
                             k_one_thousand, 1, &ok);


    if (!ok) {
        return;
    }
    std::vector<long int> arr(size);


    for (int i = 0; i < size; ++i) {
        int value = QInputDialog::getInt(this, "Array Input",
                                         QString("Element [%1]:").arg(i), 0,
                                         INT_MIN, INT_MAX, 1, &ok);
        if (!ok) {
            return;
        }
        arr[i] = static_cast<long int>(value);
    }
    QFile file(k_array_file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |
                   QIODevice::Text)) {
        text_edit_output_->setText("Failed to open file for writing array.");
        return;
    }
    QTextStream out(&file);


    for (int i = 0; i < size; ++i) {
        out << arr[i];
        if (i < size - 1) {
            out << ",";
        }
    }
    file.close();
    text_edit_output_->setText("Array saved to testinginput_0.txt");
}

void MainWindow::OnExit() {
    close();
}
