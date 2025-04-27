#ifndef STAR_H
#define STAR_H
#include "basefigure.h"

class Star : public BaseFigure {
public:
    Star();

    double get_inner_radius();
    double get_outer_radius();
    int get_vertex_count();
    double area() override;
    double perimeter() override;
    void calculate_points() override;
    void change_apex_num(int new_vertex_num);
    void change_radius_in(double new_radius_inner);
    void change_radius_out(double new_radius_outer);

private:
    double radius_inner = 40;
    double radius_outer = 80;
    int vertex_num = 5;
};

#endif  // STAR_H
