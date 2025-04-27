#ifndef CIRCLE_H
#define CIRCLE_H
#include "basefigure.h"

class Circle : public BaseFigure {
public:
    Circle();
    double get_radius();
    void change_radius(double new_radius);
    double area() override;
    double perimeter() override;
    void calculate_points() override {} //  need realization bacause calculate_points  pure virtual
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    double radius = 50;
};

#endif  // CIRCLE_H
