#include "basefigure.h"

BaseFigure::BaseFigure() {
  setFlag(ItemIsMovable, true);     // enable mouse movement
  setFlag(ItemIsSelectable, true);  // enable selection for buttons
  setTransformOriginPoint(0, 0);    // rotate and scale around basic point
}

void BaseFigure::change_rotate_angle(double new_angle) {
  rotate_angle = new_angle;
  setRotation(rotate_angle);  // built-in realization
  update();
}

void BaseFigure::change_scale(double new_scale) {
  scale_factor = new_scale;
  setScale(scale_factor);  // built-in realization
  update();
}

void BaseFigure::move_to(double new_x, double new_y) {
  setPos(new_x, new_y);  // update position built-in realizstion
  update();
}

void BaseFigure::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                       QWidget*) {  // dont use last two parametres
  calculate_points();               // update shape points
  QPolygonF polygon(points);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawPolygon(polygon);
  painter->drawEllipse(QPointF(0, 0), 1, 1);  // centre point
}

void BaseFigure::set_center() {
  if (points.isEmpty()) {
    return;
  }
  double center_x = 0;
  double center_y = 0;
  for (const QPointF& point : points) {
    center_x += point.x();
    center_y += point.y();
  }
  center_x /= points.size();
  center_y /= points.size();
  // shift points so center is at (0, 0)
  for (QPointF& point : points) {
    point -= QPointF(center_x, center_y);
  }
}

QRectF BaseFigure::boundingRect() const {  // which area the object occupies
  if (points.isEmpty())
    return QRectF();
  double min_x = points[0].x(), max_x = points[0].x();
  double min_y = points[0].y(), max_y = points[0].y();
  for (const QPointF& p : points) {
    min_x = std::min(min_x, p.x());
    max_x = std::max(max_x, p.x());
    min_y = std::min(min_y, p.y());
    max_y = std::max(max_y, p.y());
  }
  return QRectF(min_x, min_y, max_x - min_x, max_y - min_y);
}
