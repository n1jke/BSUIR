#include "mainwindow.h"
#include <QGraphicsScene>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)  // initializ list
{

  ui->setupUi(this);

  // scene with graphicsView
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  train = new Train();
  scene->addItem(train);

  smoke = new Smoke();
  scene->addItem(smoke);

  smokeTimer = new QTimer(this);
  connect(smokeTimer, &QTimer::timeout, this, &MainWindow::move_smoke);
  smokeTimer->start(300);

  int currX = train->x();
  connect(ui->slider, &QSlider::valueChanged, this,
          [=](int value) { sliderValueChanged(value, currX); });
}

void MainWindow::sliderValueChanged(int value, int currX) {
  train->moveSlider(value * 3 + currX - 150);
}

void MainWindow::move_smoke() {
  train->emitSmoke();
}

MainWindow::~MainWindow() {
  delete ui;
}
