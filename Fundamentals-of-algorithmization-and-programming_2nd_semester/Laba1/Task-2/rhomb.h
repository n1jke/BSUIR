#ifndef RHOMB_H
#define RHOMB_H
#include "basefigure.h"

class Rhomb : public BaseFigure {
public:
    Rhomb();

    double area() override;
    double perimeter() override;
    void change_side(double new_side);
    void change_angle(double new_angle);
    void calculate_points() override;

private:
    double side = 100;
    double angle = 60;  // in degrees
};

#endif  // RHOMB_H