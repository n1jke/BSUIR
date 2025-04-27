#include "mainwindow.h"
#include <QColor>
#include <QDebug>
#include <QGridLayout>
#include <QHeaderView>
#include <QLocale>
#include <QMessageBox>
#include <QVBoxLayout>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    setupUI();
    setupValidators();
    updateTables();
    displaySizes();

    setWindowTitle("Slice & Pair Demo");
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::setupUI() {
    // main widget and layout
    QWidget* central_widget = new QWidget(this);
    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);

    //two sections for each slice
    QHBoxLayout* tables_layout = new QHBoxLayout();

    // 1 slice (slice<int>) section
    QVBoxLayout* first_slice_layout = new QVBoxLayout();
    QLabel* first_slice_label = new QLabel("Slice<int>");
    firstSliceTable_ = new QTableWidget(0, 1);
    firstSliceTable_->setHorizontalHeaderLabels({"Value"});
    firstSliceTable_->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    first_slice_layout->addWidget(first_slice_label);
    first_slice_layout->addWidget(firstSliceTable_);

    // 2 slice (slice<pair<int, double>>) section
    QVBoxLayout* second_slice_layout = new QVBoxLayout();
    QLabel* second_slice_label = new QLabel("Slice<pair<int, double>>");
    secondSliceTable_ = new QTableWidget(0, 2);
    secondSliceTable_->setHorizontalHeaderLabels({"Int Value", "Double Value"});
    secondSliceTable_->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    second_slice_layout->addWidget(second_slice_label);
    second_slice_layout->addWidget(secondSliceTable_);

    tables_layout->addLayout(first_slice_layout);
    tables_layout->addLayout(second_slice_layout);
    main_layout->addLayout(tables_layout);

    // synchronous add of values
    QGridLayout* input_layout = new QGridLayout();
    intValueInput_ = new QLineEdit();
    intValueInput_->setPlaceholderText("Int Value");
    intPairValueInput_ = new QLineEdit();
    intPairValueInput_->setPlaceholderText("Pair Int");
    doublePairValueInput_ = new QLineEdit();
    doublePairValueInput_->setPlaceholderText("Pair Double");
    indexInput_ = new QLineEdit();
    indexInput_->setPlaceholderText("Index (insert/erase)");
    performFirstOpButton_ = new QPushButton("Add pair");
    clearButton_ = new QPushButton("Clear all");

    const int five = 5;
    input_layout->addWidget(new QLabel("Int Value:"), 0, 0);
    input_layout->addWidget(intValueInput_, 0, 1);
    input_layout->addWidget(new QLabel("Pair Int:"), 1, 0);
    input_layout->addWidget(intPairValueInput_, 1, 1);
    input_layout->addWidget(new QLabel("Pair Double:"), 2, 0);
    input_layout->addWidget(doublePairValueInput_, 2, 1);
    input_layout->addWidget(new QLabel("Index:"), 3, 0);
    input_layout->addWidget(indexInput_, 3, 1);
    input_layout->addWidget(performFirstOpButton_, 4, 0, 1, 2);
    input_layout->addWidget(clearButton_, five, 0, 1, 2);

    main_layout->addLayout(input_layout);

    sizesLabel_ = new QLabel();
    main_layout->addWidget(sizesLabel_);

    const int height = 600;
    const int lenght = 800;
    setCentralWidget(central_widget);
    setMinimumSize(lenght, height);


    connect(performFirstOpButton_, &QPushButton::clicked, this,
            &MainWindow::performFirstSliceOperation);
    performFirstOpButton_->setText("Add pair value");


    connect(clearButton_, &QPushButton::clicked, this, [this]() {
        slicePair_.clear();
        updateTables();
        displaySizes();
    });
    clearButton_->setText("Clear all");

    // indx insert
    QPushButton* insert_button = new QPushButton("Insert by indx");
    main_layout->addWidget(insert_button);


    connect(insert_button, &QPushButton::clicked, this, [this]() {
        bool ok1, ok2, ok3, ok_idx;
        int v1 = intValueInput_->text().toInt(&ok1);
        int v2 = intPairValueInput_->text().toInt(&ok2);
        double d2 = doublePairValueInput_->text().toDouble(&ok3);
        int idx = indexInput_->text().toInt(&ok_idx);
        if (!ok1 || !ok2 || !ok3 || !ok_idx) {
            QMessageBox::warning(this, "Erorr", "Enter correct value!");
            return;
        }
        bool success =
            slicePair_.insert(idx, v1, sml::pair<int, double>(v2, d2));
        if (!success) {
            QMessageBox::warning(this, "Error", "Wrong index!");
            return;
        }
        updateTables();
        displaySizes();
    });

    // erase indx
    QPushButton* erase_button = new QPushButton("Erase by indx");
    main_layout->addWidget(erase_button);


    connect(erase_button, &QPushButton::clicked, this, [this]() {
        bool ok_idx;
        int idx = indexInput_->text().toInt(&ok_idx);
        if (!ok_idx) {
            QMessageBox::warning(this, "Error", "Enter correct indx!");
            return;
        }
        bool success = slicePair_.erase(idx);
        if (!success) {
            QMessageBox::warning(this, "Error", "ENter correct indx!");
            return;
        }
        updateTables();
        displaySizes();
    });

    QPushButton* sync_button = new QPushButton("Sync size ");
    main_layout->addWidget(sync_button);


    connect(sync_button, &QPushButton::clicked, this, [this]() {
        if (slicePair_.isSynchronized()) {
            QMessageBox::information(this, "Info", "Curr sync");
            return;
        }

        slicePair_.synchronize();
        updateTables();
        displaySizes();
        QMessageBox::information(this, "YEss", "All is okay sunc");
    });

    QLabel* help_label = new QLabel("!!!: double with point ( 10.5)");
    help_label->setStyleSheet("color: blue;");
    main_layout->addWidget(help_label);
}

