#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QPointF>

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "rhomb.h"
#include "rightpolygon.h"
#include "square.h"
#include "star.h"

class PaintScene : public QGraphicsScene {
  Q_OBJECT //macros to use slots and signlas

 public:
  explicit PaintScene(QObject* parent = nullptr);// explicit to DONT make implicit casts; parent to become a child and refrashe at the end
  void add_circle();
  void add_rectangle();
  void add_rhomb();
  void add_right_polygon();
  void add_square();
  void add_star();
  void add_triangle();
  void smooth_move_to(double target_x, double target_y);

 private slots:

  void perform_move();

 private:
  QTimer* move_timer_;
  QPointF move_target_;
  int move_steps_;
  int current_step_;
};

#endif  // PAINTSCENE_H
