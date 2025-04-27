#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QMainWindow>
#include <QSpinBox>
#include "paintscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_change_scale(double value);
  void on_change_x(double value);
  void on_change_y(double value);
  void on_change_angle(double value);
  void on_figure_selection_changed(int index);
  void update_figure_parameters();

  void on_circle_radius_changed(double value);
  void on_star_inner_radius_changed(double value);
  void on_star_outer_radius_changed(double value);
  void on_star_vertex_count_changed(int value);
  void on_polygon_vertex_count_changed(int value);
  void on_rectangle_width_changed(double value);
  void on_rectangle_height_changed(double value);
  void on_square_side_changed(double value);
  void on_triangle_side1_changed(double value);
  void on_triangle_side2_changed(double value);
  void on_triangle_side3_changed(double value);

 private:
  void createExtraControls();
  void hideAllExtraControls();

  Ui::MainWindow* ui_ = nullptr;
  PaintScene* scene_ = nullptr;

  QGroupBox* circleGroupBox_ = nullptr;
  QDoubleSpinBox* circleRadiusSpin_ = nullptr;

  QGroupBox* starGroupBox_ = nullptr;
  QDoubleSpinBox* starInnerRadiusSpin_ = nullptr;
  QDoubleSpinBox* starOuterRadiusSpin_ = nullptr;
  QSpinBox* starVertexSpin_ = nullptr;

  QGroupBox* polygonGroupBox_ = nullptr;
  QSpinBox* polygonVertexSpin_ = nullptr;

  QGroupBox* rectangleGroupBox_ = nullptr;
  QDoubleSpinBox* rectWidthSpin_ = nullptr;
  QDoubleSpinBox* rectHeightSpin_ = nullptr;

  QGroupBox* squareGroupBox_ = nullptr;
  QDoubleSpinBox* squareSideSpin_ = nullptr;

  QGroupBox* triangleGroupBox_ = nullptr;
  QDoubleSpinBox* triSideASpin_ = nullptr;
  QDoubleSpinBox* triSideBSpin_ = nullptr;
  QDoubleSpinBox* triSideCSpin_ = nullptr;
};

#endif  // MAINWINDOW_H
