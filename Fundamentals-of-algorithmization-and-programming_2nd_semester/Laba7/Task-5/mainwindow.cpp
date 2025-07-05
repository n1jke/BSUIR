#include "mainwindow.h"
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QHeaderView>
#include <QInputDialog>
#include <QIntValidator>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QStandardItemModel>
#include <QTableView>
#include <QTimer>
#include <QVBoxLayout>
#include "ui_mainwindow.h"

namespace {
constexpr int kMaxDequeSize = 100;
constexpr int kRowHeight = 45;
constexpr int kMessageDuration = 3000;	// in milliseconds
constexpr int kIntMin = -2147483647;
constexpr int kIntMax = 2147483647;
constexpr int kFontSize = 11;
constexpr int kButtonCooldown = 300;  // ms to prevent double-clicks

// color checkup
constexpr int kFirstElementGreen = 20;
constexpr int kFirstElementBrightness = 200;
constexpr int kLastElementBlue = 20;
//constexpr int kLastElementBrightness = 120;
constexpr int kLastElementBlueValue = 220;
constexpr int kHueMaxDegrees = 270;
constexpr int kFullCircleDegrees = 360;
constexpr int kGradientSaturation = 180;
constexpr int kGradientBrightness = 220;
constexpr int kDarkGreyValue = 51;	// #333333
constexpr int kHeaderGreyValue = 80;
constexpr int kBorderSize = 2;
constexpr int kMarginSize = 5;
}  // namespace


DequeModel::DequeModel(sml::Deque<int>& deque, QObject* parent)
    : QAbstractTableModel(parent), deque_(deque) {}

int DequeModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return 1;
}

int DequeModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return deque_.size();  // number of columns
}

QVariant DequeModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() != 0) {
        return QVariant();
    }


    if (role == Qt::DisplayRole) {
        return deque_[index.column()];
    } else if (role == Qt::BackgroundRole) {
        // highlight front and back
        if (deque_.size() > 0) {
            if (index.column() == 0) {
                //more green for front
                return QBrush(QColor(kFirstElementGreen,
                                     kFirstElementBrightness,
                                     kFirstElementGreen));
            } else if (static_cast<size_t>(index.column()) ==
                       deque_.size() - 1) {
                //more blue for back
                return QBrush(QColor(kLastElementBlue, kLastElementBlue,
                                     kLastElementBlueValue));
            } else {
                // mixtape color for inside part
                int position = index.column();
                int total = deque_.size();

                int hue = (position * kHueMaxDegrees / total) %
                          kFullCircleDegrees;  // 0-270 degrees of hue
                QColor color;
                color.setHsv(hue, kGradientSaturation,
                             kGradientBrightness);	//brightness
                return QBrush(color);
            }
        } else {
            return QVariant(QColor(kDarkGreyValue, kDarkGreyValue,
                                   kDarkGreyValue));  //  grey for empty
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    } else if (role == Qt::ForegroundRole) {
        if (deque_.size() > 0) {
            if (index.column() == 0 ||
                static_cast<size_t>(index.column()) == deque_.size() - 1) {
                return QBrush(Qt::white);
            } else {
                return QBrush(Qt::black);
            }
        }
        return QBrush(Qt::white);
    } else if (role == Qt::FontRole) {
        QFont font;
        if (deque_.size() > 0 &&
            (index.column() == 0 ||
             static_cast<size_t>(index.column()) == deque_.size() - 1)) {
            font.setBold(true);
            font.setPointSize(kFontSize);
        }
        return font;
    }

    return QVariant();
}

QVariant DequeModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {


    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return section;
    }


    if (role == Qt::ForegroundRole) {
        return QBrush(Qt::white);
    }


    if (role == Qt::BackgroundRole && orientation == Qt::Horizontal) {
        // Custom header background
        return QBrush(
            QColor(kHeaderGreyValue, kHeaderGreyValue, kHeaderGreyValue));
    }

    return QVariant();
}

void DequeModel::updateView() {
    beginResetModel();
    endResetModel();
}

