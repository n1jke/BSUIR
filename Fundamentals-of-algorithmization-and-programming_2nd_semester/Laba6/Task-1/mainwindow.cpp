#include "mainwindow.h"
#include <QGridLayout>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include "magic.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    setWindowTitle("Clothes store");

    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);
    QGridLayout* buttons_layout = new QGridLayout();

    textDisplay_ = new QTextEdit(this);
    textDisplay_->setReadOnly(true);
    textDisplay_->setMinimumHeight(kFourHundred);
    textDisplay_->setStyleSheet("font-family: Monospace; font-size: 12px;");

    QPushButton* btn_direct_init =
        new QPushButton("Direct Initialization", this);
    QPushButton* btn_explicit_init =
        new QPushButton("Field-by-Field Initialization", this);
    QPushButton* btn_user_init =
        new QPushButton("Keyboard Initialization", this);
    QPushButton* btn_pointer_init =
        new QPushButton("Pointer Initialization", this);
    QPushButton* btn_reference_init =
        new QPushButton("Reference Initialization", this);

    buttons_layout->addWidget(btn_direct_init, 0, 0);
    buttons_layout->addWidget(btn_explicit_init, 0, 1);
    buttons_layout->addWidget(btn_user_init, 1, 0);
    buttons_layout->addWidget(btn_pointer_init, 1, 1);
    buttons_layout->addWidget(btn_reference_init, 2, 0, 1, 2);

    main_layout->addLayout(buttons_layout);
    main_layout->addWidget(new QLabel("Result:"));
    main_layout->addWidget(textDisplay_);

    connect(btn_direct_init, &QPushButton::clicked, this,
            &MainWindow::onDirectInitialization);
    connect(btn_explicit_init, &QPushButton::clicked, this,
            &MainWindow::onExplicitInitialization);
    connect(btn_user_init, &QPushButton::clicked, this,
            &MainWindow::onUserInputInitialization);
    connect(btn_pointer_init, &QPushButton::clicked, this,
            &MainWindow::onPointerInitialization);
    connect(btn_reference_init, &QPushButton::clicked, this,
            &MainWindow::onReferenceInitialization);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::onDirectInitialization() {
    // init list
    DATA init_data = {
        "T-shirt",
        kTen,
        kForty,
        'M',
        true,
        {kOneHundredFIftyFive, kOneHundredSixtyFive, kOneHundredSeventyFive}};

    Clothes clothes;
    clothes.setName(init_data.name);
    clothes.setCount(init_data.count);
    clothes.setPrice(init_data.price);
    clothes.setSize(init_data.size);
    clothes.setAvaliable(init_data.isAvaliable);
    clothes.setLenght(init_data.lenght[0], 0);
    clothes.setLenght(init_data.lenght[1], 1);
    clothes.setLenght(init_data.lenght[2], 2);

    QString result = "Explicit init:\n" + formatClothes(clothes);
    displayClothesInfo(result);
}

void MainWindow::onExplicitInitialization() {
    // individual
    Clothes clothes;
    clothes.setName("Jeans");
    clothes.setCount(kFifteen);
    clothes.setPrice(kOneHundred);
    clothes.setSize('L');
    clothes.setAvaliable(false);
    clothes.setLenght(kOneHundredFIftyFive, 0);
    clothes.setLenght(kOneHundredSixtyFive, 1);
    clothes.setLenght(kOneHundredSeventyFive, 2);

    QString result =
        "Field-by-field initialization:\n" + formatClothes(clothes);
    displayClothesInfo(result);
}

