#ifndef RIGHT_POLYGON_H
#define RIGHT_POLYGON_H

#include "basefigure.h"

class RightPolygon : public BaseFigure {
public:
    RightPolygon();

    double get_vertex_count();
    double area() override;
    double perimeter() override;
    void change_side(double new_side);
    void calculate_points() override;
    void change_apex_num(int new_apex_num);

private:
    double side = 50;
    int vertex_num = 4;
};

#endif  // RIGHT_POLYGON_H
