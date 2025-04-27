#ifndef BASEFIGURE_H
#define BASEFIGURE_H
#include <QGraphicsObject>
#include <QPainter>
#include <QVector>

class BaseFigure : public QGraphicsObject { // allow to use in graphicscene
public:
  BaseFigure();

  // basic transformation properties
  double rotate_angle = 0;
  double scale_factor = 1;
  bool connected_center = true;

  // methods to modify properties
  void change_rotate_angle(double new_angle);
  void change_scale(double new_scale);
  void move_to(double new_x, double new_y);

  // virtual methods(first 3 pure virtual == withous basic realization)
  virtual double area() = 0;
  virtual double perimeter() = 0;
  virtual void calculate_points() = 0;
  virtual void set_center();

  QRectF boundingRect() const override;     // boundaries for figure
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
  QVector<QPointF> points;

};

#endif
