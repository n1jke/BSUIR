#include "mainwindow.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), listHeap(new sml::ListHeap<int>()) {

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    // array heap
    arrayHeapGroup = new QGroupBox("Array-based Heap", centralWidget);
    arrayLayout = new QVBoxLayout(arrayHeapGroup);

    arrayValueSpin = new QSpinBox(arrayHeapGroup);
    arrayValueSpin->setRange(-1000, 1000);

    arrayButtonLayout = new QHBoxLayout();
    arrayInsertButton = new QPushButton("Insert", arrayHeapGroup);
    arrayExtractButton = new QPushButton("Extract Max", arrayHeapGroup);
    arrayClearButton = new QPushButton("Clear", arrayHeapGroup);

    arrayButtonLayout->addWidget(arrayInsertButton);
    arrayButtonLayout->addWidget(arrayExtractButton);
    arrayButtonLayout->addWidget(arrayClearButton);

    arrayHeapInfo = new QTextEdit(arrayHeapGroup);
    arrayHeapInfo->setReadOnly(true);

    arrayLayout->addWidget(arrayValueSpin);
    arrayLayout->addLayout(arrayButtonLayout);
    arrayLayout->addWidget(arrayHeapInfo);

    // list heap
    listHeapGroup = new QGroupBox("List-based Heap", centralWidget);
    listLayout = new QVBoxLayout(listHeapGroup);

    listValueSpin = new QSpinBox(listHeapGroup);
    listValueSpin->setRange(-1000, 1000);

    listButtonLayout = new QHBoxLayout();
    listInsertButton = new QPushButton("Insert", listHeapGroup);
    listExtractButton = new QPushButton("Extract Max", listHeapGroup);
    listClearButton = new QPushButton("Clear", listHeapGroup);

    listButtonLayout->addWidget(listInsertButton);
    listButtonLayout->addWidget(listExtractButton);
    listButtonLayout->addWidget(listClearButton);

    listHeapInfo = new QTextEdit(listHeapGroup);
    listHeapInfo->setReadOnly(true);

    listLayout->addWidget(listValueSpin);
    listLayout->addLayout(listButtonLayout);
    listLayout->addWidget(listHeapInfo);

    mainLayout->addWidget(arrayHeapGroup);
    mainLayout->addWidget(listHeapGroup);

    connect(arrayInsertButton, &QPushButton::clicked, this,
            &MainWindow::onArrayInsert);
    connect(arrayExtractButton, &QPushButton::clicked, this,
            &MainWindow::onArrayExtract);
    connect(arrayClearButton, &QPushButton::clicked, this,
            &MainWindow::onArrayClear);

    connect(listInsertButton, &QPushButton::clicked, this,
            &MainWindow::onListInsert);
    connect(listExtractButton, &QPushButton::clicked, this,
            &MainWindow::onListExtract);
    connect(listClearButton, &QPushButton::clicked, this,
            &MainWindow::onListClear);

    updateHeapDisplays();

    setWindowTitle("Binary Heap Demo");
    resize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::onArrayInsert() {
    int value = arrayValueSpin->value();
    arrayHeap.insert(value);
    updateHeapDisplays();
}

void MainWindow::onArrayExtract() {
    try {
        int max = arrayHeap.extractMax();
        QMessageBox::information(this, "Extract Max",
                                 QString("Extracted value: %1").arg(max));
        updateHeapDisplays();
    } catch (const std::out_of_range&) {
        QMessageBox::warning(this, "Error", "Array heap is empty");
    }
}

void MainWindow::onArrayClear() {
    arrayHeap.clear();
    updateHeapDisplays();
}

void MainWindow::onListInsert() {
    int value = listValueSpin->value();
    listHeap->insert(value);
    updateHeapDisplays();
}

void MainWindow::onListExtract() {
    try {
        int max = listHeap->extractMax();
        QMessageBox::information(this, "Extract Max",
                                 QString("Extracted value: %1").arg(max));
        updateHeapDisplays();
    } catch (const std::out_of_range&) {
        QMessageBox::warning(this, "Error", "List heap is empty");
    }
}

void MainWindow::onListClear() {
    listHeap->clear();
    updateHeapDisplays();
}

void MainWindow::updateHeapDisplays() {
    // Обновляем информацию о массиве
    arrayHeapInfo->clear();
    if (arrayHeap.isEmpty()) {
        arrayHeapInfo->append("Heap is empty");
    } else {
        arrayHeapInfo->append(QString("Size: %1").arg(arrayHeap.size()));
        arrayHeapInfo->append(QString("Max: %1").arg(arrayHeap.getMax()));
        arrayHeapInfo->append("Elements:");

        auto elements = arrayHeap.toVector();


        for (int val : elements) {
            arrayHeapInfo->append(QString::number(val));
        }
    }

    listHeapInfo->clear();
    if (listHeap->isEmpty()) {
        listHeapInfo->append("Heap is empty");
    } else {
        listHeapInfo->append(QString("Size: %1").arg(listHeap->size()));
        listHeapInfo->append(QString("Max: %1").arg(listHeap->getMax()));
        listHeapInfo->append("Elements:");

        auto elements = listHeap->toVector();


        for (int val : elements) {
            listHeapInfo->append(QString::number(val));
        }
    }
}
