#include "triangle.h"
#include <cmath>

Triangle::Triangle() {
  calculate_points();
}

void Triangle::calculate_points() {
  points.resize(3);
  points.resize(3);
  if (side1 <= 0 || side2 <= 0 || side3 <= 0 || side1 + side2 <= side3 ||
      side1 + side3 <= side2 || side2 + side3 <= side1) {

    points[0] = points[1] = points[2] = QPointF(0, 0);
    return;
  } else {
    points[0] = QPointF(0, 0);
    points[1] = QPointF(side1, 0);
    // calculate third point using your equations
    double x = (side3 * side3 + side1 * side1 - side2 * side2) / (2.0 * side1);
    double y = std::sqrt(side3 * side3 - x * x);
    points[2] = QPointF(x, y);
    set_center();  // center shape at (0, 0)
  }

  /*
    1p -- x^2 + y^2 = side2^2
    2p -- (x -side1)^2 + y^2 = side3^2
    2 - 1 -- (x - side1)^2  - x^2 = side3^2 - side2^2
    upsolving -2xside1 + side1^2 = side3^2 - side2^2
    findX x = (side1^2 + side2^2 - side3^2) / (2side1)
    findYaddX to 1 y = sqrt(side2^2 - x^2)
    */
}

double Triangle::area() {
  double p = (side1 + side2 + side3) / 2;
  return std::sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

double Triangle::perimeter() {
  return side1 + side2 + side3;
}

void Triangle::change_side1(double new_side1) {
  side1 = new_side1;
  calculate_points();
  update();
}

void Triangle::change_side2(double new_side2) {
  side2 = new_side2;
  calculate_points();
  update();
}

void Triangle::change_side3(double new_side3) {
  side3 = new_side3;
  calculate_points();
  update();
}

double Triangle::get_side1() {
  return side1;
}

double Triangle::get_side2() {
  return side2;
}

double Triangle::get_side3() {
  return side3;
}
