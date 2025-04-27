#include "star.h"
#include <cmath>

Star::Star() {
  calculate_points();
}

void Star::calculate_points() {
  points.resize(2 * vertex_num);
  double angle_step = M_PI / vertex_num;

  for (int i = 0; i < 2 * vertex_num; ++i) {
    double angle = i * angle_step;
    double radius = (i % 2 == 0) ? radius_outer : radius_inner;
    points[i] = QPointF(std::cos(angle) * radius, std::sin(angle) * radius);
  }

  set_center();
  // calculates vertices of a star with alternating inner and outer radii
}

double Star::area() {
  double angle = M_PI / vertex_num;
  return vertex_num * (radius_outer * radius_inner * std::sin(angle) +
                       0.5 * radius_outer * radius_outer * std::sin(angle) *
                           std::cos(angle));
}

double Star::perimeter() {
  double angle = M_PI / vertex_num;
  double side1 =
      std::sqrt(radius_outer * radius_outer + radius_inner * radius_inner -
                2 * radius_outer * radius_inner * std::cos(angle));

  double side2 = 2 * radius_outer * std::sin(angle);
  return vertex_num * (side1 + side2);
}

double Star::get_inner_radius() {
  return radius_inner;
}

double Star::get_outer_radius() {
  return radius_outer;
}

int Star::get_vertex_count() {
  return vertex_num;
}

void Star::change_apex_num(int new_apex_num) {
  vertex_num = new_apex_num;
  calculate_points();
  update();
}

void Star::change_radius_in(double new_radius_in) {
  radius_inner = new_radius_in;
  calculate_points();
  update();
}

void Star::change_radius_out(double new_radius_out) {
  radius_outer = new_radius_out;
  calculate_points();
  update();
}
