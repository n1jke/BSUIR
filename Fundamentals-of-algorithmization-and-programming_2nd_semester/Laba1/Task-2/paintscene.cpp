#include "paintscene.h"
#include <QGraphicsItem>

PaintScene::PaintScene(QObject* parent)
    : QGraphicsScene(parent),
      move_steps_(0),
      current_step_(0) {  // lost of initialization
  move_timer_ = new QTimer(this);
  connect(move_timer_, &QTimer::timeout, this, &PaintScene::perform_move);
  move_timer_->setInterval(16);
}

void PaintScene::add_circle() {
  Circle* circle = new Circle();
  circle->move_to(0, 0);
  addItem(circle);
}

void PaintScene::add_rectangle() {
  Rectangle* rect = new Rectangle();
  rect->move_to(0, 0);
  addItem(rect);
}

void PaintScene::add_rhomb() {
  Rhomb* rhomb = new Rhomb();
  rhomb->move_to(0, 0);
  addItem(rhomb);
}

void PaintScene::add_right_polygon() {
  RightPolygon* poly = new RightPolygon();
  poly->move_to(0, 0);
  addItem(poly);
}

void PaintScene::add_square() {
  Square* square = new Square();
  square->move_to(0, 0);
  addItem(square);
}

void PaintScene::add_star() {
  Star* star = new Star();
  star->move_to(0, 0);
  addItem(star);
}

void PaintScene::add_triangle() {
  Triangle* triangle = new Triangle();
  triangle->move_to(0, 0);
  addItem(triangle);
}

void PaintScene::smooth_move_to(double target_x, double target_y) {
  if (selectedItems().isEmpty()) {
    return;
  }

  move_target_ = QPointF(target_x, target_y);
  move_steps_ = 100;  // move by 100 steps
  current_step_ = 0;
  move_timer_->start();
}

void PaintScene::perform_move() {
  if (selectedItems().isEmpty() || current_step_ >= move_steps_) {
    move_timer_->stop();
    return;
  }
  //find step for evetu figure
  for (QGraphicsItem* item : selectedItems()) {
    if (BaseFigure* figure = dynamic_cast<BaseFigure*>(
            item)) {  // dynamic_cast -- check is objects its a figure
      QPointF currentPos = figure->pos();
      QPointF step =
          (move_target_ - currentPos) / (move_steps_ - current_step_);
      figure->move_to(currentPos.x() + step.x(), currentPos.y() + step.y());
    }
  }
  ++current_step_;
}