void MainWindow::setupValidators() {
    // set validators for input fields
    QIntValidator* int_validator = new QIntValidator(this);
    QDoubleValidator* double_validator = new QDoubleValidator(this);
    intValueInput_->setValidator(int_validator);
    intPairValueInput_->setValidator(int_validator);
    indexInput_->setValidator(int_validator);
    double_validator->setNotation(QDoubleValidator::StandardNotation);
    double_validator->setLocale(QLocale::C);
    doublePairValueInput_->setValidator(double_validator);
    doublePairValueInput_->setLocale(QLocale::C);
    doublePairValueInput_->setPlaceholderText("Double Value (e.g. 10.5)");
}

void MainWindow::updateTables() {
    // update 1 slice table
    firstSliceTable_->setRowCount(0);
    for (size_t i = 0; i < slicePair_.first.size(); i++) {
        firstSliceTable_->insertRow(firstSliceTable_->rowCount());
        firstSliceTable_->setItem(
            i, 0, new QTableWidgetItem(QString::number(slicePair_.first[i])));
    }
    // update 2 slice table
    secondSliceTable_->setRowCount(0);
    for (size_t i = 0; i < slicePair_.second.size(); i++) {
        secondSliceTable_->insertRow(secondSliceTable_->rowCount());
        secondSliceTable_->setItem(
            i, 0,
            new QTableWidgetItem(QString::number(slicePair_.second[i].first)));

        QString double_value =
            QString::number(slicePair_.second[i].second, 'f', 2);
        secondSliceTable_->setItem(i, 1, new QTableWidgetItem(double_value));
    }

    const int first = 255;
    const int second_third = 200;

    // colorize not sync rows
    if (!slicePair_.isSynchronized()) {
        size_t min_size = slicePair_.size();
        size_t max_size =
            std::max(slicePair_.first.size(), slicePair_.second.size());


        for (size_t i = min_size; i < max_size; i++) {
            if (i < slicePair_.first.size()) {
                // this row not in second slice
                for (int col = 0; col < firstSliceTable_->columnCount();
                     ++col) {
                    QTableWidgetItem* item = firstSliceTable_->item(i, col);
                    if (item) {
                        item->setBackground(
                            QColor(first, second_third, second_third));
                    }
                }
            }

            if (i < slicePair_.second.size()) {
                // this row not in first slice
                for (int col = 0; col < secondSliceTable_->columnCount();
                     ++col) {
                    QTableWidgetItem* item = secondSliceTable_->item(i, col);
                    if (item) {
                        item->setBackground(
                            QColor(first, second_third, second_third));
                    }
                }
            }
        }
    }
}

void MainWindow::displaySizes() {
    QString size_info;

    if (slicePair_.isSynchronized()) {
        size_info = QString("Размер: %1").arg(slicePair_.size());
    } else {
        size_info = QString(" ERRRR size dont sync: 1 slice - %1, 2 slice - %2")
                        .arg(slicePair_.first.size())
                        .arg(slicePair_.second.size());
    }

    sizesLabel_->setText(size_info);
}

void MainWindow::performFirstSliceOperation() {
    bool ok1, ok2, ok3;
    int v1 = intValueInput_->text().toInt(&ok1);
    int v2 = intPairValueInput_->text().toInt(&ok2);
    double d2 = doublePairValueInput_->text().toDouble(&ok3);


    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Error",
                             "Enter valid nums\n Double with POINT (10.5)");
        return;
    }

    slicePair_.push_back(v1, sml::pair<int, double>(v2, d2));
    updateTables();
    displaySizes();

    intValueInput_->clear();
    intPairValueInput_->clear();
    doublePairValueInput_->clear();
}