// MainWindow implementation
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      deque_(),
      dequeModel_(nullptr),


      buttonsEnabled_(true) {
    ui_->setupUi(this);

    // DequeModel and TableView
    dequeModel_ = new DequeModel(deque_, this);
    ui_->dequeTableView->setModel(dequeModel_);
    ui_->dequeTableView->verticalHeader()->setVisible(false);
    ui_->dequeTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    ui_->dequeTableView->verticalHeader()->setDefaultSectionSize(kRowHeight);
    QIntValidator* validator = new QIntValidator(kIntMin, kIntMax, this);
    ui_->valueLineEdit->setValidator(validator);
    ui_->valueLineEdit->setPlaceholderText("Enter integer value...");

    disconnectButtons();

    setupButtonConnections();

    setStyleSheet(
        "QMainWindow { background-color: #222222; color: #ffffff; } "
        "QPushButton { background-color: #444444; color: #ffffff; border: "
        "none; padding: 8px; "
        "            border-radius: 5px; font-weight: bold; } "
        "QPushButton:hover { background-color: #666666; }"
        "QPushButton:pressed { background-color: #333333; }"
        "QPushButton:disabled { background-color: #2a2a2a; color: #555555; }"
        "QPushButton#pushButton_pushFront { background-color: #2b6329; } "
        "QPushButton#pushButton_pushFront:hover { background-color: #327a31; } "
        "QPushButton#pushButton_pushBack { background-color: #2d5f94; } "
        "QPushButton#pushButton_pushBack:hover { background-color: #3571b1; } "
        "QPushButton#pushButton_popFront { background-color: #7d3b3b; } "
        "QPushButton#pushButton_popFront:hover { background-color: #984646; } "
        "QPushButton#pushButton_popBack { background-color: #7d5b3b; } "
        "QPushButton#pushButton_popBack:hover { background-color: #986e46; } "
        "QPushButton#pushButton_clear { background-color: #4b4b4b; } "
        "QPushButton#pushButton_clear:hover { background-color: #5a5a5a; } "
        "QTableView { background-color: #333333; gridline-color: #555555; "
        "color: #ffffff; "
        "            selection-background-color: #555555; border: none; "
        "border-radius: 5px; }"
        "QHeaderView::section { background-color: #444444; color: #ffffff; "
        "padding: 5px; border: none; }"
        "QLineEdit { background-color: #333333; color: #ffffff; border: 1px "
        "solid #555555; "
        "           padding: 8px; border-radius: 5px; font-size: 14px; }"
        "QLineEdit:focus { border-color: #777777; background-color: #3d3d3d; }"
        "QLabel { color: #ffffff; font-weight: bold; }");

    setWindowTitle(QString("Double-Ended Queue Visualization (max %1 elements)")
                       .arg(kMaxDequeSize));

    ui_->dequeTableView->setStyleSheet(
        ui_->dequeTableView->styleSheet() +
        QString("QTableView { border: %1px solid #555555; margin: %2px; }")
            .arg(kBorderSize)
            .arg(kMarginSize));

    //TODO fix double click TODO
    buttonCooldownTimer_ = new QTimer(this);
    buttonCooldownTimer_->setSingleShot(true);
    connect(buttonCooldownTimer_, &QTimer::timeout, this,
            &MainWindow::enableButtons);

    updateDequeView();

    qDebug() << "MainWindow initialized. Deque size:" << deque_.size();
}

MainWindow::~MainWindow() {
    disconnectButtons();
    delete ui_;
    delete dequeModel_;
    delete buttonCooldownTimer_;
}

void MainWindow::setupButtonConnections() {
    connect(ui_->pushButton_pushFront, &QPushButton::clicked, this,
            &MainWindow::on_pushButton_pushFront_clicked);
    connect(ui_->pushButton_pushBack, &QPushButton::clicked, this,
            &MainWindow::on_pushButton_pushBack_clicked);
    connect(ui_->pushButton_popFront, &QPushButton::clicked, this,
            &MainWindow::on_pushButton_popFront_clicked);
    connect(ui_->pushButton_popBack, &QPushButton::clicked, this,
            &MainWindow::on_pushButton_popBack_clicked);
    connect(ui_->pushButton_clear, &QPushButton::clicked, this,
            &MainWindow::on_pushButton_clear_clicked);
}

