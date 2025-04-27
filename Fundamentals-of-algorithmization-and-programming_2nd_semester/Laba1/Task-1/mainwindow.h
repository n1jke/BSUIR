
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QSlider>
#include <QTimer>
#include "smoke.h"
#include "train.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;  // auto generated class with pointers to widget in ui
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void sliderValueChanged(int value, int currX);

  void move_smoke();

 private:
  Ui::MainWindow* ui;  // ui content from designer
  QGraphicsScene* scene;
  Train* train;
  Smoke* smoke;
  QTimer* smokeTimer;
};

#endif  // MAINWINDOW_H