void MainWindow::onUserInputInitialization() {
    bool ok;
    Clothes clothes;

    QString name = QInputDialog::getText(
        this, "Data Input", "Product name:", QLineEdit::Normal, "Jacket", &ok);


    if (!ok) {
        return;
    }
    clothes.setName(name);

    int count = QInputDialog::getInt(this, "Data Input", "Count:", kFive, 0,
                                     kTenThousand, 1, &ok);


    if (!ok) {
        return;
    }
    clothes.setCount(count);

    double price = QInputDialog::getDouble(
        this, "Data Input", "Price:", kOneHundred, 0, kTenThousand, 2, &ok);


    if (!ok) {
        return;
    }
    clothes.setPrice(price);

    QString size_str = QInputDialog::getText(
        this, "Data Input", "Size (S, M, L, XL):", QLineEdit::Normal, "XL",
        &ok);


    if (!ok) {
        return;
    }
    QChar size = size_str.isEmpty() ? 'M' : size_str.at(0);
    clothes.setSize(size);

    int is_available =
        QMessageBox::question(this, "Data Input", "Is product available?",
                              QMessageBox::Yes | QMessageBox::No);
    clothes.setAvaliable(is_available == QMessageBox::Yes);


    for (int i = 0; i < 3; i++) {
        long long length = QInputDialog::getInt(
            this, "Data Input", QString("Length %1:").arg(i + 1),
            kOneHundredFIftyFive + i * kTen, 0, kTenThousand, 1, &ok);
        if (!ok) {
            return;
        }
        clothes.setLenght(length, i);
    }

    QString result = "Keyboard initialization:\n" + formatClothes(clothes);
    displayClothesInfo(result);
}

void MainWindow::onPointerInitialization() {
    Clothes clothes;
    Clothes* p_clothes = &clothes;

    // ptr init
    p_clothes->setName("Hat");
    p_clothes->setCount(kForty);
    p_clothes->setPrice(kFifteen);
    p_clothes->setSize('S');
    p_clothes->setAvaliable(true);
    p_clothes->setLenght(kOneHundredFIftyFive, 0);
    p_clothes->setLenght(kOneHundredSixtyFive, 1);
    p_clothes->setLenght(kOneHundredSeventyFive, 2);

    //   pointer
    QString result = "Pointer initialization:\n";
    result += "Name: " + p_clothes->name() + " | ";
    result += "Count: " + QString::number(p_clothes->count()) + " | ";
    result += "Price: " + QString::number(p_clothes->price()) + " | ";
    result += "Size: " + QString(p_clothes->size()) + " | ";
    result += "Available: " + QString(p_clothes->isAvaliable() ? "Yes" : "No") +
              " | ";
    result += "Lengths: ";


    for (int i = 0; i < 3; i++) {
        result += QString::number(p_clothes->lenght(i));
        if (i < 2) {
            result += ", ";
        }
    }

    displayClothesInfo(result);
}

void MainWindow::onReferenceInitialization() {
    Clothes clothes;
    Clothes& ref_clothes = clothes;

    // reference
    ref_clothes.setName("socks");
    ref_clothes.setCount(kForty);
    ref_clothes.setPrice(kFive);
    ref_clothes.setSize('U');
    ref_clothes.setAvaliable(true);
    ref_clothes.setLenght(kForty, 0);
    ref_clothes.setLenght(kForty, 1);
    ref_clothes.setLenght(kForty, 2);

    QString result = "Reference initialization:\n";
    result += "Name: " + ref_clothes.name() + " | ";
    result += "Count: " + QString::number(ref_clothes.count()) + " | ";
    result += "Price: " + QString::number(ref_clothes.price()) + " | ";
    result += "Size: " + QString(ref_clothes.size()) + " | ";
    result +=
        "Available: " + QString(ref_clothes.isAvaliable() ? "Yes" : "No") +
        " | ";
    result += "Lengths: ";


    for (int i = 0; i < 3; i++) {
        result += QString::number(ref_clothes.lenght(i));
        if (i < 2) {
            result += ", ";
        }
    }

    displayClothesInfo(result);
}

void MainWindow::displayClothesInfo(const QString& text) {
    textDisplay_->setText(text);
}

QString MainWindow::formatClothes(const Clothes& clothes) {
    QString result;

    result += "Name: " + clothes.name() + " | ";
    result += "Count: " + QString::number(clothes.count()) + " | ";
    result += "Price: " + QString::number(clothes.price()) + " | ";
    result += "Size: " + QString(clothes.size()) + " | ";
    result +=
        "Available: " + QString(clothes.isAvaliable() ? "Yes" : "No") + " | ";
    result += "Lengths: ";


    for (int i = 0; i < 3; i++) {
        result += QString::number(clothes.lenght(i));
        if (i < 2) {
            result += ", ";
        }
    }

    return result;
}