void MainWindow::disconnectButtons() {
    ui_->pushButton_pushFront->disconnect();
    ui_->pushButton_pushBack->disconnect();
    ui_->pushButton_popFront->disconnect();
    ui_->pushButton_popBack->disconnect();
    ui_->pushButton_clear->disconnect();
}

void MainWindow::disableButtons() {
    buttonsEnabled_ = false;
    ui_->pushButton_pushFront->setEnabled(false);
    ui_->pushButton_pushBack->setEnabled(false);
    ui_->pushButton_popFront->setEnabled(false);
    ui_->pushButton_popBack->setEnabled(false);
    ui_->pushButton_clear->setEnabled(false);

    // Start cooldown timer
    buttonCooldownTimer_->start(kButtonCooldown);
}

void MainWindow::enableButtons() {
    buttonsEnabled_ = true;
    ui_->pushButton_pushFront->setEnabled(true);
    ui_->pushButton_pushBack->setEnabled(true);
    ui_->pushButton_popFront->setEnabled(true);
    ui_->pushButton_popBack->setEnabled(true);
    ui_->pushButton_clear->setEnabled(true);
}

void MainWindow::on_pushButton_pushFront_clicked() {
    // prevent double clicks


    if (!buttonsEnabled_) {
        qDebug() << "Button click ignored (cooldown active)";
        return;
    }
    disableButtons();

    QString value_text = ui_->valueLineEdit->text();

    if (value_text.isEmpty()) {
        QMessageBox::information(this, "Input Required",
                                 "Please enter a value.");
        return;
    }

    bool ok;
    int value = value_text.toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Invalid Input",
                             "Please enter a valid integer.");
        return;
    }

    if (deque_.size() >= kMaxDequeSize) {
        QMessageBox::warning(this, "Limit Exceeded",
                             QString("Deque can hold a maximum of %1 elements.")
                                 .arg(kMaxDequeSize));
        return;
    }

    qDebug() << "Before push_front: Deque size =" << deque_.size();
    deque_.push_front(value);
    qDebug() << "After push_front: Deque size =" << deque_.size()
             << ", Added value =" << value;

    ui_->valueLineEdit->clear();
    updateDequeView();

    // info message
    ui_->statusbar->showMessage(QString("Added %1 to front. Deque size: %2/%3")
                                    .arg(value)
                                    .arg(deque_.size())
                                    .arg(kMaxDequeSize),
                                kMessageDuration);
}

void MainWindow::on_pushButton_pushBack_clicked() {
    // prevent double clicks


    if (!buttonsEnabled_) {
        qDebug() << "Button click ignored (cooldown active)";
        return;
    }
    disableButtons();

    QString value_text = ui_->valueLineEdit->text();

    if (value_text.isEmpty()) {
        QMessageBox::information(this, "Input Required",
                                 "Please enter a value.");
        return;
    }

    bool ok;
    int value = value_text.toInt(&ok);


    if (!ok) {
        QMessageBox::warning(this, "Invalid Input",
                             "Please enter a valid integer.");
        return;
    }

    if (deque_.size() >= kMaxDequeSize) {
        QMessageBox::warning(this, "Limit Exceeded",
                             QString("Deque can hold a maximum of %1 elements.")
                                 .arg(kMaxDequeSize));
        return;
    }

    qDebug() << "Before push_back: Deque size =" << deque_.size();
    deque_.push_back(value);
    qDebug() << "After push_back: Deque size =" << deque_.size()
             << ", Added value =" << value;

    ui_->valueLineEdit->clear();
    updateDequeView();

    ui_->statusbar->showMessage(QString("Added %1 to back. Deque size: %2/%3")
                                    .arg(value)
                                    .arg(deque_.size())
                                    .arg(kMaxDequeSize),
                                kMessageDuration);
}

