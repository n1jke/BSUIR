#include "mainwindow.h"
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QIntValidator>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      _scene(new QGraphicsScene(this)),
      _inputKey(new QLineEdit(this)),
      _btnInsert(new QPushButton(tr("Insert"), this)),
      _btnErase(new QPushButton(tr("Erase"), this)),
      _btnClear(new QPushButton(tr("Clear"), this)),
      _view(new QGraphicsView(_scene, this)) {
    _inputKey->setValidator(new QIntValidator(-10000, 10000, this));
    _inputKey->setPlaceholderText(tr("Key (int)"));

    auto* hLayout = new QHBoxLayout;
    hLayout->addWidget(_inputKey);
    hLayout->addWidget(_btnInsert);
    hLayout->addWidget(_btnErase);
    hLayout->addWidget(_btnClear);

    auto* vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(_view);

    auto* central = new QWidget(this);
    central->setLayout(vLayout);
    setCentralWidget(central);
    setWindowTitle(tr("msl::map<int,int> Visualization"));

    connect(_btnInsert, &QPushButton::clicked, this, &MainWindow::onInsert);
    connect(_btnErase, &QPushButton::clicked, this, &MainWindow::onErase);
    connect(_btnClear, &QPushButton::clicked, this, &MainWindow::onClear);

    drawTree();
}

MainWindow::~MainWindow() = default;

void MainWindow::onInsert() {
    bool ok = false;
    int key = _inputKey->text().toInt(&ok);
    if (!ok)
        return;
    _tree.insert(key, key);
    drawTree();
}

void MainWindow::onErase() {
    bool ok = false;
    int key = _inputKey->text().toInt(&ok);
    if (!ok)
        return;
    // _tree.erase(key);
    drawTree();
}

void MainWindow::onClear() {
    _tree.clear();
    drawTree();
}

void MainWindow::drawTree() {
    _scene->clear();
    int w = _view->viewport()->width();
    drawNode(_tree.root(), 0, 0, w);
}

void MainWindow::drawNode(sml::map<int, int>::Node* node, int depth, int xMin,
                          int xMax) {
    if (!node || node == _tree.nil())
        return;

    int x = (xMin + xMax) / 2;
    int y = 50 + depth * 80;
    int r = 20;

    // линии до детей
    if (node->left && node->left != _tree.nil()) {
        int cx = (xMin + x) / 2;
        int cy = 50 + (depth + 1) * 80;
        _scene->addLine(x, y, cx, cy);
    }
    if (node->right && node->right != _tree.nil()) {
        int cx = (x + xMax) / 2;
        int cy = 50 + (depth + 1) * 80;
        _scene->addLine(x, y, cx, cy);
    }

    // узел
    auto* circle = _scene->addEllipse(
        x - r, y - r, 2 * r, 2 * r, QPen(Qt::black),
        QBrush(node->color == sml::map<int, int>::RED ? Qt::red : Qt::black));
    auto* txt = _scene->addText(QString::number(node->kv.first));
    txt->setDefaultTextColor(Qt::white);
    txt->setPos(x - r / 2, y - r / 2);

    // рекурсия
    drawNode(node->left, depth + 1, xMin, x);
    drawNode(node->right, depth + 1, x, xMax);
}
