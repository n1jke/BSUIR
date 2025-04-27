#include "rhomb.h"
#include <cmath>

Rhomb::Rhomb() {
    calculate_points();
}

void Rhomb::calculate_points() {
    points.resize(4);
    double angle_rad = angle * M_PI / 180;
    double x_offset = side * std::cos(angle_rad / 2);
    double y_offset = side * std::sin(angle_rad / 2);

    points[0] = QPointF(0, y_offset);
    points[1] = QPointF(x_offset, 0);
    points[2] = QPointF(0, -y_offset);
    points[3] = QPointF(-x_offset, 0);

    set_center(); //calculates vertices of the rhombus based on side length and angle
}

/*incorrect mb fix
 * void Rhomb::calculate_points() {
    points.resize(4);
    double angle_rad = angle * M_PI / 180;
    double half_diag = side / 2;

    points[0] = QPointF(0, half_diag);
    points[1] = QPointF(half_diag / std::tan(angle_rad / 2), 0);
    points[2] = QPointF(-half_diag, 0);
    points[3] = QPointF(-half_diag / std::tan(angle_rad / 2), 0);

    set_center();// calculates vertices of the rhombus based on side length and angle
}*/

double Rhomb::area() {
    double angle_rad = angle * M_PI / 180;
    return side * side * std::sin(angle_rad);
}

double Rhomb::perimeter() {
    return 4 * side;
}

void Rhomb::change_side(double new_side) {
    side = new_side;
    calculate_points();
    update();
}

void Rhomb::change_angle(double new_angle) {
    angle = new_angle;
    calculate_points();
    update();
}
