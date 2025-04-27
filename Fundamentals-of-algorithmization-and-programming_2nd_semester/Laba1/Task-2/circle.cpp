#include "circle.h"
#include <cmath>

Circle::Circle() {}

void Circle::change_radius(double new_radius) {
    radius = new_radius;
    update();  // init re-paint
}

void Circle::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget*) {// last two parametr useless
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(QPointF(0, 0), radius, radius);
}

double Circle::area() {
    return M_PI * radius * radius;
}

double Circle::perimeter() {
    return 2 * M_PI * radius;
}

double Circle::get_radius(){
    return radius;
}
