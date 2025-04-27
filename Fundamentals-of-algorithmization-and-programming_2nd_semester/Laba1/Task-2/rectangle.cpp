#include "rectangle.h"

Rectangle::Rectangle() {
    calculate_points();
}

void Rectangle::calculate_points() {
    points = {QPointF(0, 0), QPointF(width, 0), QPointF(width, height), QPointF(0, height)};
    set_center();  // center shape at (0, 0)
}

double Rectangle::area() {
    return width * height;
}

double Rectangle::perimeter() {
    return 2 * (height + width);
}

void Rectangle::change_height(double new_height) {
    height = new_height;
    calculate_points();
    update();
}

void Rectangle::change_width(double new_width) {
    width = new_width;
    calculate_points();
    update();
}

double Rectangle::get_width(){
    return width;
}

double Rectangle::get_height(){
    return height;
}
