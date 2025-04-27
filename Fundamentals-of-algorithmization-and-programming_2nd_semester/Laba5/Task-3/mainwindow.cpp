#include "mainwindow.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QMessageBox>
#include <QVBoxLayout>
#include <limits>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    setWindowTitle("Bitset Visualization");

    //  layout
    QVBoxLayout* main_layout = new QVBoxLayout(ui_->centralwidget);

    // label to bitset
    QLabel* bitset_label = new QLabel();
    bitset_label->setAlignment(Qt::AlignCenter);
    bitset_label->setObjectName("bitsetLabel");
    main_layout->addWidget(bitset_label);

    //  input fields
    QHBoxLayout* input_layout = new QHBoxLayout();
    QLabel* pos_label = new QLabel("Position/Value:");
    QLineEdit* pos_input = new QLineEdit();
    pos_input->setObjectName("posInput");
    const int hundred = 100;
    pos_input->setMaximumWidth(hundred);

    pos_input->setValidator(
        new QIntValidator(0, std::numeric_limits<int>::max(), this));

    // init
    QLabel* init_label = new QLabel("Initialize with:");
    QLineEdit* init_input = new QLineEdit();
    init_input->setObjectName("initInput");
    init_input->setMaximumWidth(hundred);
    init_input->setValidator(
        new QIntValidator(0, std::numeric_limits<int>::max(), this));

    QPushButton* init_btn = new QPushButton("Initialize");

    input_layout->addWidget(pos_label);
    input_layout->addWidget(pos_input);
    input_layout->addWidget(init_label);
    input_layout->addWidget(init_input);
    input_layout->addWidget(init_btn);
    main_layout->addLayout(input_layout);

    //  buttons grid
    QGridLayout* button_layout = new QGridLayout();

    // row 1
    QPushButton* set_btn = new QPushButton("set(pos)");
    QPushButton* set_all_btn = new QPushButton("set()");
    QPushButton* reset_btn = new QPushButton("reset(pos)");
    QPushButton* reset_all_btn = new QPushButton("reset()");
    // row 2
    QPushButton* flip_btn = new QPushButton("flip(pos)");
    QPushButton* flip_all_btn = new QPushButton("flip()");
    QPushButton* test_btn = new QPushButton("test(pos)");
    QPushButton* count_btn = new QPushButton("count()");
    // row 3
    QPushButton* all_btn = new QPushButton("all()");
    QPushButton* any_btn = new QPushButton("any()");
    QPushButton* none_btn = new QPushButton("none()");
    QPushButton* size_btn = new QPushButton("size()");
    // row 4
    QPushButton* to_string_btn = new QPushButton("to_string()");
    QPushButton* to_ulong_btn = new QPushButton("to_ulong()");
    QPushButton* to_ullong_btn = new QPushButton("to_ullong()");
    QPushButton* not_btn = new QPushButton("~");
    // row 5
    QPushButton* or_btn = new QPushButton("|");

    // Add button
    button_layout->addWidget(set_btn, 0, 0);
    button_layout->addWidget(set_all_btn, 0, 1);
    button_layout->addWidget(reset_btn, 0, 2);
    button_layout->addWidget(reset_all_btn, 0, 3);

    button_layout->addWidget(flip_btn, 1, 0);
    button_layout->addWidget(flip_all_btn, 1, 1);
    button_layout->addWidget(test_btn, 1, 2);
    button_layout->addWidget(count_btn, 1, 3);

    button_layout->addWidget(all_btn, 2, 0);
    button_layout->addWidget(any_btn, 2, 1);
    button_layout->addWidget(none_btn, 2, 2);
    button_layout->addWidget(size_btn, 2, 3);

    button_layout->addWidget(to_string_btn, 3, 0);
    button_layout->addWidget(to_ulong_btn, 3, 1);
    button_layout->addWidget(to_ullong_btn, 3, 2);
    button_layout->addWidget(not_btn, 3, 3);

    button_layout->addWidget(or_btn, 4, 0);

    main_layout->addLayout(button_layout);

    connect(set_btn, &QPushButton::clicked, this, &MainWindow::onSetClicked);
    connect(set_all_btn, &QPushButton::clicked, this,
            &MainWindow::onSetAllClicked);
    connect(reset_btn, &QPushButton::clicked, this,
            &MainWindow::onResetClicked);
    connect(reset_all_btn, &QPushButton::clicked, this,
            &MainWindow::onResetAllClicked);
    connect(flip_btn, &QPushButton::clicked, this, &MainWindow::onFlipClicked);
    connect(flip_all_btn, &QPushButton::clicked, this,
            &MainWindow::onFlipAllClicked);
    connect(test_btn, &QPushButton::clicked, this, &MainWindow::onTestClicked);
    connect(all_btn, &QPushButton::clicked, this,
            &MainWindow::onCheckAllClicked);
    connect(any_btn, &QPushButton::clicked, this,
            &MainWindow::onCheckAnyClicked);
    connect(none_btn, &QPushButton::clicked, this,
            &MainWindow::onCheckNoneClicked);
    connect(count_btn, &QPushButton::clicked, this,
            &MainWindow::onCountClicked);
    connect(init_btn, &QPushButton::clicked, this,
            &MainWindow::onInitializeClicked);


    connect(size_btn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Size",
                                 "Size: " + QString::number(bitset_.size()));
    });
    connect(to_string_btn, &QPushButton::clicked, this,
            &MainWindow::onToStringClicked);
    connect(to_ulong_btn, &QPushButton::clicked, this,
            &MainWindow::onToUlongClicked);
    connect(to_ullong_btn, &QPushButton::clicked, this,
            &MainWindow::onToUllongClicked);
    connect(not_btn, &QPushButton::clicked, this, &MainWindow::onNotClicked);
    connect(or_btn, &QPushButton::clicked, this, &MainWindow::onOrClicked);

    updateDisplay();
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::updateDisplay() {
    QLabel* label = ui_->centralwidget->findChild<QLabel*>("bitsetLabel");


    if (label) {
        label->setText("Bitset: " +
                       QString::fromStdString(bitset_.to_string()));
    }
}

