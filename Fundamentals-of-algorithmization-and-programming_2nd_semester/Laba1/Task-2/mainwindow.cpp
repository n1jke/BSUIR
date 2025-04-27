#include "mainwindow.h"
#include "basefigure.h"
#include "circle.h"
#include "rectangle.h"
#include "rightpolygon.h"
#include "square.h"
#include "star.h"
#include "triangle.h"
#include "ui_mainwindow.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalBlocker>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  scene_ = new PaintScene(this);
  ui_->graphicsView->setScene(scene_);
  scene_->setSceneRect(-200, -200, 400, 400);
  ui_->graphicsView->setRenderHint(QPainter::Antialiasing);

  connect(ui_->change_scale, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_change_scale);
  connect(ui_->change_x, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_change_x);
  connect(ui_->change_y, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_change_y);
  connect(ui_->change_angle, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_change_angle);
  connect(ui_->change_figure, &QComboBox::currentIndexChanged, this,
          &MainWindow::on_figure_selection_changed);
  connect(scene_, &QGraphicsScene::selectionChanged, this,
          &MainWindow::update_figure_parameters);

  createExtraControls();
  hideAllExtraControls();
}

MainWindow::~MainWindow() {
  delete scene_;
  delete ui_;
}

void MainWindow::on_change_scale(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* figure = dynamic_cast<BaseFigure*>(item)) {
      figure->change_scale(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_change_x(double value) {
  for (auto* item : scene_->selectedItems()) {
    if (auto* figure = dynamic_cast<BaseFigure*>(item)) {
      QPointF pos = figure->pos();
      figure->move_to(value, pos.y());
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_change_y(double value) {
  for (auto* item : scene_->selectedItems()) {
    if (auto* figure = dynamic_cast<BaseFigure*>(item)) {
      QPointF pos = figure->pos();
      figure->move_to(pos.x(), value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_change_angle(double value) {
  for (auto* item : scene_->selectedItems()) {
    if (auto* figure = dynamic_cast<BaseFigure*>(item)) {
      figure->change_rotate_angle(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_circle_radius_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* circle = dynamic_cast<Circle*>(item)) {
      circle->change_radius(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_star_inner_radius_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* star = dynamic_cast<Star*>(item)) {
      if (value < star->get_outer_radius()) {
        star->change_radius_in(value);
        update_figure_parameters();  // Обновление UI
      }
    }
  }
  scene_->update();
}

void MainWindow::on_star_outer_radius_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* star = dynamic_cast<Star*>(item)) {
      if (value > star->get_inner_radius()) {
        star->change_radius_out(value);
        update_figure_parameters();  // Обновление UI
      }
    }
  }
  scene_->update();
}

void MainWindow::on_star_vertex_count_changed(int value) {
  if (value < 3)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* star = dynamic_cast<Star*>(item)) {
      star->change_apex_num(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_polygon_vertex_count_changed(int value) {
  if (value < 3)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* poly = dynamic_cast<RightPolygon*>(item)) {
      poly->change_apex_num(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_rectangle_width_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* rect = dynamic_cast<Rectangle*>(item)) {
      rect->change_width(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_rectangle_height_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* rect = dynamic_cast<Rectangle*>(item)) {
      rect->change_height(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_square_side_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* square = dynamic_cast<Square*>(item)) {
      square->change_side(value);
      update_figure_parameters();  // Обновление UI
    }
  }
  scene_->update();
}

void MainWindow::on_triangle_side1_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* tri = dynamic_cast<Triangle*>(item)) {
      double s2 = tri->get_side2();
      double s3 = tri->get_side3();
      if (value + s2 > s3 && value + s3 > s2 && s2 + s3 > value) {
        tri->change_side1(value);
        update_figure_parameters();  // Обновление UI
      } else {
        QSignalBlocker blocker(triSideASpin_);
        triSideASpin_->setValue(tri->get_side1());
      }
    }
  }
  scene_->update();
}

void MainWindow::on_triangle_side2_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* tri = dynamic_cast<Triangle*>(item)) {
      double s1 = tri->get_side1();
      double s3 = tri->get_side3();
      if (s1 + value > s3 && s1 + s3 > value && value + s3 > s1) {
        tri->change_side2(value);
        update_figure_parameters();  // Обновление UI
      } else {
        QSignalBlocker blocker(triSideBSpin_);
        triSideBSpin_->setValue(tri->get_side2());
      }
    }
  }
  scene_->update();
}

void MainWindow::on_triangle_side3_changed(double value) {
  if (value <= 0)
    return;
  for (auto* item : scene_->selectedItems()) {
    if (auto* tri = dynamic_cast<Triangle*>(item)) {
      double s1 = tri->get_side1();
      double s2 = tri->get_side2();
      if (s1 + s2 > value && s1 + value > s2 && s2 + value > s1) {
        tri->change_side3(value);
        update_figure_parameters();  // Обновление UI
      } else {
        QSignalBlocker blocker(triSideCSpin_);
        triSideCSpin_->setValue(tri->get_side3());
      }
    }
  }
  scene_->update();
}

void MainWindow::on_figure_selection_changed(int index) {
  hideAllExtraControls();
  BaseFigure* newFigure = nullptr;
  switch (index) {
    case 0:
      scene_->add_circle();
      break;
    case 1:
      scene_->add_rectangle();
      break;
    case 2:
      scene_->add_rhomb();
      break;
    case 3:
      scene_->add_right_polygon();
      break;
    case 4:
      scene_->add_square();
      break;
    case 5:
      scene_->add_star();
      break;
    case 6:
      scene_->add_triangle();
      break;
    default:
      break;
  }
  if (newFigure) {
    newFigure->setSelected(true);
    update_figure_parameters();  // Обновление UI для новой фигуры
  }
  scene_->update();
}

void MainWindow::update_figure_parameters() {
  if (scene_->selectedItems().isEmpty()) {
    ui_->area->clear();
    ui_->perimetre->clear();
    return;
  }
  auto* figure = dynamic_cast<BaseFigure*>(scene_->selectedItems().first());
  if (figure == nullptr) {
    return;
  }

  // Блокировка сигналов для предотвращения рекурсии
  QSignalBlocker scaleBlocker(ui_->change_scale);
  QSignalBlocker xBlocker(ui_->change_x);
  QSignalBlocker yBlocker(ui_->change_y);
  QSignalBlocker angleBlocker(ui_->change_angle);

  // Обновление полей периметра и площади
  ui_->area->setText(QString::number(figure->area(), 'f', 2));
  ui_->perimetre->setText(QString::number(figure->perimeter(), 'f', 2));
  ui_->change_scale->setValue(figure->scale_factor);
  ui_->change_x->setValue(figure->pos().x());
  ui_->change_y->setValue(figure->pos().y());
  ui_->change_angle->setValue(figure->rotate_angle);

  // Обновление специфических параметров
  hideAllExtraControls();
  if (auto* circle = dynamic_cast<Circle*>(figure)) {
    circleGroupBox_->show();
    QSignalBlocker blocker(circleRadiusSpin_);
    circleRadiusSpin_->setValue(circle->get_radius());
  } else if (auto* rect = dynamic_cast<Rectangle*>(figure)) {
    rectangleGroupBox_->show();
    QSignalBlocker widthBlocker(rectWidthSpin_);
    QSignalBlocker heightBlocker(rectHeightSpin_);
    rectWidthSpin_->setValue(rect->get_width());
    rectHeightSpin_->setValue(rect->get_height());
  } else if (auto* square = dynamic_cast<Square*>(figure)) {
    squareGroupBox_->show();
    QSignalBlocker blocker(squareSideSpin_);
    squareSideSpin_->setValue(square->get_side());
  } else if (auto* tri = dynamic_cast<Triangle*>(figure)) {
    triangleGroupBox_->show();
    QSignalBlocker blockerA(triSideASpin_);
    QSignalBlocker blockerB(triSideBSpin_);
    QSignalBlocker blockerC(triSideCSpin_);
    triSideASpin_->setValue(tri->get_side1());
    triSideBSpin_->setValue(tri->get_side2());
    triSideCSpin_->setValue(tri->get_side3());
  } else if (auto* star = dynamic_cast<Star*>(figure)) {
    starGroupBox_->show();
    QSignalBlocker innerBlocker(starInnerRadiusSpin_);
    QSignalBlocker outerBlocker(starOuterRadiusSpin_);
    QSignalBlocker vertexBlocker(starVertexSpin_);
    starInnerRadiusSpin_->setValue(star->get_inner_radius());
    starOuterRadiusSpin_->setValue(star->get_outer_radius());
    starVertexSpin_->setValue(star->get_vertex_count());
  } else if (auto* poly = dynamic_cast<RightPolygon*>(figure)) {
    polygonGroupBox_->show();
    QSignalBlocker blocker(polygonVertexSpin_);
    polygonVertexSpin_->setValue(poly->get_vertex_count());
  }
}

void MainWindow::createExtraControls() {
  // circle group
  circleGroupBox_ = new QGroupBox("Circle Parameters", ui_->centralwidget);
  circleGroupBox_->setGeometry(450, 50, 300, 60);
  auto* circle_layout = new QHBoxLayout(circleGroupBox_);
  auto* circle_radius_label = new QLabel("Radius:", circleGroupBox_);
  circleRadiusSpin_ = new QDoubleSpinBox(circleGroupBox_);
  circleRadiusSpin_->setRange(0.0, 200.0);
  circleRadiusSpin_->setValue(50.0);
  circle_layout->addWidget(circle_radius_label);
  circle_layout->addWidget(circleRadiusSpin_);
  connect(circleRadiusSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_circle_radius_changed);

  // star group
  starGroupBox_ = new QGroupBox("Star Parameters", ui_->centralwidget);
  starGroupBox_->setGeometry(450, 120, 300, 120);
  auto* star_layout = new QVBoxLayout(starGroupBox_);
  auto* star_inner_layout = new QHBoxLayout;
  auto* star_inner_label = new QLabel("Inner Radius:", starGroupBox_);
  starInnerRadiusSpin_ = new QDoubleSpinBox(starGroupBox_);
  starInnerRadiusSpin_->setRange(0.0, 200.0);
  starInnerRadiusSpin_->setValue(40.0);
  star_inner_layout->addWidget(star_inner_label);
  star_inner_layout->addWidget(starInnerRadiusSpin_);
  auto* star_outer_layout = new QHBoxLayout;
  auto* star_outer_label = new QLabel("Outer Radius:", starGroupBox_);
  starOuterRadiusSpin_ = new QDoubleSpinBox(starGroupBox_);
  starOuterRadiusSpin_->setRange(0.0, 200.0);
  starOuterRadiusSpin_->setValue(80.0);
  star_outer_layout->addWidget(star_outer_label);
  star_outer_layout->addWidget(starOuterRadiusSpin_);
  auto* star_vertex_layout = new QHBoxLayout;
  auto* star_vertex_label = new QLabel("Vertices:", starGroupBox_);
  starVertexSpin_ = new QSpinBox(starGroupBox_);
  starVertexSpin_->setRange(3, 20);
  starVertexSpin_->setValue(5);
  star_vertex_layout->addWidget(star_vertex_label);
  star_vertex_layout->addWidget(starVertexSpin_);
  star_layout->addLayout(star_inner_layout);
  star_layout->addLayout(star_outer_layout);
  star_layout->addLayout(star_vertex_layout);
  connect(starInnerRadiusSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_star_inner_radius_changed);
  connect(starOuterRadiusSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_star_outer_radius_changed);
  connect(starVertexSpin_, &QSpinBox::valueChanged, this,
          &MainWindow::on_star_vertex_count_changed);

  // right polygon group
  polygonGroupBox_ =
      new QGroupBox("Right Polygon Parameters", ui_->centralwidget);
  polygonGroupBox_->setGeometry(450, 230, 300, 60);
  auto* polygon_layout = new QHBoxLayout(polygonGroupBox_);
  auto* polygon_vertex_label = new QLabel("Vertices:", polygonGroupBox_);
  polygonVertexSpin_ = new QSpinBox(polygonGroupBox_);
  polygonVertexSpin_->setRange(3, 20);
  polygonVertexSpin_->setValue(4);
  polygon_layout->addWidget(polygon_vertex_label);
  polygon_layout->addWidget(polygonVertexSpin_);
  connect(polygonVertexSpin_, &QSpinBox::valueChanged, this,
          &MainWindow::on_polygon_vertex_count_changed);

  // rectangle group
  rectangleGroupBox_ =
      new QGroupBox("Rectangle Parameters", ui_->centralwidget);
  rectangleGroupBox_->setGeometry(450, 290, 300, 100);
  auto* rect_layout = new QVBoxLayout(rectangleGroupBox_);
  auto* rect_width_layout = new QHBoxLayout;
  auto* rect_width_label = new QLabel("Width:", rectangleGroupBox_);
  rectWidthSpin_ = new QDoubleSpinBox(rectangleGroupBox_);
  rectWidthSpin_->setRange(0.0, 200.0);
  rectWidthSpin_->setValue(80.0);
  rect_width_layout->addWidget(rect_width_label);
  rect_width_layout->addWidget(rectWidthSpin_);
  auto* rect_height_layout = new QHBoxLayout;
  auto* rect_height_label = new QLabel("Height:", rectangleGroupBox_);
  rectHeightSpin_ = new QDoubleSpinBox(rectangleGroupBox_);
  rectHeightSpin_->setRange(0.0, 200.0);
  rectHeightSpin_->setValue(50.0);
  rect_height_layout->addWidget(rect_height_label);
  rect_height_layout->addWidget(rectHeightSpin_);
  rect_layout->addLayout(rect_width_layout);
  rect_layout->addLayout(rect_height_layout);
  connect(rectWidthSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_rectangle_width_changed);
  connect(rectHeightSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_rectangle_height_changed);

  // square group
  squareGroupBox_ = new QGroupBox("Square Parameters", ui_->centralwidget);
  squareGroupBox_->setGeometry(450, 400, 300, 60);
  auto* square_layout = new QHBoxLayout(squareGroupBox_);
  auto* square_side_label = new QLabel("Side:", squareGroupBox_);
  squareSideSpin_ = new QDoubleSpinBox(squareGroupBox_);
  squareSideSpin_->setRange(0.0, 200.0);
  squareSideSpin_->setValue(60.0);
  square_layout->addWidget(square_side_label);
  square_layout->addWidget(squareSideSpin_);
  connect(squareSideSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_square_side_changed);

  // triangle group
  triangleGroupBox_ = new QGroupBox("Triangle Parameters", ui_->centralwidget);
  triangleGroupBox_->setGeometry(450, 470, 300, 120);
  auto* triangle_layout = new QVBoxLayout(triangleGroupBox_);
  auto* tri_side_a_layout = new QHBoxLayout;
  auto* tri_side_a_label = new QLabel("Side 1:", triangleGroupBox_);
  triSideASpin_ = new QDoubleSpinBox(triangleGroupBox_);
  triSideASpin_->setRange(0.0, 200.0);
  triSideASpin_->setValue(50.0);
  tri_side_a_layout->addWidget(tri_side_a_label);
  tri_side_a_layout->addWidget(triSideASpin_);
  auto* tri_side_b_layout = new QHBoxLayout;
  auto* tri_side_b_label = new QLabel("Side 2:", triangleGroupBox_);
  triSideBSpin_ = new QDoubleSpinBox(triangleGroupBox_);
  triSideBSpin_->setRange(0.0, 200.0);
  triSideBSpin_->setValue(50.0);
  tri_side_b_layout->addWidget(tri_side_b_label);
  tri_side_b_layout->addWidget(triSideBSpin_);
  auto* tri_side_c_layout = new QHBoxLayout;
  auto* tri_side_c_label = new QLabel("Side 3:", triangleGroupBox_);
  triSideCSpin_ = new QDoubleSpinBox(triangleGroupBox_);
  triSideCSpin_->setRange(0.0, 200.0);
  triSideCSpin_->setValue(50.0);
  tri_side_c_layout->addWidget(tri_side_c_label);
  tri_side_c_layout->addWidget(triSideCSpin_);
  triangle_layout->addLayout(tri_side_a_layout);
  triangle_layout->addLayout(tri_side_b_layout);
  triangle_layout->addLayout(tri_side_c_layout);
  connect(triSideASpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_triangle_side1_changed);
  connect(triSideBSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_triangle_side2_changed);
  connect(triSideCSpin_, &QDoubleSpinBox::valueChanged, this,
          &MainWindow::on_triangle_side3_changed);
}

void MainWindow::hideAllExtraControls() {
  if (circleGroupBox_)
    circleGroupBox_->hide();
  if (starGroupBox_)
    starGroupBox_->hide();
  if (polygonGroupBox_)
    polygonGroupBox_->hide();
  if (rectangleGroupBox_)
    rectangleGroupBox_->hide();
  if (squareGroupBox_)
    squareGroupBox_->hide();
  if (triangleGroupBox_)
    triangleGroupBox_->hide();
}
