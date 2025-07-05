#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <sstream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      scene_(new QGraphicsScene(this)) {

    ui_->setupUi(this);
    setWindowTitle("Doubly Linked List Visualizer");

    QWidget* central_widget = new QWidget(this);
    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);
    setCentralWidget(central_widget);

    // Graphics view
    QGraphicsView* view = new QGraphicsView(scene_);
    const int height = 300;
    view->setMinimumHeight(height);
    view->setRenderHint(QPainter::Antialiasing);
    main_layout->addWidget(view);

    // Status label
    statusLabel_ = new QLabel("List is empty");
    statusLabel_->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(statusLabel_);

    // Buttons
    QHBoxLayout* btn_layout = new QHBoxLayout();
    QPushButton* push_front = new QPushButton("Push Front");
    QPushButton* push_back = new QPushButton("Push Back");
    QPushButton* pop_front = new QPushButton("Pop Front");
    QPushButton* pop_back = new QPushButton("Pop Back");
    QPushButton* clear = new QPushButton("Clear");
    QPushButton* swap_min_max = new QPushButton("Swap Min/Max");
    QPushButton* find = new QPushButton("Find");

    btn_layout->addWidget(push_front);
    btn_layout->addWidget(push_back);
    btn_layout->addWidget(pop_front);
    btn_layout->addWidget(pop_back);
    btn_layout->addWidget(clear);
    btn_layout->addWidget(swap_min_max);
    btn_layout->addWidget(find);

    main_layout->addLayout(btn_layout);

    // Connect
    connect(push_front, &QPushButton::clicked, this, &MainWindow::onPushFront);
    connect(push_back, &QPushButton::clicked, this, &MainWindow::onPushBack);
    connect(pop_front, &QPushButton::clicked, this, &MainWindow::onPopFront);
    connect(pop_back, &QPushButton::clicked, this, &MainWindow::onPopBack);
    connect(clear, &QPushButton::clicked, this, &MainWindow::onClear);
    connect(swap_min_max, &QPushButton::clicked, this,
            &MainWindow::onSwapMinMax);
    connect(find, &QPushButton::clicked, this, &MainWindow::onFindValue);

    updateScene();
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::onPushFront() {
    bool ok;
    const double min = -1e6;
    const double max = 1e6;
    int val = QInputDialog::getInt(this, "Push Front", "Enter value:", 0, min,
                                   max, 1, &ok);


    if (ok) {
        list_.push_front(val);
        updateScene();
    }
}

void MainWindow::onPushBack() {
    bool ok;
    const double min = -1e6;
    const double max = 1e6;
    int val = QInputDialog::getInt(this, "Push Back", "Enter value:", 0, min,
                                   max, 1, &ok);


    if (ok) {
        list_.push_back(val);
        updateScene();
    }
}

void MainWindow::onPopFront() {
    if (list_.empty()) {
        QMessageBox::information(this, "Error", "List is empty.");
        return;
    }
    list_.pop_front();
    updateScene();
}

void MainWindow::onPopBack() {
    if (list_.empty()) {
        QMessageBox::information(this, "Error", "List is empty.");
        return;
    }
    list_.pop_back();
    updateScene();
}

void MainWindow::onClear() {
    list_.clear();
    updateScene();
}

void MainWindow::onSwapMinMax() {
    if (list_.size() < 2) {
        QMessageBox::information(this, "Info", "At least 2 elements required.");
        return;
    }
    list_.swap_min_max_nodes();	 // swaps *values* not *nodes*
    updateScene();
}

void MainWindow::onFindValue() {
    bool ok;
    const double min = -1e6;
    const double max = 1e6;
    int val =
        QInputDialog::getInt(this, "Find", "Enter value:", 0, min, max, 1, &ok);


    if (!ok) {
        return;
    }

    auto node = list_.find(val);


    if (node) {
        std::stringstream ss;
        ss << std::hex << std::showbase << reinterpret_cast<uintptr_t>(node);
        QMessageBox::information(this, "Found",
                                 QString("Value %1 found at address %2")
                                     .arg(val)
                                     .arg(QString::fromStdString(ss.str())));
    } else {
        QMessageBox::information(this, "Not Found", "Value not found in list.");
    }
}
void MainWindow::updateScene() {
    scene_->clear();
    int count = 0;
    const int kx = 50;
    const int ky = 150;
    int x = kx;
    int y = ky;

    for (auto it = list_.begin(); it != list_.end() && count < MAX_NODES_;
         ++it, ++count) {
        auto* cur = it.operator->();

        // create string
        std::stringstream ss;
        ss << std::hex << std::showbase << reinterpret_cast<uintptr_t>(cur);
        QString addr = QString::fromStdString(ss.str());

        drawNode(x, y, cur->data, addr);


        if (cur->next && count < MAX_NODES_ - 1) {
            scene_->addLine(x, y, x + NODE_SPACING_, y, QPen(Qt::black, 2));
        }

        x += NODE_SPACING_;
    }
}

void MainWindow::drawNode(int x, int y, int value, const QString& addr) {
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    scene_->addEllipse(x - NODE_RADIUS_, y - NODE_RADIUS_, NODE_RADIUS_ * 2,
                       NODE_RADIUS_ * 2, pen, brush);

    const double k_one_half = 1.5;
    const int k_five = 5;
    const int k_seven = 7;
    auto* val_text = scene_->addText(QString::number(value));
    val_text->setPos(x - val_text->boundingRect().width() / 2,
                     y - NODE_RADIUS_ / k_one_half);

    auto* addr_text = scene_->addText(addr);
    addr_text->setDefaultTextColor(Qt::green);
    addr_text->setFont(QFont("Courier", k_seven));
    addr_text->setPos(x - addr_text->boundingRect().width() / 2, y + k_five);
}

void MainWindow::drawArrow(int x1, int y1, int x2, int y2, QColor color) {
    QPen pen(color);
    pen.setWidth(2);
    scene_->addLine(x1, y1, x2, y2, pen);

    const double arrow_size = 8;
    const int k_six = 6;
    double angle = std::atan2(y2 - y1, x2 - x1);
    QPointF p1(x2 - arrow_size * std::cos(angle - M_PI / k_six),
               y2 - arrow_size * std::sin(angle - M_PI / k_six));
    QPointF p2(x2 - arrow_size * std::cos(angle + M_PI / k_six),
               y2 - arrow_size * std::sin(angle + M_PI / k_six));

    QPolygonF arrow_head;
    arrow_head << QPointF(x2, y2) << p1 << p2;
    scene_->addPolygon(arrow_head, pen, QBrush(color));
}