void MainWindow::onInitializeClicked() {
    QLineEdit* init_input = ui_->centralwidget->findChild<QLineEdit*>("initInput");

    if (init_input) {
        bool ok;
        size_t value = init_input->text().toULongLong(&ok);
        if (ok) {
            const int size = 64;
            bitset_ = Bitsett<size>(value);
            updateDisplay();
        } else {
            QMessageBox::warning(this, "Error", "Invalid value");
        }
    }
}

void MainWindow::onSetClicked() {
    QLineEdit* pos_input = ui_->centralwidget->findChild<QLineEdit*>("posInput");


    if (pos_input) {
        bool ok;
        size_t pos = pos_input->text().toULongLong(&ok);
        if (ok) {
            try {
                bitset_.set(pos);
                updateDisplay();
            } catch (const std::out_of_range& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        } else {
            QMessageBox::warning(this, "Error", "Invalid position value");
        }
    }
}

void MainWindow::onSetAllClicked() {
    bitset_.set();
    updateDisplay();
}

void MainWindow::onResetClicked() {
    QLineEdit* pos_input = ui_->centralwidget->findChild<QLineEdit*>("posInput");


    if (pos_input) {
        bool ok;
        size_t pos = pos_input->text().toULongLong(&ok);
        if (ok) {
            try {
                bitset_.reset(pos);
                updateDisplay();
            } catch (const std::out_of_range& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        } else {
            QMessageBox::warning(this, "Error", "Invalid position value");
        }
    }
}

void MainWindow::onResetAllClicked() {
    bitset_.reset();
    updateDisplay();
}

void MainWindow::onFlipClicked() {
    QLineEdit* pos_input = ui_->centralwidget->findChild<QLineEdit*>("posInput");


    if (pos_input) {
        bool ok;
        size_t pos = pos_input->text().toULongLong(&ok);
        if (ok) {
            try {
                bitset_.flip(pos);
                updateDisplay();
            } catch (const std::out_of_range& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        } else {
            QMessageBox::warning(this, "Error", "Invalid position value");
        }
    }
}

void MainWindow::onFlipAllClicked() {
    bitset_.flip();
    updateDisplay();
}

void MainWindow::onTestClicked() {
    QLineEdit* pos_input = ui_->centralwidget->findChild<QLineEdit*>("posInput");


    if (pos_input) {
        bool ok;
        size_t pos = pos_input->text().toULongLong(&ok);
        if (ok) {
            try {
                bool result = bitset_.test(pos);
                QMessageBox::information(this, "Test Result",
                                         "Bit at position " +
                                             QString::number(pos) + " is " +
                                             (result ? "1" : "0"));
            } catch (const std::out_of_range& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        } else {
            QMessageBox::warning(this, "Error", "Invalid position value");
        }
    }
}

void MainWindow::onCheckAllClicked() {
    bool result = bitset_.all();
    QMessageBox::information(
        this, "All Result",
        "All bits are " + QString(result ? "set" : "not set"));
}

void MainWindow::onCheckAnyClicked() {
    bool result = bitset_.any();
    QMessageBox::information(
        this, "Any Result",
        result ? "At least one bit is set" : "No bits are set");
}

void MainWindow::onCheckNoneClicked() {
    bool result = bitset_.none();
    QMessageBox::information(
        this, "None Result",
        result ? "No bits are set" : "At least one bit is set");
}

void MainWindow::onCountClicked() {
    size_t count = bitset_.count();
    QMessageBox::information(this, "Count Result",
                             "Number of set bits: " + QString::number(count));
}

void MainWindow::onToStringClicked() {
    std::string str = bitset_.to_string();
    QMessageBox::information(this, "String Representation",
                             "String: " + QString::fromStdString(str));
}

void MainWindow::onToUlongClicked() {
    try {
        unsigned long value = bitset_.to_ulong();
        QMessageBox::information(this, "ULong Value",
                                 "Unsigned long: " + QString::number(value));
    } catch (const std::overflow_error& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onToUllongClicked() {
    try {
        size_t value = bitset_.to_ullong();
        QMessageBox::information(
            this, "ULLong Value",
            "Unsigned long long: " + QString::number(value));
    } catch (const std::overflow_error& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onNotClicked() {
    bitset_ = ~bitset_;
    updateDisplay();
}

void MainWindow::onOrClicked() {
    QLineEdit* pos_input =
        ui_->centralwidget->findChild<QLineEdit*>("posInput");


    if (pos_input) {
        bool ok;
        size_t value = pos_input->text().toULongLong(&ok);
        if (ok) {
            const int size = 64;
            Bitsett<size> temp_bitset(value);
            bitset_ = bitset_ | temp_bitset;
            updateDisplay();
        } else {
            QMessageBox::warning(this, "Error", "Invalid value");
        }
    }
}
