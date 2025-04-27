#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "basefigure.h"

class Triangle : public BaseFigure {
public:
    Triangle();

    double get_side1();
    double get_side2();
    double get_side3();
    double area() override;
    double perimeter() override;
    void calculate_points() override;
    void change_side1(double new_side1);
    void change_side2(double new_side2);
    void change_side3(double new_side3);

private:
    double side1 = 50;
    double side2 = 50;
    double side3 = 50;
};

#endif  // TRIANGLE_H