void MainWindow::on_pushButton_popFront_clicked() {
    // prevent double clicks


    if (!buttonsEnabled_) {
        qDebug() << "Button click ignored (cooldown active)";
        return;
    }
    disableButtons();

    if (deque_.empty()) {
        QMessageBox::information(this, "Info", "Deque is empty.");
        return;
    }

    size_t size_before = deque_.size();
    qDebug() << "Before pop_front: Deque size =" << size_before;

    qDebug() << "Deque contents before pop_front:";
    for (size_t i = 0; i < deque_.size(); ++i) {
        qDebug() << "  [" << i << "] =" << deque_[i];
    }

    int front_value = deque_.front();
    qDebug() << "Front value to be removed =" << front_value;

    deque_.pop_front();

    size_t size_after = deque_.size();
    qDebug() << "After pop_front: Deque size =" << size_after;

    qDebug() << "Deque contents after pop_front:";
    for (size_t i = 0; i < deque_.size(); ++i) {
        qDebug() << "  [" << i << "] =" << deque_[i];
    }


    if (size_before != size_after + 1) {
        qDebug() << "ERROR: Pop operation removed" << (size_before - size_after)
                 << "elements instead of 1";
        QMessageBox::warning(this, "Error",
                             QString("Operation removed %1 elements instead of "
                                     "1. Please check deque implementation.")
                                 .arg(size_before - size_after));
    }

    ui_->dequeTableView->reset();

    updateDequeView();

    ui_->statusbar->showMessage(
        QString("Removed %1 from front. Deque size: %2/%3")
            .arg(front_value)
            .arg(deque_.size())
            .arg(kMaxDequeSize),
        kMessageDuration);
}

void MainWindow::on_pushButton_popBack_clicked() {
    // prevent double clicks


    if (!buttonsEnabled_) {
        qDebug() << "Button click ignored (cooldown active)";
        return;
    }
    disableButtons();

    if (deque_.empty()) {
        QMessageBox::information(this, "Info", "Deque is empty.");
        return;
    }

    size_t size_before = deque_.size();
    qDebug() << "Before pop_back: Deque size =" << size_before;

    qDebug() << "Deque contents before pop_back:";
    for (size_t i = 0; i < deque_.size(); ++i) {
        qDebug() << "  [" << i << "] =" << deque_[i];
    }

    int back_value = deque_.back();
    qDebug() << "Back value to be removed =" << back_value;
    deque_.pop_back();

    size_t size_after = deque_.size();
    qDebug() << "After pop_back: Deque size =" << size_after;


    qDebug() << "Deque contents after pop_back:";
    for (size_t i = 0; i < deque_.size(); ++i) {
        qDebug() << "  [" << i << "] =" << deque_[i];
    }


    if (size_before != size_after + 1) {
        qDebug() << "ERROR: Pop operation removed" << (size_before - size_after)
                 << "elements instead of 1";
        QMessageBox::warning(this, "Error",
                             QString("Operation removed %1 elements instead of "
                                     "1. Please check deque implementation.")
                                 .arg(size_before - size_after));
    }

    ui_->dequeTableView->reset();

    updateDequeView();

    ui_->statusbar->showMessage(
        QString("Removed %1 from back. Deque size: %2/%3")
            .arg(back_value)
            .arg(deque_.size())
            .arg(kMaxDequeSize),
        kMessageDuration);
}

void MainWindow::on_pushButton_clear_clicked() {


    if (!buttonsEnabled_) {
        qDebug() << "Button click ignored (cooldown active)";
        return;
    }
    disableButtons();

    if (deque_.empty()) {
        QMessageBox::information(this, "Info", "Deque is already empty.");
        return;
    }

    qDebug() << "Before clear: Deque size =" << deque_.size();
    deque_.clear();
    qDebug() << "After clear: Deque size =" << deque_.size();

    updateDequeView();

    ui_->statusbar->showMessage("Deque cleared.", kMessageDuration);
}

void MainWindow::updateDequeView() {
    dequeModel_->updateView();

    ui_->dequeTableView->viewport()->update();

    QString status;
    if (deque_.empty()) {
        status = "Deque is empty";
    } else {
        status =
            QString("Deque size: %1/%2").arg(deque_.size()).arg(kMaxDequeSize);
    }
    ui_->statusbar->showMessage(status);

    qDebug() << "View updated. Current deque size:" << deque_.size();
}
