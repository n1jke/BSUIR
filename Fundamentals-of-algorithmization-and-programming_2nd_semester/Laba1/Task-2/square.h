#ifndef SQUARE_H
#define SQUARE_H

#include "basefigure.h"

class Square : public BaseFigure {
public:
    Square();

    double get_side();
    double area() override;
    double perimeter() override;
    void calculate_points() override;
    void change_side(double new_side);

private:
    double side = 50;
};

#endif  // SQUARE_H
