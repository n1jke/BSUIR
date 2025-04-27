#include "square.h"

Square::Square() {
    calculate_points();
}

void Square::calculate_points() {
    double half_side = side / 2;
    points.resize(4);
    points[0] = QPointF(-half_side, -half_side);
    points[1] = QPointF(half_side, -half_side);
    points[2] = QPointF(half_side, half_side);
    points[3] = QPointF(-half_side, half_side);
}

double Square::area() {
    return side * side;
}

double Square::perimeter() {
    return side * 4;
}

double Square::get_side(){
    return side;
}

void Square::change_side(double new_side) {
    side = new_side;
    calculate_points();
    update();
}
