#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "basefigure.h"

class Rectangle : public BaseFigure {
public:
    Rectangle();

    double get_width();
    double get_height();
    double area() override;
    double perimeter() override;
    void calculate_points() override;
    void change_height(double new_height);
    void change_width(double new_width);

private:
    double height = 50;
    double width = 100;
};

#endif  // RECTANGLE_H
