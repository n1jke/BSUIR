#include "rightpolygon.h"
#include <cmath>

RightPolygon::RightPolygon() {
    calculate_points();
}


void RightPolygon::calculate_points() {
    points.resize(vertex_num);
    double angle_increment = 2 * M_PI / vertex_num;
    double radius = side / (2 * std::sin(M_PI / vertex_num));

    for (int i = 0; i < vertex_num; ++i) {
        double angle = i * angle_increment;
        points[i] = QPointF(radius * std::cos(angle), radius * std::sin(angle));
    }

    set_center();// calculates vertices of a regular polygon using polar coordinates
}

void RightPolygon::change_apex_num(int new_apex_num) {
    vertex_num = new_apex_num;
    calculate_points();
    update();
}

void RightPolygon::change_side(double new_side) {
    side = new_side;
    calculate_points();
    update();
}

double RightPolygon::area() {
    return 0.25 * vertex_num * side * side / std::tan(M_PI / vertex_num);
}

double RightPolygon::perimeter() {
    return vertex_num * side;
}

double RightPolygon::get_vertex_count(){
    return vertex_num;
}

